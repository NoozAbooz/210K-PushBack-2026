#include "main.h"
#include <cmath>

double kw::x_pos = 0; // global X
double kw::y_pos = 0; // global Y
double kw::theta = 0; // global theta [0, 359]

double kw::correct_angle = 0;
bool kw::update_odom = true;

// Return robot rotation in degrees, unwrapped
double kw::get_imu_rotation() {
	double rotation1 = inertial1.get_rotation();
	double rotation2 = inertial2.get_rotation();

	// if (!isnanf(inertial2.get_rotation()) && !std::isinf(inertial2.get_rotation())) { // use imu 2 when available
	// 	return (rotation1 + rotation2) / 2;
	// } else {
		return rotation1;
	// }
}

double kw::get_vertical_distance_traveled() {
	if (!isnanf(verticalEncoder.get_position()) && !std::isinf(verticalEncoder.get_position())) { // use rot sensor as priority
		return ((verticalEncoder.get_position() / 36000.0) * M_PI * kw::vertical_tracker_diameter);
	} else if (!isnanf(leftDrive.get_position(0)) && !std::isinf(leftDrive.get_position(0))) { // 900 is cartridge gearing, leave since its factored into rpm
		console.println("ODOM Using motor encoder fallback");
		double left_distance = (leftDrive.get_position(0) / 900 * kw::wheel_distance_in);
		double right_distance = (rightDrive.get_position(0) / 900 * kw::wheel_distance_in);

		return (left_distance + right_distance) / 2; // find avg
	} else {
		return 0;
	}
}
double kw::get_horizontal_distance_traveled() {
	return ((horizontalEncoder.get_position() / 36000.0) * M_PI * kw::horizontal_tracker_diameter);
}

// double get_dt_heading() {
// 	double wheel_circumference = M_PI * wheel_diameter;

// 	double left_distance = (leftDrive.at(1).get_position() / 360) * wheel_circumference / gear_ratio;
// 	double right_distance = (rightDrive.at(1).get_position() / 360) * wheel_circumference / gear_ratio;

// 	double heading_in_radians = (left_distance - right_distance) / track_width;
// 	return std::fmod(to_deg(heading_in_radians), 360);
// }


// important vars for odom
double prev_heading_rad = 0;
double prev_horizontal_pos = 0, prev_vertical_pos = 0;
double delta_local_x_in = 0, delta_local_y_in = 0;
double local_polar_angle_rad = 0;

void kw::reset_chassis() {
	inertial1.reset();
	inertial2.reset();

	verticalEncoder.reset_position();
	horizontalEncoder.reset_position();
}

void kw::initialize_odom() {
	kw::reset_chassis();
	
	if (inertial1.reset() != PROS_ERR) {	
	  	while( inertial1.is_calibrating() ) {
			pros::delay(10);
	  	}
	  	console.println("Passed Primary IMU calibration check"); 
	} else {
	  	if( errno == ENODEV ) {
			rumble_pattern = "---";
			console.println("[ERROR] Primary IMU failed to calibrate...");
	  	}
	}

	double start_time = pros::millis();
	while (isnanf(inertial1.get_rotation()) || std::isinf(inertial1.get_rotation())) {
		pros::delay(10);
	}

	rumble_pattern = ".";
	pros::Task odom_task(kw::odom_update); 
}

void kw::set_odom_position(double x_new, double y_new, double theta_new) {
	update_odom = false; // stop odom task loop
	x_pos = x_new;
	y_pos = y_new;

	verticalEncoder.reset_position();
	horizontalEncoder.reset_position();

	prev_vertical_pos = 0;
	prev_horizontal_pos = 0;
	prev_heading_rad = 0;

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

void kw::odom_update() {
	console.printf("%.0lf, %.0lf", verticalEncoder.get_position(), get_horizontal_distance_traveled());

	while (true) {
		if (update_odom == true) {
			// printf("%f, %f\n", get_vertical_distance_traveled(), get_horizontal_distance_traveled());
			double heading_rad = kw::to_rad(kw::get_imu_rotation());
			double vertical_pos = kw::get_vertical_distance_traveled();
    		double horizontal_pos = kw::get_horizontal_distance_traveled();

    		double delta_heading_rad = heading_rad - prev_heading_rad;
			double delta_vertical_in = (vertical_pos - prev_vertical_pos);
    		double delta_horizontal_in = (horizontal_pos - prev_horizontal_pos);
    		
    		// Calculate local movement based on heading change
    		if (fabs(delta_heading_rad) < 1e-6) {
    		  	delta_local_x_in = delta_horizontal_in;
    		  	delta_local_y_in = delta_vertical_in;
    		} else {
    		  	double sin_multiplier = 2.0 * sin(delta_heading_rad / 2.0);
    		  	delta_local_x_in = sin_multiplier * ((delta_horizontal_in / delta_heading_rad) + kw::horizontal_tracker_dist_from_center);
    		  	delta_local_y_in = sin_multiplier * ((delta_vertical_in / delta_heading_rad) + kw::vertical_tracker_dist_from_center);
    		}
		
    		// Avoid undefined atan2(0, 0)
    		if (fabs(delta_local_x_in) < 1e-6 && fabs(delta_local_y_in) < 1e-6) {
    		  	local_polar_angle_rad = 0;
    		} else {
    		  	local_polar_angle_rad = atan2(delta_local_y_in, delta_local_x_in);
    		}
    		double polar_radius_in = sqrt(pow(delta_local_x_in, 2) + pow(delta_local_y_in, 2));
    		double polar_angle_rad = local_polar_angle_rad - heading_rad - (delta_heading_rad / 2);
		
    		x_pos += polar_radius_in * cos(polar_angle_rad);
    		y_pos += polar_radius_in * sin(polar_angle_rad);
			theta = fmod(kw::get_imu_rotation(), 360); // wrap to [0, 360) for user view
    		if (theta < 0) theta += 360;
		
    		prev_heading_rad = heading_rad;
    		prev_horizontal_pos = horizontal_pos;
    		prev_vertical_pos = vertical_pos;
		}

		pros::delay(10);
	}
}