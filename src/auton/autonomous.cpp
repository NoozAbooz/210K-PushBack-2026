#include "libKW/config.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "libKW/drivetrain/odom.hpp"
#include "main.h"
#include "libKW/api.hpp"
#include "pros/motors.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void testPID() {
    //kw::driveTo(24, 3000, 127);
    //kw::moveToPoint(0, 24, 1000)  ; // kw::turnToAngle(180, 1500);
    // kw::driveTo(24, 3000, 127);
   // kw::driveTo(5, 1000);

}

double getDistance(pros::Distance& sensor) {
    double weights = 0; // weighted average distance from keej https://github.com/8pxl/keejLib/blob/main/lib/src/keejLib/odom.cpp
    double weightedDist = 0;

    for (int i=0; i<4; i++) {
        double distReading = kw::mm_to_in(sensor.get_distance());
        double confidence = sensor.get_confidence();
        if (confidence <= 20) confidence = 2;
        weights += confidence;
        weightedDist += distReading * confidence;
        pros::delay(10);
    }
    return weightedDist / weights;
}

void testDistReset() {
    // initial position: bwd 48.5n, right 1.2in
    intakeMacro("L1"); // all ts for a park zone clear
    kw::move_raw(6000, 6000);
    pros::delay(300);
    kw::move_raw(8000, 8000);
    pros::delay(500);
    kw::move_raw(6000, 6000);
    pros::delay(700);
    kw::move_raw(12000, 12000);
    pros::delay(500);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(200);

    kw::turnToAngle(0, 800); // make sure angle isnt fucked up by our barrier cross
    // odom reset!!!
    kw::set_odom_position(getDistance(rightDistance) - 1.2, getDistance(bwdDistance) - 48.5);
    
    // move bwd to midgoal
    kw::turnToPoint(-51, 10, 1000, false);
    kw::moveToPoint(-51, 10, 2000, false);

    // align with midgoal
    kw::swing(140, 1000, false);

    // grab 1 blue ball, score all 7
    kw::driveTo(9, 800);
    kw::driveTo(-10, 800);
    intakeMacro("R2");
    intake_velocity.set_target(500); // sketchy workaround to make velo controller work

    pros::delay(4000);
    kw::driveTo(5, 800, 127, false);
    intakeMacro("L1");
    loaderPiston.set_value(true);
    blockerPiston.set_value(true);
    wingPiston.set_value(true);

    kw::moveToPoint(-27, 27, 2000);
    kw::turnToAngle(90, 1000);

}

void testColourSort() {
    alliance = "red"; // set alliance to red for testing
    toggleColourSort = true;
    intakeMacro("R1");
}

void measureOdomOffsets() {
    std::pair<double, double> offsets = {0,0};
    for (int i = 0; i < 2; i++) {
        std::pair<double, double> deltaEnc = {0, 0};
        double imuStart = kw::get_imu_rotation();

        // this -> turn(target, {.async = true, .timeout=1000, .exit = new exit::Range(0.01, 500)});
        kw::set_odom_position(0, 0);
        std::pair<double, double> prev = {0,0};

        if (i % 2 == 0) {
            //kw::move_raw(6000, -6000);
            kw::turnToAngle(175, 1500);
        } else {
            //kw::move_raw(-6000, 6000);
            kw::turnToAngle(185, 1500);
        }
        int start_time = pros::millis();

        while (pros::millis() - start_time < 1800) {
            double currVert = verticalEncoder.get_position() / 100.0;
            double currHoriz = horizontalEncoder.get_position() / 100.0;
            
            deltaEnc.first += fabs(currVert - prev.first);
            deltaEnc.second += fabs(currHoriz - prev.second);
            // std::cout << "vert: " << deltaEnc.first << " horiz: " << deltaEnc.second << std::endl;
            prev.first = currVert;
            prev.second = currHoriz;
            pros::delay(10);
            
            // if (pros::millis() - start_time > 1000) {
            //     kw::stop_chassis(pros::E_MOTOR_BRAKE_BRAKE);
            // }
        }
        double delta = kw::to_rad(fabs(kw::get_imu_rotation() - imuStart));
        // std::cout << delta << std::endl;
        offsets.first += ((deltaEnc.first / 360) * M_PI * kw::vertical_tracker_diameter) / delta;
        offsets.second += ((deltaEnc.second / 360) * M_PI * kw::horizontal_tracker_diameter) / delta;
    }
    console.printf("Vert Pod Offset: %.2lf\n", offsets.first / 2);
    console.printf("Horiz Pod Offset: %.2lf\n", offsets.second / 2);
}

/* Legacy Auton Routines */
void driveForward() {
    kw::driveTo(6, 3000);
}

rd::Selector gui_selector({ // SAWP (Solo AWP), HAWP (Half AWP)
    {"SAWP", sawp, "", 0},
    {"Left Awp", left_half, "", 0},
    {"Right Awp", right_half, "", 0},

    {"7 Right", right_7, "", 0},
    {"7 Left", left_7, "", 0},

    {"Skills", skills, "", 100},

    {"Move forward", testPID, "", 0},
    { "Measure Odom Offsets", measureOdomOffsets, "", 220},
    // { "Test PID", testPID, "", 220},
    { "Test DistReset", testDistReset, "", 220},
    // { "Test Colour Sort", testColourSort, "", 220},
    // {"Legacy SAWP", legacy_sawp, "", 0},
    {"Legacy Skills", Legacy_skills, "", 0}
});

void autonomous() {
    inertial1.tare();
    inertial2.tare();

    kw::set_odom_position(0, 0, 0);

    field_status = "autonomous";

    // wait for inertial to calibrate until starting auton
    int start_time = pros::millis();
    while ((isnanf(inertial1.get_rotation()) || std::isinf(inertial1.get_rotation())) && start_time < 2800) {
		pros::delay(10);
	}
    console.println("Running auton...");
    rd_view_focus(sensorview);
    gui_selector.run_auton();
}