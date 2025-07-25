#include "main.h"

using namespace ks;

double    x = 0; // global X
double    y = 0; // global Y
double    theta = 0; // global theta

// Gyro scale effect from 2775V
// If it is a bit less than 360, that's your number. If it is a bit more than 0, add 360 and that's your number.
double gyro_scale1 = 360;
double gyro_scale2 = 360;

double vertical_wheel_diameter = 2.0;
double vertical_wheel_offset = -0.244094;

double horizontal_wheel_diameter = 2.0;
double horizontal_wheel_offset = 0.0;
double gear_ratio = 36.0 / 48;

// Return robot rotation in degrees, unwrapped
double get_imu_rotation() {
	double rotation1 = inertial1.get_rotation();
	double rotation2 = inertial2.get_rotation();

	if (!isnanf(inertial2.get_rotation()) && !isinf(inertial2.get_rotation())) { // use imu 2 when available
		return (rotation1 + rotation2) / 2;
	} else {
		return rotation1;
	}
	//return rotation1;
}

double get_vertical_distance_traveled() {
	if (!isnanf(verticalEncoder.get_position()) && !isinf(verticalEncoder.get_position())) { // use rot sensor as priority
		return ((verticalEncoder.get_position() / 36000.0) * M_PI * vertical_wheel_diameter); // 1 is gear ratio
	} else if (!isnanf(leftDrive.get_position(0)) && !isinf(leftDrive.get_position(0))) { // 900 is cartridge gearing, leave since its factored into rpm
		console.println("ODOM Using motor encoder fallback");
		double left_distance = (leftDrive.get_position(0) / 900 * (vertical_wheel_diameter * M_PI) / gear_ratio);
		double right_distance = (rightDrive.get_position(0) / 900 * (vertical_wheel_diameter * M_PI) / gear_ratio);

		return (left_distance + right_distance) / 2; // find avg
	} else {
		return 0;
	}
}
double get_horizontal_distance_traveled() { 
	return ((horizontalEncoder.get_position() / 36000.0) * M_PI * horizontal_wheel_diameter);
}

// double get_dt_heading() {
// 	double wheel_circumference = M_PI * wheel_diameter;

// 	double left_distance = (leftDrive.at(1).get_position() / 360) * wheel_circumference / gear_ratio;
// 	double right_distance = (rightDrive.at(1).get_position() / 360) * wheel_circumference / gear_ratio;

// 	double heading_in_radians = (left_distance - right_distance) / track_width;
// 	return std::fmod(to_deg(heading_in_radians), 360);
// }


// important vars for odom
double vertical_pos;
double horizontal_pos;

double prev_vertical_pos = 0;
double prev_horizontal_pos = 0;

double delta_vertical;
double delta_horizontal;

double heading;
double prev_heading;
double delta_heading;
double avg_heading;
	
double deltaXLocal;
double deltaYLocal;

void ks::initializeOdom() {
	inertial1.reset();
	inertial2.reset();

	verticalEncoder.reset_position();
	horizontalEncoder.reset_position();
	
	if (inertial1.reset() != PROS_ERR) {	
	  	while( inertial1.is_calibrating() ) {
			pros::delay(10);
	  	}
	  	console.println("Passed Primary IMU calibration check"); 
	} else {
	  	if( errno == ENODEV ) {
			console.println("[ERROR] Primary IMU failed to calibrate...");
	  	}
	}

	while (isnanf(inertial1.get_rotation()) || isinf(inertial1.get_rotation())) {
		pros::delay(10);
	}

	vertical_pos = get_vertical_distance_traveled();
	horizontal_pos = get_horizontal_distance_traveled();
	heading = to_rad(fmod((360 - get_imu_rotation()) + 90, 360));

	prev_vertical_pos = vertical_pos;
	prev_horizontal_pos = horizontal_pos;
	prev_heading = heading;

	pros::Task odom_task(ks::odomUpdate); 
}

void ks::setOdomPosition(double x_new, double y_new, double theta_new) {
	update_odom = false; // stop odom task loop
	x = 0;
	y = 0;

	verticalEncoder.reset_position();
	horizontalEncoder.reset_position();

	prev_vertical_pos = 0;
	prev_horizontal_pos = 0;
	vertical_pos = 0;
	horizontal_pos = 0;

	prev_heading = 0;

	if (theta_new != 360) {
		inertial1.set_rotation(theta_new);
		inertial2.set_rotation(theta_new);
	}
	update_odom = true; // resume odom task loop
}
/* // pos reset - do not run async
float absX = -((backwardDist.get_distance() / 25.4 + 3.9) - 72);
float absY = leftDist.get_distance() / 25.4 - 0;
chassis.setPose(absX, absY, chassis.getPose().theta); */

void ks::odomUpdate() {
	console.printf("%.0lf, %.0lf", verticalEncoder.get_position(), get_horizontal_distance_traveled());

	while (true) {
		if (update_odom == true) {
			// printf("%f, %f\n", get_vertical_distance_traveled(), get_horizontal_distance_traveled());
			vertical_pos = get_vertical_distance_traveled();
			horizontal_pos = get_horizontal_distance_traveled();

			delta_vertical = (vertical_pos - prev_vertical_pos);
			delta_horizontal = (horizontal_pos - prev_horizontal_pos);

			prev_vertical_pos = vertical_pos;
			prev_horizontal_pos = horizontal_pos;

			heading = to_rad(fmod((360 - get_imu_rotation()) + 90, 360)); // convert compass to standard position in RAD
			delta_heading = heading - prev_heading;
			prev_heading = heading;

			if (delta_heading == 0) {
				deltaXLocal = delta_horizontal;
				deltaYLocal = delta_vertical;
			} else {
				// LEFT_TRACKING_RADIUS is the distance from the left tracking wheel to the tracking center of the robot
				// PERPENDICULAR_TRACKING_RADIUS is the distance from the perpendicular tracking wheel to the tracking center of the robot
				deltaXLocal = 2 * sin(delta_heading / 2) * ((delta_horizontal / delta_heading) + horizontal_wheel_offset);
				deltaYLocal = 2 * sin(delta_heading / 2) * ((delta_vertical / delta_heading) + vertical_wheel_offset);
			}

			avg_heading = heading - (delta_heading / 2);

			x += (deltaYLocal * cos(avg_heading)) + (deltaXLocal * sin(avg_heading));
			y += (deltaYLocal * sin(avg_heading)) - (deltaXLocal * cos(avg_heading));

			chassis.setPose(x, y, get_imu_rotation());
		}
		pros::delay(10);
	}
}