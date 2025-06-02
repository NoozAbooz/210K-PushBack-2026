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
    chassis.moveToPoint(0, 24, 1000);
    intake.move_voltage(12000);
    //chassis.turnToHeading(90, 2000);
    //chassis.moveToPoint(24, 24, 1000);
}
void testBM() {
    chassis.moveToPose(24, 24, 90, 1500);
}

/* Legacy Auton Routines */
void driveForward() {
    chassis.moveToPoint(0, 5, 1000);
}

rd::Selector gui_selector({ // SAWP (Solo AWP), HAWP (Half AWP)
    {"SAWP", sawp, "", 0},
    {"Left Half-AWP", left_half, "", 0},
    {"Right Half-AWP", right_half, "", 0},

    {"Skills", skills, "", 100},

    {"Move forward", driveForward, "", 0},
    { "Test PID", testPID, "", 220},
    { "Test BM", testBM, "", 220},
});

void autonomous() {
    inertial1.tare();

    chassis.setPose(0, 0, 0);
    field_status = "autonomous";
    console.println("Running auton...");
    gui_selector.run_auton();
}