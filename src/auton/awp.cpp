#include "deviceGlobals.hpp"
#include "libKS/drivetrain/chassis.hpp"
#include "main.h"

void sawp() {
	// libKS MTPoint v0.1
// Starting point: (-48.82 in, 13.41 in)
chassis.moveToPoint(0.00, 0.00, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 2}); // Point 1
chassis.moveToPoint(-0, 31.53, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 1}); // Point 2
chassis.turnToHeading(90, 600); // Turn to 90 degrees
liftPiston.set_value(true); // Lift piston up
trapdoorPiston.set_value(true); // Trapdoor piston up

// drive into goal #1
chassis.moveToPoint(18.39, 33.08, 1200, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 3
pros::delay(400);
intake.move_voltage(12000); // Spin intake
pros::delay(400);
chassis.moveToPoint(0.0, 33.48, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 9, .earlyExitRange = 5}); // Point 4
chassis.turnToHeading(135, 500); // Turn to 135 degrees
chassis.moveToPoint(23.82, 9.70, 1000, {.forwards = true, .maxSpeed = 70, .minSpeed = 0}); // Point 5
chassis.moveToPoint(39.92, -6.7, 1000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 6
pros::delay(500);
liftPiston.set_value(false); // Lift piston down
pros::delay(1000);
chassis.moveToPoint(25, 5, 1000, {.forwards = false, .minSpeed = 110, .earlyExitRange = 2}); // Point 7
liftPiston.set_value(true); // Lift piston up
pros::delay(50);
trapdoorPiston.set_value(false); // Trapdoor piston down

chassis.moveToPoint(27.04, -40.70, 2000, {.forwards = true, .maxSpeed = 65, .minSpeed = 0}); // Point 7
chassis.moveToPoint(2.58, -60.16, 1500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
chassis.turnToHeading(90, 700); // Turn to 90 degrees
chassis.moveToPoint(17.90, -60.16, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
intake.move_voltage(-12000); // Spin intake
pros::delay(200);
trapdoorPiston.set_value(true); 
intake.move_voltage(12000);// Trapdoor piston up
pros::delay(1600);
chassis.moveToPoint(5, -59.16, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 11
chassis.turnToHeading(270, 900);
loaderPiston.set_value(true); // Loader piston up
ks::moveStraight(111, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 127}); // Move to goal #2
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