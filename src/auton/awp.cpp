#include "main.h"

void sawp() {
	intakeBottom.move_voltage(12000);
	intakeMiddleLower.move_voltage(12000);
	intakeMiddleUpper.move(-12000);
	//kw::moveToPoint(6, 15, 2000);
	//kw::swing(90, 2000, true, 80);
	kw::moveToPoint(9, 21, 2000, true, 40);
	
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


void left_half() { // Left Side Half Solo AWP

}

void right_half() { // Right Side Half Solo AWP

}

/* LEGACY */

void old_sawp() {

}