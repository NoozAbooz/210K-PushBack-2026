#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include <sys/_intsup.h>

void sawp() {
	toggleColourSort = true;

	/* travel to loader */
	intakeMacro("L1");
	kw::driveTo(31.7, 2500, 127); // drive to loader
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
	pros::Task([] { // prep to score early via task
		kw::moveToPoint(-20, 34.0, 1000, false, 127); // drive backwards into long goal
		//kw::driveTo(-33, 1500); // drive backwards into long goal
	});
	pros::delay(500); // ASYNC wait to arrive at goal
	intakeMacro("R1"); // score on long goal
	loaderPiston.set_value(false); // retract matchloader

	// /* drive to group of 3 */
	pros::delay(1600);
	// kw::driveTo(1.5, 1000, 127, false); // drive fwd from long goal
	kw::turnToAngle(225, 800); // swing to face group of three #1
	pros::Task([] {
		intakeMacro("L1"); // intake into hoard
		toggleColourSort = false;
	});

	kw::driveTo(8.3, 1000, 127, false);
	kw::turnToAngle(178, 1000);
	kw::driveTo(30, 1500, 127, false);
	loaderPiston.set_value(true); // lower matchloader to prevent balls from rolling away
	kw::turnToAngle(140, 1000);
	//kw::correct_angle = kw::normalize_target(140.6);
	kw::moveToPoint(-37.4, -23.0, 1000, false);
		pros::Task([] {
		intakeMacro("R2"); // intake into hoard4
			intakeTop.move_voltage(-6500);
			pros::delay(850);
		intakeMacro("L1");
	});
	pros::delay(850);
	kw::moveToPoint(-3.5, -61.15 , 1500, true); // drive backwards into long goal
	pros::delay(50);
	kw::correct_angle = kw::normalize_target(152);
	toggleColourSort = true;
	kw::turnToAngle(90, 600); // face long goal
	kw::driveTo(15, 800, 90); // drive into loader
	kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
	pros::delay(650);
	pros::Task([] {
		kw::moveToPoint(-23, -59.74	, 1000, false); // drive backwards into long goal
		//kw::driveTo(-33, 1000);
		intakeMacro("R1");
		wingPiston.set_value(true); // deploy wings
	});


	// /* score on low mid goal */
	// kw::turnToAngle(228, 1000); // face mid goal

	// pros::Task([] {
	// 	kw::driveTo(13, 1500, 80);
	// });
	// pros::delay(350);
	// intakeMacro("HOARD_L2");

	// pros::delay(600);
	// kw::driveTo(2, 600); // give it a little push into the goal

	// /* back away and go to group 3 */
	// pros::delay(275);
	// intakeMacro("HOARD_L1");
	// kw::driveTo(-12.5, 1500); // back away from mid goal

	// kw::turnToAngle(183, 1000); // face 2nd group of three

	// pros::Task([] {
	// 	kw::driveTo(42.5, 2500); // drive to 2nd group of three
	// });
	// pros::delay(650); // async wait before putting loader down
	// loaderPiston.set_value(true); // lower matchloader to prevent balls from rolling away

	// kw::turnToAngle(127, 1000); // face long goal
	// pros::Task([] {
	// 	pros::delay(600);
	// 	intakeMacro("HOARD_LOAD_R2"); // already start cycling balls up to 3rd stage
	// });

	// pros::Task([] {
	// 	kw::driveTo(-12, 800); // drive backwards into long goal
	// 	kw::move_raw(-4000, -4000);
	// });
	// pros::delay(600);
	// intakeMacro("HOARD_R2");

}


void left_half() { // Left Side Half Solo AWP
	toggleColourSort = true;

	/* travel to loader */
	intakeMacro("L1");
	kw::driveTo(31.7, 2500, 127); // drive to loader
	loaderPiston.set_value(true);
	kw::turnToAngle(270, 700); // turn to face loader
	pros::delay(50);

	/* get balls from loader */
	kw::driveTo(11.4,800, 60); // drive into loader
	kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
	pros::delay(250); // stay at matchloader

	/* score on long goal */
	//kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	//kw::moveToPoint(18, 34, 2000, false, 90); // drive backwards into long goal
	pros::Task([] { // prep to score early via task
		kw::moveToPoint(22, 31.0, 3000, false, 127); // drive backwards into long goal
		kw::move_raw(-6000, -6000);

		//kw::driveTo(-33, 1500); // drive backwards into long goal
	});
	pros::delay(500); // ASYNC wait to arrive at goal
	intakeMacro("R1"); // score on long goal
	loaderPiston.set_value(false); // retract matchloader

	// /* drive to group of 3 */
	pros::delay(2000);
	// kw::driveTo(1.5, 1000, 127, false); // drive fwd from long goal
	kw::driveTo(15, 1000);
	kw::turnToAngle(135, 800); // swing to face group of three #1
	pros::Task([] {
		intakeMacro("L1"); // intake into hoard
		//toggleColourSort = false;
	});

	kw::moveToPoint(22, 8, 1000, true, 70);
	kw::driveTo(5, 1000, 60);
	pros::delay(300);

	kw::turnToAngle(315, 1000);
	kw::moveToPoint(35, -8, 1000, false, 80);
	kw::driveTo(-5, 1000);
	pros::delay(700);
	intakeMacro("R2");
	intakeTop.move_voltage(-5500);
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