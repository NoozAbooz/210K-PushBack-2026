#include "deviceGlobals.hpp"
#include "libKS/drivetrain/chassis.hpp"
#include "main.h"
void skills() { /* NO COLOUR SORT */
   chassis.setPose(0, 0, 0); // Reset odom position to (0, 0, 0)    
   chassis.moveToPoint(-3, 28.3, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Move forward 32 inches
   chassis.turnToHeading(90, 1000); // Turn to 90 degrees
      pros::Task([] {
       loaderPiston.set_value(true); // Lift piston up
       intake.move_voltage(12000); // Spin intake
       liftPiston.set_value(true); // Lift piston down
   });
ks::moveStraight(12, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 127}); // Move forward 12 inches
   pros::delay(2000);
   ks::moveStraight(-12.8, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Move backward 12 inches
   chassis.turnToHeading(270, 1000); // Turn to 270 degrees
   chassis.moveToPoint(-17.4, 31, 1000);
pros::Task([] {
    loaderPiston.set_value(false);
	pros::delay(800);
	trapdoorPiston.set_value(true); // Trapdoor piston up
	intake.move_voltage(-12000); // Reverse intake
	pros::delay(150);
	intake.move_voltage(12000); // Spin intake
});
pros::delay(3000);
trapdoorPiston.set_value(false); // Trapdoor piston down
chassis.moveToPoint(0, 33, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Move backward to (0, 33)
chassis.moveToPoint(-28, 5, 3000, {.forwards = true, .maxSpeed = 40, .minSpeed = 0}); // Move to (28, 5)
chassis.moveToPoint(0, 33, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 110}); // Move backward to (0, 33)
chassis.turnToHeading(270, 1000); // Turn to 270 degrees
chassis.moveToPoint(-17.4, 33, 1000);
pros::Task([] {
    pros::delay(500);
    trapdoorPiston.set_value(true); // Trapdoor piston up
    intake.move_voltage(-12000); // Reverse intake
    pros::delay(350);
    intake.move_voltage(12000); // Spin intake
});
pros::delay(3000);
// chassis.moveToPoint(0, 31, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}); // Move backward to (0, 33)
// chassis.moveToPoint(0, 10, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Move backward to (0, 10)

// chassis.moveToPoint(-96, 6,  1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Move forward to (0, 30.5)
}