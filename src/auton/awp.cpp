#include "deviceGlobals.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void sawp() {
	pros::Task([] {
		loaderPiston.set_value(true);
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		intakeMiddleUpper.move_voltage(12000);
	});
	kw::boomerang(19, 24.5, 90, 0.5, 4000, true, 90, false);
	pros::delay(600);
	//pros::delay(800);
	kw::moveToPoint(-16, 26, 1500, false, 90);
	pros::Task([] {
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		intakeMiddleUpper.move_voltage(12000);
		intakeTop.move_voltage(12000);
		pros::delay(500);
		loaderPiston.set_value(false);
	});
	pros::delay(1600);
	kw::moveToPoint(-5, 26, 1000, true, 127, false);
	kw::boomerang(-23, 0, 218, 0.6, 2000, true, 90, false);
	pros::Task([] {
		//pros::delay(200);
		loaderPiston.set_value(true);
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		intakeMiddleUpper.move_voltage(-12000);
		intakeTop.move_voltage(0);
	});
	// pros::delay(500);
	// kw::boomerang(-24, -46, 180, 0.2, 2000, true, 90, true);
	// pros::Task([] {
	// 	pros::delay(500);
	// 	loaderPiston.set_value(false);
	// 	pros::delay(1500);
	// 	loaderPiston.set_value(true);
	// 	intakeBottom.move_voltage(-4000);
	// 	intakeMiddleLower.move_voltage(12000);
	// 	intakeMiddleUpper.move_voltage(12000);
	// 	intakeTop.move_voltage(-8000);
	// });
	// kw::boomerang(-35, -34, 135, 0.4, 2000, false, 90);
	// pros::delay(1500);
	// kw::boomerang(14, -70, 90, 0.6, 3000, true);
	// pros::Task([] {
	// 	intakeBottom.move_voltage(12000);
	// 	intakeMiddleLower.move_voltage(12000);
	// 	intakeMiddleUpper.move_voltage(-12000);
	// });
	// pros::delay(700);
	// kw::moveToPoint(-18, -69, 2000, false, 90);
	// 	pros::Task([] {
	// 	intakeBottom.move_voltage(-4000);
	// 	intakeMiddleLower.move_voltage(12000);
	// 	intakeMiddleUpper.move_voltage(12000);
	// 	intakeTop.move_voltage(12000);
	// });

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