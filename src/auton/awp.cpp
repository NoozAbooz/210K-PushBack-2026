#include "main.h"
#include "libKW/api.hpp"

void sawp() {
	toggleColourSort = false;

	/* travel to loader */
	intakeMacro("L1");
	kw::driveTo(31.0, 2500, 127); // drive to loader
	loaderPiston.set_value(true);
	kw::turnToAngle(90, 700); // turn to face loader
	pros::delay(50);

	/* get balls from loader */
	kw::driveTo(11.5,800, 60); // drive into loader
	kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
	pros::delay(250); // stay at matchloader

	/* score on long goal */
	//kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	//kw::moveToPoint(-18, 34, 2000, false, 90); // drive backwards into long goal
	double turn_angle = kw::normalize_target(kw::to_deg(atan2(-20 - kw::x_pos, 31 - kw::y_pos))) + 180;
	kw::turnToAngle(turn_angle, 1000); // turn towards long goal

	pros::Task([] { // prep to score early via task
		kw::moveToPoint(-20, 32.0, 1000, false, 127); // drive backwards into long goal
		//kw::driveTo(-33, 1500); // drive backwards into long goal
	});
	pros::delay(500); // ASYNC wait to arrive at goal
	intakeMacro("R1"); // score on long goal
	loaderPiston.set_value(false); // retract matchloader

	// /* drive to group of 3 */
	pros::delay(1500);
	// kw::driveTo(1.5, 1000, 127, false); // drive fwd from long goal
	kw::turnToAngle(225, 800); // swing to face group of three #1
	pros::Task([] {
		intakeMacro("L1"); // intake into hoard
		toggleColourSort = false;
	});

	kw::driveTo(8.3, 1000, 127, false);
	kw::turnToAngle(180, 1000);
	kw::driveTo(30, 1500, 127, false);
	loaderPiston.set_value(true); // lower matchloader to prevent balls from rolling away
	kw::turnToAngle(140, 1000);
	//kw::correct_angle = kw::normalize_target(140.6);
	kw::moveToPoint(-38.1, -24, 1000, false);
	pros::Task([] {
		intakeMacro("R2"); // intake into hoard4
			intakeTop.move_voltage(-5000);
			pros::delay(725);
		intakeMacro("L1");
	});
	pros::Task([] {
		double turn_angle = kw::normalize_target(kw::to_deg(atan2(-3.5 - kw::x_pos, -61.95 - kw::y_pos)));
		kw::turnToAngle(turn_angle, 1000);
	});
	pros::delay(750);

	kw::moveToPoint(-3.5, -63.25 , 1500, true); // 
	pros::delay(50);
	kw::correct_angle = kw::normalize_target(152);
	toggleColourSort = true;
	kw::turnToAngle(90, 600); // face long goal
	kw::driveTo(15, 800, 90); // drive into loader
	kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
	pros::delay(450);
		turn_angle = kw::normalize_target(kw::to_deg(atan2(-23 - kw::x_pos, -63 - kw::y_pos))) + 180;
		kw::turnToAngle(turn_angle, 1000);
		
		kw::moveToPoint(-23, -63.74, 1000, false); // drive backwards into long goal
		//kw::driveTo(-33, 1000);

		intakeMacro("R1");
		wingPiston.set_value(true); // deploy wings for driver
		kw::move_raw(-6000, -6000);

		wingStatus = true;
		loaderStatus = true;
}


void left_half() { // Left Side Half Solo AWP
	intakeMacro("L1");
    wingPiston.set_value(true);
    kw::driveTo(28.5, 2000, 60, false);
    kw::moveToPoint(-15, 49, 1000);
    pros::delay(200);
    kw::moveToPoint(-15, 22, 1000, false, 127, false);
    kw::turnToAngle(236, 1000);
    kw::moveToPoint(-30, 25, 1000, false, 127, false);
	kw::moveToPoint(-25.59, 32.4, 1000, false);
	kw::move_raw(-7000, -7000);
    pros::delay(300);
    intakeMacro("R1");
	loaderPiston.set_value(true);
	pros::delay(1500);
	intakeMacro("L1");
	kw::moveToPoint(-32.07, 2.08, 1000, true, 80);
	kw::move_raw(5000, 5000);
	pros::delay(400);
	kw::driveTo(-10, 1000);
	kw::turnToAngle(239, 1000);
	kw::moveToPoint(15, 36, 1000, false, 127);
}

void right_half() { // Right Side Half Solo AWP

}

/* LEGACY */

// void nooz_sawp() {
// 	intakeMacro("L1");
// 	kw::driveTo(32, 2500, 127); // drive to loader
// 	loaderPiston.set_value(true);
// 	kw::turnToAngle(90, 700); // turn to face loader
// 	pros::delay(100);

// 	kw::driveTo(6, 800, 127, false); // drive into loader
// 	kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
// 	pros::delay(900);

// 	kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
// 	//kw::moveToPoint(-18, 34, 2000, false, 90); // drive backwards into long goal
// 	pros::Task([] {
// 		kw::driveTo(-23, 1000); // drive backwards into long goal
// 	});

// 	pros::delay(800); // wait to arrive at goal
// 	intakeMacro("R1"); // score on long goal
// 	loaderPiston.set_value(false); // retract matchloader

// 	pros::delay(800);
// 	kw::driveTo(1, 1000, 127, false);
// 	kw::turnToAngle(220, 1500); // swing to face group of three #1
// 	intakeMacro("L1"); // intake into hoard
// 	kw::driveTo(30, 1500, 80);

// 	kw::turnToAngle(180, 1000);
// 	intakeMacro("HOARD_L1");

// 	pros::Task([] {
// 		kw::driveTo(48, 1000); // drive backwards into long goal
// 	});
// 	pros::delay(1000);
// 	loaderPiston.set_value(true); // loader down to prevent balls from rolling away

// 	// // go to upper goal
// 	// kw::driveTo(-12, 1000);
// 	// kw::turnToAngle(270, 1000);
// 	// kw::moveToPoint(-30, 14, 1, 3000);
// 	// //driveTo(48, 4000);

// 	// kw::turnToAngle(-140, 1000);
// 	// kw::driveTo(-15, 1000);
// 	// pros::delay(2000);

// 	// // loader
// 	// kw::moveToPoint(-51, -7, 1, 3000);
// 	// kw::turnToAngle(180, 1000);
// 	// kw::driveTo(5, 1000);
// 	// pros::delay(1000);

// 	// // long goal
// 	// kw::driveTo(-22, 2000);
// }