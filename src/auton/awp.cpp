#include "deviceGlobals.hpp"
#include "libKS/drivetrain/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void sawp() {
	// libKS MTPoint v0.1
// Starting point: (-48.82 in, 13.41 in)
chassis.moveToPoint(0.00, 0.00, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 2}); // Point 1
chassis.moveToPoint(-0, 30.03, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 1}); // Point 2
chassis.turnToHeading(90, 600); // Turn to 90 degrees
pros::Task([] {
	liftPiston.set_value(true); // Lift piston up
	trapdoorPiston.set_value(true); // Trapdoor piston up
	pros::delay(780);
	intake.move_voltage(12000); // Spin intake
});
// drive into goal #1
chassis.moveToPoint(18.39, 32.28, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 3
pros::delay(50);
chassis.moveToPoint(0.0, 32.78, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 9, .earlyExitRange = 5}); // Point 4

chassis.moveToPoint(24.02, 9.70, 1000, {.forwards = true, .maxSpeed = 70, .minSpeed = 0}); // Point 5
chassis.moveToPoint(39.92, -6.7, 1000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 6
pros::Task([] {
	pros::delay(900);
	liftPiston.set_value(false); // Lift piston up
	pros::delay(1650);
	trapdoorPiston.set_value(false); // Trapdoor piston down
});
pros::delay(2600);
chassis.moveToPoint(29, 5, 1000, {.forwards = false, .minSpeed = 110, .earlyExitRange = 2}); // Point 7
pros::Task([] {
	pros::delay(400);
	liftPiston.set_value(true); // Lift piston up
});
chassis.moveToPoint(27.74, -43.70, 2000, {.forwards = true, .maxSpeed = 85, .minSpeed = 0}); // Point 7
chassis.moveToPoint(3.58, -60.16, 1500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
chassis.turnToHeading(90, 700); // Turn to 90 degrees
chassis.moveToPoint(16.70, -60.46, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
pros::Task([] {
	pros::delay(300);
	intake.move_voltage(-12000); // Spin intake
	pros::delay(125);
	trapdoorPiston.set_value(true);
	intake.move_voltage(12000); // Trapdoor piston up
});
pros::delay(1500);
//chassis.moveToPoint(5, -61.69, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 1.5}); // Point 11
ks::moveStraight(-12, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 1.5}); // Point 11
pros::Task([] {
	pros::delay(300);
	loaderPiston.set_value(true); // dropdown match loader
});
chassis.turnToHeading(270, 900, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE}, false);
chassis.moveToPoint(-9.7, -60.46, 300, {.forwards = true, .maxSpeed = 127, .minSpeed = 127}); // Point 11
ks::moveStraight(30, 8000, {.forwards = false, .maxSpeed = 60, .minSpeed = 0}); // Point 12
//chassis.moveToPoint(-10, -61.16, 800, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 12
//ks::moveStraight(16, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 127});

//chassis.moveToPoint(-15.10, -61.16, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
}

void left_half() { // Left Side Half Solo AWP

}

void right_half() { // Right Side Half Solo AWP

}

/* LEGACY */

void old_sawp() {
// libKS MTPoint v0.1
// Starting point: (54.83 in, 12.77 in)
// chassis.moveToPoint(0.00, 0.00, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
// liftPiston.set_value(true); // Lift piston up
// chassis.moveToPoint(-4, 31.83, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 2
// chassis.turnToHeading(90, 1000); // Turn to 90 degrees
// loaderPiston.set_value(true); // Loader piston up
// intake.move_voltage(12000); // Spin intake
// chassis.moveToPoint(4.915, 31.53, 1200, {.forwards = true, .maxSpeed = 127, .minSpeed = 127}); // Point 3
// pros::delay(1150);
// chassis.moveToPoint(-4.15, 30.90, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 4
// chassis.turnToHeading(270, 1000); // Turn to 270 degrees
// pros::delay(500);
// loaderPiston.set_value(false); // Loader piston down
// intake.move_voltage(12000); // Reverse intake
// chassis.moveToPoint(-24.70, 34.63, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 4
// pros::delay(500);
// trapdoorPiston.set_value(true); // Trapdoor piston up
// intake.move_voltage(-5000); // Stop intake
// pros::delay(500);
// intake.move_voltage(12000); // Reverse intake
// pros::delay(2100);
// chassis.moveToPoint(-17.45, 30.83, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127}); // Point 5
// chassis.turnToHeading(225, 1000); // Turn to 225 degrees
// chassis.moveToPoint(-35.83, 10.66, 3000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 6
// chassis.moveToPoint(-47.52, -4.62, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
// pros::delay(700);
// intake.move_voltage(-5000); // Stop intake
// pros::delay(500);
// chassis.turnToHeading(225, 1000); // Turn to 0 degrees
// pros::delay(2500);
// chassis.moveToPoint(-31, 3, 1000, {.forwards = false});
// chassis.moveToPoint(-31.55, -37.34, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
// chassis.turnToHeading(315, 1000);
// chassis.moveToPoint(-42.49, -29.40, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
// // chassis.moveToPoint(-4.51, -58.59, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
// chassis.moveToPoint(7.73, -59.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 11
// chassis.moveToPoint(-27.04, -59.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 12

}