#include "main.h"

void right_elim() {
	// libKS MTPoint v0.1
// libKS MTPoint v0.1
// Starting point: (-46.89 in, -7.19 in)
chassis.moveToPoint(0.00, 0.00, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
pros::Task([] {
	liftPiston.set_value(true); // Lift piston up
	pros::delay(500);
	intake.move_voltage(12000); // Spin intake
});
chassis.moveToPoint(11.0, 35.02, 4000, {.forwards = true, .maxSpeed = 42, .minSpeed = 40}); // Point 2
//chassis.moveToPoint(12, 39.90, 1000,{.forwards = true, .maxSpeed = 70, .minSpeed = 2, .earlyExitRange = 0});
chassis.turnToPoint(28, 42, 750); // Turn to 90 degrees
chassis.moveToPoint(27.3, 41.3, 2000, {.forwards = true, .maxSpeed = 110, .minSpeed = 2}); // Point 3
pros::Task([] {
	pros::delay(280);
	loaderPiston.set_value(true); // Loader piston down
	pros::delay(2000);
	loaderPiston.set_value(false); // Loader piston up
});

chassis.moveToPoint(10.11,39.01, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127, .earlyExitRange = 0}); // Point 5
chassis.moveToPoint(17, 13, 1000);
chassis.moveToPoint(31.82, -0.01, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 0}); // Point 6
chassis.turnToHeading(0, 650);
chassis.moveToPoint(31.5012, 16.99, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
pros::Task([] {
	pros::delay(800);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake

});
pros::delay(2700);
trapdoorPiston.set_value(false); // Trapdoor piston down
chassis.moveToPoint(32.802, 5, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 8
chassis.turnToHeading(180, 700, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100}); // Turn to 180 degrees
loaderPiston.set_value(true); // Loader piston down
chassis.moveToPoint(32.807, -13.1, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
// chassis.moveToPoint(39.92, 18.67, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
pros::delay(1050);
chassis.moveToPoint(31.1002, 5, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 10
chassis.turnToHeading(0, 700, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100});
chassis.moveToPoint(31.30012, 17.07, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7

pros::Task([] {

	loaderPiston.set_value(false); // Loader piston up
	pros::delay(100);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	scoreOwnColour(4000);
});
}

void left_elim() {
	// libKS MTPoint v0.1
// libKS MTPoint v0.1
// Starting point: (-46.89 in, -7.19 in)
chassis.moveToPoint(0, 0.00, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
pros::Task([] {
	liftPiston.set_value(true); // Lift piston up
	pros::delay(500);
	intake.move_voltage(12000); // Spin intake
});
chassis.moveToPoint(-12, 36.02, 4000, {.forwards = true, .maxSpeed = 47, .minSpeed = 40}); // Point 2
//chassis.moveToPoint(-12, 39.90, 1000,{.forwards = true, .maxSpeed = 70, .minSpeed = 2, .earlyExitRange = 0});
chassis.turnToPoint(29, 40, 750); // Turn to 90 degrees
chassis.moveToPoint(-26.8, 40.7, 2000, {.forwards = true, .maxSpeed = 110, .minSpeed = 2}); // Point 3
pros::Task([] {
	pros::delay(180);
	loaderPiston.set_value(true); // Loader piston down
	pros::delay(2000);
	loaderPiston.set_value(false); // Loader piston up
});
pros::delay(600);
chassis.moveToPoint(-10.11,39.01, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127, .earlyExitRange = 0}); // Point 5
chassis.moveToPoint(-17, 13, 1000);
chassis.moveToPoint(-31.82, -0.01, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 0}); // Point 6
chassis.turnToPoint(-31, 16, 700, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100});
chassis.moveToPoint(-31.3012, 16.09, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
pros::Task([] {
	pros::delay(800);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake

});
pros::delay(2700);
trapdoorPiston.set_value(false); // Trapdoor piston down
chassis.moveToPoint(-32.802, 5, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 8
chassis.turnToHeading(180, 700, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100}); // Turn to 180 degrees
loaderPiston.set_value(true); // Loader piston down
chassis.moveToPoint(-32.807, -13.1, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
// chassis.moveToPoint(-39.92, 18.67, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
pros::delay(1050);
chassis.moveToPoint(-31.1002, 5, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 10
chassis.turnToPoint(-31, 16, 700, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100});
chassis.moveToPoint(-30.80012, 16.07, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7

pros::Task([] {

	loaderPiston.set_value(false); // Loader piston up
	pros::delay(100);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	scoreOwnColour(4000);
});
    
}