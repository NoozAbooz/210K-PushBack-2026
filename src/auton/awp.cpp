#include "deviceGlobals.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void sawp() {
	pros::Task([]{
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		intakeMiddleUpper.move(-12000);
		loaderPiston.set_value(true);
	});

	kw::boomerang(14, 25, 90, 0.5, 4000, true, 80);
	pros::Task([] {
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(15.9, 25.4, 1000);
	pros::delay(500);
	kw::moveToPoint(-14.5, 25.7, 1000, false);
	pros::Task([]{
		intakeBottom.move_voltage(-6000);
		intakeMiddleLower.move_voltage(12000);
		intakeMiddleUpper.move(12000);
		intakeTop.move_voltage(12000);
		pros::delay(500);
		loaderPiston.set_value(false);
	});
	pros::delay(3000);
	kw::moveToPoint(-10, 15, 1000);
	kw::boomerang(-25, 0, 225, 0.7, 3000, true, 90);
	pros::Task([]{
		intakeBottom.move_voltage(12000);
	intakeMiddleLower.move_voltage(12000);
	intakeMiddleUpper.move(-12000);
	intakeTop.move_voltage(00);
	loaderPiston.set_value(true);
	});
	pros::Task([]{
		loaderPiston.set_value(false);
	});
	kw::moveToPoint(-24, -20, 1000);
	
	kw::moveToPoint(-28, -45, 1000);
	pros::Task([]{
		pros::delay(100);
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		intakeMiddleUpper.move(12000);
		loaderPiston.set_value(true);
	});
	pros::delay(500);
	kw::turnToAngle(135, 1000);
	kw::moveToPoint(-33.2, -34, 1000, false);
	pros::Task([]{
		pros::delay(3000);
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		intakeMiddleUpper.move(12000);
		intakeTop.move_voltage(-12000);
		pros::delay(500);
		loaderPiston.set_value(false);
	});
	// kw::driveTo(15, 1000);
	// pros::delay(2000);

	// // bgo to upper goal
	// kw::driveTo(-12, 1000);
	// kw::turnToAngle(270, 1000);
	// kw::moveToPoint(-30, 14, 1, 3000);
	// //driveTo(48, 4000);

	// kw::turnToAngle(-140, 1000);
	// kw::driveTo(-15, 1000);
	// pros::delay(2000);

	// // loader
	// kw::moveToPoint(-51, -7, 1, 3000);
	// kw::turnToAngle(180, 1000);
	// kw::driveTo(5, 1000);
	// pros::delay(1000);

	// // long goal
	// kw::driveTo(-22, 2000);
}


void left_half() { // Left Side Half Solo AWP

}

void right_half() { // Right Side Half Solo AWP

}

/* LEGACY */

void sawp_12() {
	intakeBottom.move_voltage(8000);
	intakeMiddleLower.move_voltage(12000);
	intakeMiddleUpper.move(-3000);
	// kw::moveToPoint(6, 15, 2000);
	// kw::swing(90, 2000, true, 40);
	kw::moveToPoint(5, 14, 2000, true, 127, false);
	kw::moveToPoint(9, 21, 2000, true, 20);

	//kw::swing(310, 2000);

	// kw::turnToAngle(310, 1000);
	// kw::driveTo(15, 1000);
	// pros::delay(2000);

	// // bgo to upper goal
	// kw::driveTo(-12, 1000);
	// kw::turnToAngle(270, 1000);
	// kw::moveToPoint(-30, 14, 1, 3000);
	// //driveTo(48, 4000);

	// kw::turnToAngle(-140, 1000);
	// kw::driveTo(-15, 1000);
	// pros::delay(2000);

	// // loader
	// kw::moveToPoint(-51, -7, 1, 3000);
	// kw::turnToAngle(180, 1000);
	// kw::driveTo(5, 1000);
	// pros::delay(1000);

	// // long goal
	// kw::driveTo(-22, 2000);
}