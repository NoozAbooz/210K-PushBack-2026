#include "main.h"

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

void testDistReset() {
   kw::boomerang(31, 35.5, 90, 0.35, 2000, true, 90);
    kw::turnToAngle(90, 900);
    loaderPiston.set_value(true);
    wingPiston.set_value(true);
    intakeMacro("L1");

    // go into zone
    
    pros::delay(260);
    kw::move_raw(6000, 6000);
    pros::delay(280);
    kw::move_raw(8000, 8000);
    pros::delay(230);
    kw::move_raw(4000, 4000);
    pros::delay(200);
    loaderPiston.set_value(false);
    pros::delay(700);

    kw::move_raw(6000, 6000);
    pros::delay(1200);
    kw::turnToAngle(90, 1000);
    kw::move_raw(-4000, -4000);
    wingPiston.set_value(false);
    pros::delay(1400);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(100);
    
    // // reset
    // reset_x_coord = 0;//(kw::getDistance(bwdDistance));
    // reset_y_coord = -(kw::getDistance(leftDistance));
    kw::set_odom_position(0, 0, 0);
    kw::turnToAngle(270,1000);
    kw::moveToPoint(30, -6, 1000, false);
    kw::turnToAngle(270,1000);
    intakeMacro("stop");
    intake_velocity.set_target(0);
    kw::boomerang(54, -5, 315, 0.3, 2000, false, 60);
    kw::move_raw(-4000, -4000);
    pros::delay(200);
    intakeMacro("R2");
     intake_velocity.set_target(490);
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
            kw::move_raw(6000, -6000);
            // kw::turnToAngle(175, 1500);
        } else {
            kw::move_raw(-6000, 6000);
            // kw::turnToAngle(185, 1500);
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
            
            if (pros::millis() - start_time > 1000) {
                kw::stop_chassis(pros::E_MOTOR_BRAKE_BRAKE);
            }
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
    {"True SAWP", true_sawp, "", 0},
    {"Left Awp", left_half, "", 0},
    {"Right Awp", right_half, "", 0},

    {"7 Right", right_7, "", 0},
    {"6+3", left_elim, "", 0},
    {"7 Left", left_7, "", 0},

    {"Skills", skills, "", 100},

    {"Move forward", testPID, "", 0},
    { "Measure Odom Offsets", measureOdomOffsets, "", 220},
    // { "Test PID", testPID, "", 220},
    { "Test DistReset", testDistReset, "", 220},
    // { "Test Colour Sort", testColourSort, "", 220},
    // {"Legacy SAWP", legacy_sawp, "", 0},
    {"97 skills", skills, "", 0},
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
        rumble_pattern = ".-"; //notify driver
	}
    console.println("Running auton...");
    rd_view_focus(sensorview);
    gui_selector.run_auton();
}
