#include "main.h"

void right_elim() {
// libKS MTPoint v0.1
// Starting point: (-46.89 in, -7.19 in)
chassis.moveToPoint(0.00, 0.00, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
pros::Task([] {
	liftPiston.set_value(true); // Lift piston up
	pros::delay(500);
	intake.move_voltage(12000); // Spin intake
});
chassis.moveToPoint(9.81, 32.82, 4000, {.forwards = true, .maxSpeed = 45, .minSpeed = 40, .earlyExitRange = 10}); // Point 2
chassis.moveToPoint(12, 39.78, 1000,{.forwards = true, .maxSpeed = 70, .minSpeed = 2, .earlyExitRange = 0});
chassis.turnToHeading(90, 650); // Turn to 90 degrees
chassis.moveToPoint(27.5, 42.0, 1000, {.forwards = true, .maxSpeed = 70, .minSpeed = 2}); // Point 3
pros::Task([] {
	pros::delay(300);
	loaderPiston.set_value(true); // Loader piston down
	pros::delay(2000);
	loaderPiston.set_value(false); // Loader piston up
});

chassis.moveToPoint(10.11,39.01, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127, .earlyExitRange = 5}); // Point 5
chassis.moveToPoint(17, 13, 1000);
chassis.moveToPoint(33.82, -0.01, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 0}); // Point 6
chassis.turnToHeading(0, 650);
chassis.moveToPoint(32.812, 17.87, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
pros::Task([] {
	pros::delay(800);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake

});
pros::delay(2650);
trapdoorPiston.set_value(false); // Trapdoor piston down
chassis.moveToPoint(33.82, 5, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 8
chassis.turnToHeading(180, 700, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100}); // Turn to 180 degrees
loaderPiston.set_value(true); // Loader piston down
chassis.moveToPoint(33.767, -12.86, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
// chassis.moveToPoint(39.92, 18.67, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
pros::delay(1250);
chassis.moveToPoint(32.1002, 5, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 10
chassis.turnToHeading(0, 700, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100});
chassis.moveToPoint(32.2012, 18.07, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
pros::Task([] {
	loaderPiston.set_value(false); // Loader piston up
	pros::delay(100);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake
	//scoreOwnColour(4000);
    chassis.turnToHeading(0, 700);
});

}

void left_elim() {

    
}