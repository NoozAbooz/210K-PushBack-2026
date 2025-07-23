#include "main.h"

void sawp() {
// libKS MTPoint v0.1
// Starting point: (54.83 in, 12.77 in)
chassis.moveToPoint(0.00, 0.00, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
liftPiston.set_value(true); // Lift piston up
chassis.moveToPoint(-5.00, 31.83, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 2
chassis.turnToHeading(90, 1000); // Turn to 90 degrees
loaderPiston.set_value(true); // Loader piston up
intake.move_voltage(12000); // Spin intake
chassis.moveToPoint(2.215, 30.83, 1200, {.forwards = true, .maxSpeed = 127, .minSpeed = 127}); // Point 3
pros::delay(1500);
chassis.moveToPoint(-4.15, 32.00, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 4
chassis.turnToHeading(270, 1000); // Turn to 270 degrees
loaderPiston.set_value(false); // Loader piston down
intake.move_voltage(12000); // Reverse intake
chassis.moveToPoint(-23.40, 34.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 4
pros::delay(500);
trapdoorPiston.set_value(true); // Trapdoor piston up
intake.move_voltage(0); // Stop intake
pros::delay(500);
intake.move_voltage(12000); // Reverse intake
pros::delay(1000);
chassis.moveToPoint(-17.45, 30.83, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127}); // Point 5
chassis.turnToHeading(225, 1000); // Turn to 225 degrees
chassis.moveToPoint(-31.83, 5.66, 3000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 6
chassis.moveToPoint(-48.42, -6.72, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
pros::delay(500);
intake.move_voltage(-7000); // Stop intake
chassis.turnToHeading(225, 1000); // Turn to 0 degrees
pros::delay(1000);
chassis.moveToPoint(-31, 3, 1000, {.forwards = false});
chassis.moveToPoint(-31.55, -37.34, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
chassis.turnToHeading(315, 1000);
chassis.moveToPoint(-42.49, -29.40, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
// chassis.moveToPoint(-4.51, -58.59, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
// chassis.moveToPoint(7.73, -59.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 11
// chassis.moveToPoint(-27.04, -59.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 12

}

void left_half() { // Left Side Half Solo AWP

}

void right_half() { // Right Side Half Solo AWP

}