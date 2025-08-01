#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKS/drivetrain/chassis.hpp"
#include "main.h"
#include "pros/colors.hpp"
#include "pros/rtos.hpp"
#include <sys/_intsup.h>

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
chassis.moveToPoint(16.59, 32.58, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 120, .earlyExitRange = 0}); // Point 3
pros::delay(550);
chassis.moveToPoint(6, 32.78, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 8, .earlyExitRange = 0}); // Point 4
chassis.moveToPoint(24.242,6., 2000, {.forwards = true, .maxSpeed = 65, .minSpeed = 45}); // Point 5
//ks::moveStraight(15, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0});
chassis.moveToPoint(34.71, -1.3, 1200, {.forwards = true, .maxSpeed = 60, .minSpeed = 70}); // Point 6
chassis.turnToHeading(135, 300);
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
chassis.moveToPoint(25.700, -41.0, 2000, {.forwards = true, .maxSpeed = 65, .minSpeed = 0, .earlyExitRange = 0}); // Point 7
chassis.moveToPoint(3.58, -61.06, 1500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
chassis.turnToPoint(16, -60.6, 700); // Turn to 90 degrees
chassis.moveToPoint(15.510, -60.57, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
pros::Task([] {
	pros::delay(300);
	intake.move_voltage(-12000); // Spin intake
	pros::delay(125);
	trapdoorPiston.set_value(true);
	intake.move_voltage(12000); // Trapdoor piston up
});
pros::delay(1650);
chassis.moveToPoint(10.2, -61.9, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 0}); // Point 11
// ks::moveStraight(-12, 800, {.forwards = false, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 1.5}); // Point 11
pros::Task([] {
	pros::delay(300);
	loaderPiston.set_value(true);
	pros::delay(1300);
	trapdoorPiston.set_value(false); // dropdown match loader
});
chassis.turnToPoint(-11, -60.9, 900, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE}, false);
chassis.moveToPoint(-10.7, -60.856, 1500, {.forwards = true, .maxSpeed = 115, .minSpeed = 110}); // Point 11
pros::delay(1300);
//ks::moveStraight(30, 1500, {.forwards = false, .maxSpeed = 40, .minSpeed = 0}); // Point 12
//chassis.moveToPoint(-10.9, -61.6, 800, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 12
//ks::moveStraight(2, 200, {.forwards = true, .maxSpeed = 5, .minSpeed = 0});
ks::moveStraight(-2, 200, {.forwards = false, .maxSpeed = 30, .minSpeed = 250});

//chassis.moveToPoint(-15.10, -61.66, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
}



void left_half() { // Left Side Half Solo AWP

chassis.moveToPoint(0, 0.00, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
liftPiston.set_value(true); // Lift piston up
chassis.moveToPoint(4, 31.63, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 2
chassis.turnToHeading(270, 1000); // Turn to 90 degrees
pros::Task([] {
	loaderPiston.set_value(true); // Loader piston up
	intake.move_voltage(12000); // Spin intake
});
chassis.moveToPoint(-10.915, 32.53, 1200, {.forwards = true, .maxSpeed = 73, .minSpeed = 73}); // Point 3
pros::delay(1550);
chassis.moveToPoint(4.15, 31.90, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 4
chassis.turnToHeading(90, 1000); // Turn to 270 degrees
pros::Task([] {
	loaderPiston.set_value(false); // Loader piston down
	intake.move_voltage(-12000); // Reverse intake
});
pros::delay(100);
intake.move_voltage(12000); // Reverse intake
chassis.moveToPoint(16, 32.03, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 4
pros::delay(400);
chassis.turnToHeading(90, 1000);
trapdoorPiston.set_value(true); // Trapdoor piston up
intake.move_voltage(-12000); // Stop intake
pros::delay(50);
scoreOwnColour(2000);
trapdoorPiston.set_value(true); // Trapdoor piston down
chassis.moveToPoint(5.45, 30.83, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127}); // Point 5
intake.move_voltage(12000); // Reverse intake
pros::Task([] {
	trapdoorPiston.set_value(false); // Trapdoor piston down
});
chassis.turnToHeading(135, 1000); // Turn to 225 degrees
chassis.moveToPoint(21.83, 10.66, 3000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 6
chassis.moveToPoint(35.32, -4.02, 2000, {.forwards = true, .maxSpeed = 60, .minSpeed = 0}); // Point 7
chassis.turnToHeading(135, 1000); // Turn to 0 degrees
pros::Task([] {
	pros::delay(700);
	liftPiston.set_value(false);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake

});
}

void right_half() { // Right Side Half Solo AWP
/// libKS MTPoint v0.1
// Starting point: (54.83 in, 12.77 in)
chassis.moveToPoint(0.00, 0.00, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
liftPiston.set_value(true); // Lift piston up
chassis.moveToPoint(-4, 31.83, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 2
chassis.turnToHeading(90, 1000); // Turn to 90 degrees
pros::Task([] {
	loaderPiston.set_value(true); // Loader piston up
	intake.move_voltage(12000); // Spin intake
});
chassis.moveToPoint(10.915, 31.93, 1200, {.forwards = true, .maxSpeed = 73, .minSpeed = 73}); // Point 3
pros::delay(1550);
chassis.moveToPoint(-4.15, 32.10, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 4
chassis.turnToHeading(270, 1000); // Turn to 270 degrees
pros::Task([] {
	loaderPiston.set_value(false); // Loader piston down
	intake.move_voltage(-12000); // Reverse intake
});
pros::delay(100);
intake.move_voltage(12000); // Reverse intake
chassis.moveToPoint(-16, 31.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 4
pros::delay(400);
chassis.turnToHeading(270, 1000);
trapdoorPiston.set_value(true); // Trapdoor piston up
intake.move_voltage(-12000); // Stop intake
pros::delay(50);
scoreOwnColour(2000);
trapdoorPiston.set_value(true); // Trapdoor piston down
chassis.moveToPoint(-5.45, 30.83, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127}); // Point 5
intake.move_voltage(12000); // Reverse intake
pros::Task([] {
	pros::delay(3700);
	intake.move_voltage(0); // Stop intake
});
chassis.turnToHeading(225, 1000); // Turn to 225 degrees
chassis.moveToPoint(-21.83, 10.66, 3000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 6
chassis.moveToPoint(-35.52, -4.92, 1000, {.forwards = true, .maxSpeed = 60, .minSpeed = 0}); // Point 7
chassis.turnToHeading(225, 1000); // Turn to 0 degrees
pros::delay(400);
intake.move_voltage(-7300); // Stop intake
pros::delay(500);
// chassis.turnToHeading(225, 1000); // Turn to 0 degrees
// pros::delay(2500);
// chassis.moveToPoint(-31, 3, 1000, {.forwards = false});
// chassis.moveToPoint(-31.55, -37.34, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
// chassis.turnToHeading(315, 1000);
// chassis.moveToPoint(-42.49, -29.40, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
// // chassis.moveToPoint(-4.51, -58.59, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10
// chassis.moveToPoint(7.73, -59.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 11
// chassis.moveToPoint(-27.04, -59.23, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 12}
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