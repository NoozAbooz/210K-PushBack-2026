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
chassis.moveToPoint(8.81, 32.82, 5000, {.forwards = true, .maxSpeed = 40, .minSpeed = 40, .earlyExitRange = 10}); // Point 2
chassis.moveToPoint(12, 39.89, 1000);
chassis.turnToHeading(90, 900); // Turn to 90 degrees
chassis.moveToPoint(27.5, 42, 1300, {.forwards = true, .maxSpeed = 70, .minSpeed = 0}); // Point 3
pros::Task([] {
	pros::delay(300);
	loaderPiston.set_value(true); // Loader piston down
	pros::delay(2000);
	loaderPiston.set_value(false); // Loader piston up
});
chassis.moveToPoint(10.11,39.01, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127, .earlyExitRange = 5}); // Point 5
chassis.moveToPoint(17, 13, 1000);
chassis.moveToPoint(30.92, -0.01, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 1, .earlyExitRange = 12}); // Point 6
chassis.turnToHeading(0, 700);
chassis.moveToPoint(30.82, 18.47, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
pros::Task([] {
	pros::delay(800);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake
});
pros::delay(2600);
trapdoorPiston.set_value(false); // Trapdoor piston down
chassis.moveToPoint(30.52, 5, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 8
chassis.turnToHeading(180, 700); // Turn to 180 degrees
loaderPiston.set_value(true); // Loader piston down
chassis.moveToPoint(31.27, -12.16, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
// chassis.moveToPoint(39.92, 18.67, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
pros::delay(1200);
chassis.moveToPoint(31.72, 5, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 10
chassis.turnToHeading(0, 700);
chassis.moveToPoint(30.812, 18.47, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
pros::Task([] {
	loaderPiston.set_value(false); // Loader piston up
	pros::delay(200);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake
	scoreOwnColour(4000);
});

}

void left_elim() {

    
}