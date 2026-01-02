#include "main.h"
#include "libKW/api.hpp"

void sawp() {
	toggleColourSort = false;
	pros::Task([] {
		intakeMacro("L1");
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(0, 31.55, 1000, true, 127);
	kw::turnToAngle(90, 700); // turn to face loader
	kw::moveToPoint(9.66, 31.55, 1000, true, 90); // Loader #1
	kw::move_raw(3000, 3000);
	pros::delay(200);
	pros::Task([] {
		pros::delay(600);
		intakeMacro("R1");
	});
	kw::moveToPoint(-18.74, 32.5, 1500, false, 127); // long Goal #1
	kw::move_raw(-2000, -2000);
	pros::delay(1000);
	loaderPiston.set_value(false);
	kw::swing(225, 800, true, 90); // turn to face cluster
	pros::Task([] {
		intakeMacro("L1");
		pros::delay(800);
		loaderPiston.set_value(true);
		pros::delay(400);
		loaderPiston.set_value(false);
		pros::delay(800);
		loaderPiston.set_value(true);
	});
	kw::boomerang(-25.75, 8.37, 180, 0.3, 1500, true, 70); // Mid Cluster 1
	kw::turnToAngle(180, 200);
	kw::driveTo(35, 1000, 127, false);
	kw::boomerang(-24.11, -38.70, 135, 0.4, 1000, true, 60); // Mid Cluster 2
	pros::Task([] {
		pros::delay(700);
		intakeMacro("R2");
		pros::delay(1000);
		intakeMacro("L1");
	});
	kw::moveToPoint(-34.12, -27.68, 1000, false, 127); // Mid Goal
	kw::move_raw(-2000, -2000);
	pros::delay(1000);
	kw::moveToPoint(-3.93, -62.81, 1500, true, 127); // Mid to Loader
	kw::turnToAngle(90, 600); // Turning to Loader #2
	kw::moveToPoint(10.94, -62.81, 1000, true, 90); // Loader #2
	kw::move_raw(3000, 3000);
	pros::delay(300);
	pros::Task([] {
		pros::delay(600);
		intakeMacro("R1");
	});
	kw::moveToPoint(-17.38, -62.45, 1000, false, 127); // long Goal #2
	kw::move_raw(-2000, -2000);

}
void legacy_sawp() {
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
	toggleColourSort = false;
	pros::Task([] {
		intakeMacro("L1");
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(0, 31.55, 1000, true, 127);
	kw::turnToAngle(90, 700); // turn to face loader
	kw::moveToPoint(-9.66, 31.55, 1000, true, 90); // Loader #1
	kw::move_raw(3000, 3000);
	pros::delay(200);
	pros::Task([] {
		pros::delay(600);
		intakeMacro("R1");
	});
	kw::moveToPoint(16.74, 31.55, 1500, false, 127); // long Goal #1
	kw::move_raw(-2000, -2000);
	pros::delay(1000);
	loaderPiston.set_value(false);
	kw::moveToPoint(9.01, 21.25, 1500, true, 127);
	kw::turnToAngle(135, 800, true); // turn to face cluster
	pros::Task([] {
		intakeMacro("L1");
		pros::delay(800);
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(25.11, 6.44, 1000, true, 90);
	kw::turnToAngle(135, 1000);
	kw::moveToPoint(33.48, -1.93, 1000, false, 90); // Mid Cluster 1
	kw::move_raw(-2000, -2000);
	intakeMacro("R2");
	pros::delay(2000);
	loaderPiston.set_value(false);
	kw::moveToPoint(12.81, 19.96, 1000, true, 127); // Mid Goal
	kw::turnToAngle(270, 1000);
	kw::moveToPoint(38.63, 19.96, 1000, false, 90); // Loader #2




}

void right_half() { // Right Side Half Solo AWP
toggleColourSort = false;
	pros::Task([] {
		intakeMacro("L1");
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(0, 31.55, 1000, true, 127);
	kw::turnToAngle(270, 700); // turn to face loader
	kw::moveToPoint(9.66, 31.55, 1000, true, 90); // Loader #1
	kw::move_raw(3000, 3000);
	pros::delay(200);
	pros::Task([] {
		pros::delay(600);
		intakeMacro("R1");
	});
	kw::moveToPoint(-16.74, 31.55, 1500, false, 127); // long Goal #1
	kw::move_raw(-2000, -2000);
	pros::delay(1000);
	loaderPiston.set_value(false);
	kw::moveToPoint(-9.01, 21.25, 1500, true, 127);
	kw::turnToAngle(225, 800, true); // turn to face cluster
	pros::Task([] {
		intakeMacro("L1");
		pros::delay(800);
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(-25.11, 6.44, 1000, true, 90);
	pros::delay(200);
	loaderPiston.set_value(false);
	kw::moveToPoint(-33.48, -1.93, 1000, true, 90); // Mid Cluster 1
	intakeMacro("L2");
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