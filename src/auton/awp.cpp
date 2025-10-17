#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void sawp() {
	/* travel to loader */
	intakeMacro("L1");
	kw::driveTo(31, 2500, 127); // drive to loader
	loaderPiston.set_value(true);
	kw::turnToAngle(90, 700); // turn to face loader
	pros::delay(100);

	/* get balls from loader */
	kw::driveTo(6, 800, 127, false); // drive into loader
	kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
	pros::delay(750); // stay at matchloader

	/* score on long goal */
	kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	//kw::moveToPoint(-18, 34, 2000, false, 90); // drive backwards into long goal
	pros::Task([] { // prep to score early via task
		kw::driveTo(-23, 1000, 100); // drive backwards into long goal
	});
	pros::delay(800); // ASYNC wait to arrive at goal
	intakeMacro("R1"); // score on long goal
	loaderPiston.set_value(false); // retract matchloader

	/* drive to group of 3 */
	pros::delay(1400);
	kw::driveTo(1.5, 1000, 127, false); // drive fwd from long goal
	kw::turnToAngle(219, 1500); // swing to face group of three #1
	intakeMacro("HOARD_L1"); // intake into hoard
	kw::driveTo(32, 2000, 50);

	/* score on low mid goal */
	kw::turnToAngle(230, 1000); // face mid goal

	pros::Task([] {
		kw::driveTo(13.5, 1500, 80);
	});
	pros::delay(300);
	intakeMacro("HOARD_L2");

	pros::delay(500);
	kw::driveTo(2, 600); // give it a little push into the goal

	/* back away and go to group 3 */
	pros::delay(275);
	intakeMacro("HOARD_L1");
	kw::driveTo(-12.5, 1500); // back away from mid goal

	kw::turnToAngle(183, 1000); // face 2nd group of three

	pros::Task([] {
		kw::driveTo(42.5, 2500); // drive to 2nd group of three
	});
	pros::delay(650); // async wait before putting loader down
	loaderPiston.set_value(true); // lower matchloader to prevent balls from rolling away

	kw::turnToAngle(128.5, 1000); // face long goal
	pros::Task([] {
		pros::delay(600);
		intakeMacro("HOARD_LOAD_R2"); // already start cycling balls up to 3rd stage
	});

	pros::Task([] {
		kw::driveTo(-12, 800); // drive backwards into long goal
		kw::move_raw(-4000, -4000);
	});
	pros::delay(600);
	intakeMacro("HOARD_R2");

}


void left_half() { // Left Side Half Solo AWP

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