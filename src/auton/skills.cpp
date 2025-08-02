#include "deviceGlobals.hpp"
#include "libKS/drivetrain/chassis.hpp"
#include "main.h"
void skills() { /* NO COLOUR SORT */
 chassis.moveToPoint(0.00, 0.00, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
liftPiston.set_value(true); // Lift piston up
chassis.moveToPoint(-4, 31.83, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 2
chassis.turnToHeading(90, 1000); // Turn to 90 degrees
pros::Task([] {
	loaderPiston.set_value(true); // Loader piston up
	intake.move_voltage(12000); // Spin intake
});
chassis.moveToPoint(10.915, 32.9, 1200, {.forwards = true, .maxSpeed = 73, .minSpeed = 73}); // Point 3
pros::delay(4050);
chassis.moveToPoint(-4.15, 32.10, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 4
chassis.turnToHeading(270, 1000); // Turn to 270 degrees
pros::Task([] {
	loaderPiston.set_value(false); // Loader piston down
	intake.move_voltage(-12000); // Reverse intake
});
pros::delay(100);
intake.move_voltage(12000); // Reverse intake
chassis.moveToPoint(-16, 31.83, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 4
pros::delay(400);
chassis.turnToHeading(270, 1000);
trapdoorPiston.set_value(true); // Trapdoor piston up
intake.move_voltage(-12000); // Stop intake
pros::delay(50);
intake.move_voltage(12000); // Reverse intake
pros::delay(4000);
trapdoorPiston.set_value(true); // Trapdoor piston down
chassis.moveToPoint(-5.45, 30.83, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127}); // Point 5
pros::Task([] {
    trapdoorPiston.set_value(false); // Trapdoor piston down
    intake.move_voltage(12000); // Reverse intake
});

chassis.turnToHeading(225, 1000); // Turn to 225 degrees
chassis.moveToPoint(-22.83, 9.66, 3000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Point 6
chassis.moveToPoint(-4.15, 32.10, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Point 4
chassis.moveToPoint(-16, 31.73, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 4
pros::Task([] {
	pros::delay(800);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake 5
});
pros::delay(4000);
chassis.moveToPoint(8.45, 30.83, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127}); // Point 5
chassis.turnToHeading(180, 1000);
chassis.moveToPoint(11, 10, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7

pros::delay(1000);
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(20, 5, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 127}); // Point 8
ks::moveStraight(-0.2, 2000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0});
chassis.turnToHeading(180, 1000);
ks::moveStraight(17, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 127});
pros::Task([] {
pros::delay(200);
   loaderPiston.set_value(true); // Loader piston up
   odomLiftPiston.set_value(true); // Odom lift piston down
   pros::delay(150);
});
ks::moveRaw(12000, 2000);
}