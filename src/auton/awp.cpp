#include "deviceGlobals.hpp"
#include "libKS/drivetrain/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void sawp() {
	// libKS MTPoint v0.1
// Starting point: (-48.82 in, 13.41 in)
chassis.moveToPoint(0.00, 0.00, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 127}); // Point 1
chassis.moveToPoint(-0, 30.903, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 2
chassis.turnToHeading(90, 600); // Turn to 90 degrees
pros::Task([] {
	liftPiston.set_value(true); // Lift piston up
	trapdoorPiston.set_value(true); // Trapdoor piston up
	pros::delay(800);
	intake.move_voltage(12000); // Spin intake
});
// drive into goal #1
chassis.moveToPoint(16.59, 32.18, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 120, .earlyExitRange = 0}); // Point 3
pros::delay(350);
chassis.moveToPoint(6, 32.78, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 8, .earlyExitRange = 0}); // Point 4
chassis.moveToPoint(24.242,6., 2000, {.forwards = true, .maxSpeed = 45, .minSpeed = 45}); // Point 5
//ks::moveStraight(15, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0});
chassis.moveToPoint(34.8, -2.3, 1200, {.forwards = true, .maxSpeed = 70, .minSpeed = 70}); // Point 6
pros::Task([] {
	pros::delay(200);
	liftPiston.set_value(false); // Lift piston up
	pros::delay(1900);
	trapdoorPiston.set_value(false); // Trapdoor piston down
});
pros::delay(1950);
chassis.moveToPoint(15, 0, 1000, {.forwards = false, .minSpeed = 110}); // Point 7
pros::Task([] {
	pros::delay(400);
	liftPiston.set_value(true); // Lift piston up
});
chassis.moveToPoint(25.900, -41.0, 2000, {.forwards = true, .maxSpeed = 75, .minSpeed = 0, .earlyExitRange = 0}); // Point 7
chassis.moveToPoint(3.58, -61.06, 1500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
chassis.turnToHeading(90, 700); // Turn to 90 degrees
chassis.moveToPoint(15.910, -61.27, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
pros::Task([] {
	pros::delay(300);
	intake.move_voltage(-12000); // Spin intake
	pros::delay(125);
	trapdoorPiston.set_value(true);
	intake.move_voltage(12000); // Trapdoor piston up
});
pros::delay(1650);
chassis.moveToPoint(10, -61.7, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 100, .earlyExitRange = 0}); // Point 11
// ks::moveStraight(-12, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 1.5}); // Point 11
pros::Task([] {
	pros::delay(300);
	loaderPiston.set_value(true);
	pros::delay(1300);
	trapdoorPiston.set_value(false); // dropdown match loader
});
chassis.turnToHeading(270, 900, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE}, false);
chassis.moveToPoint(-10.4, -61.456, 1500, {.forwards = true, .maxSpeed = 100, .minSpeed = 90}); // Point 11
pros::delay(1300);
//ks::moveStraight(30, 1500, {.forwards = false, .maxSpeed = 40, .minSpeed = 0}); // Point 12
//chassis.moveToPoint(-10.9, -61.6, 800, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 12
//ks::moveStraight(2, 200, {.forwards = true, .maxSpeed = 5, .minSpeed = 0});
ks::moveStraight(-2, 200, {.forwards = false, .maxSpeed = 30, .minSpeed = 250});

//chassis.moveToPoint(-15.10, -61.66, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
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