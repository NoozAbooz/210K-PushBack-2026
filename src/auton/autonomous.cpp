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
    kw::driveTo(24, 3000, 127);
    kw::turnToAngle(180, 1500);
    kw::driveTo(24, 3000, 127);
    kw::turnToAngle(0, 1500);

}
void testDistReset() {
    double weights = 0; // weighted average distance from keej https://github.com/8pxl/keejLib/blob/main/lib/src/keejLib/odom.cpp
    double weightedDist = 0;

    for (int i=0; i<3; i++) {
        double distReading = kw::mm_to_in(fwdDistance.get_distance());
        double confidence = fwdDistance.get_distance();
        if (confidence <= 20) { confidence = 2; } 
        weights += confidence;
        weightedDist += distReading * confidence;
        pros::delay(10);
    }
    double avgDist = weightedDist / weights;
        

    kw::set_odom_position(0, 0);
    //chassis.moveToPose(24, 24, 90, 1500);
}
void testColourSort() {
    alliance = "red"; // set alliance to red for testing
    toggleColourSort = true;
}

/* Legacy Auton Routines */
void driveForward() {

}

rd::Selector gui_selector({ // SAWP (Solo AWP), HAWP (Half AWP)
    {"SAWP", sawp, "", 0},
    {"Left Side AWP", left_half, "", 0},
    {"Right Side AWP", right_half, "", 0},

    {"Elim Routines", nullptr, "Submenu for Elim Routines", 0},
    {"Right Side Elim", right_elim, "", 0},
    {"Left Side Elim", left_elim, "", 0},

    {"Skills", skills, "", 100},

    {"Move forward", driveForward, "", 0},
    { "Test PID", testPID, "", 220},
    { "Test BM", testDistReset, "", 220},
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
    gui_selector.run_auton();
}