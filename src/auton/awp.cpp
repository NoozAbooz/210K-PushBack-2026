#include "main.h"

void true_sawp(){
	pros::Task([] {
		intakeMacro("L1");
		blockerPiston.set_value(true);
		//loaderPiston.set_value(true);
	});
	kw::driveTo(8, 1000, 127); // push
	kw::moveToPoint(-2, -40.52, 1800, false, 127); //loader
	loaderPiston.set_value(true);
	kw::turnToAngle(270, 700); // turn to face loader
	kw::moveToPoint(-11.01, -42.27, 800, true, 60); // Loader #1
	kw::move_raw(8000, 8000);
	pros::delay(120);
	pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(500);
		intakeMacro("R1");
		loaderPiston.set_value(false);
	
	});
	kw::moveToPoint(21, -43, 1000, false, 127); // long Goal #1
	kw::move_raw(-6000, -6000);
	pros::delay(1200);
	kw::turnToAngle(25, 800);
	pros::Task([] {
		intakeMacro("L1");
		pros::delay(300);
		loaderPiston.set_value(true);
		pros::delay(300);
		loaderPiston.set_value(false);
		//pros::delay(700);
	});
	kw::boomerang(26.5, -20, 0.3, 0, 1500, true, 80); // Mid Cluster 1
	pros::Task([] {
		pros::delay(760);

		loaderPiston.set_value(true);

	});
	kw::moveToPoint(24.5, 28, 1700, true, 127);
	kw::turnToAngle(315, 700);
	pros::Task([] {
		intake_velocity.set_target(0);
		pros::delay(750);
		intakeMacro("R2");
		pros::delay(800);
		//intake.move_voltage(0); // im pretty sure we have to we have to use the velocity controller to stop the intake
		intake_velocity.set_target(0); // -> bro i forgot i made velo controller aurghhh
		pros::delay(200);
		// intakePullDownPiston.set_value(false); // balls were getting caught in the bot after we finish midgoal, i relocated this code a bit after -MZ
		// intakeMacro("L1"); // -> it is expected balls will fall out of the bot as we go to loader cuz midgoal isnt closed.... but we cant risk it getting stuck
	});
	//kw::turnToAngle(320, 700);
	kw::boomerang(38.16, 14.4, 315, 0.3, 1000, false, 800.3);
	//kw::moveToPoint(38, 11.3, 1000, false, 100); // Mid Goal
	kw::move_raw(-3000, -3000);
	pros::delay(900);
	//stopIntake(); // dont leak balls
	kw::moveToPoint(-1, 52.3, 2000, true, 127); // Mid to Loader

	// relocated part -MZ
	intakePullDownPiston.set_value(false);
	intakeMacro("L1");

	kw::turnToAngle(270, 900); // Turning to Loader #2
	kw::moveToPoint(-14.5, 54, 1000, true, 60); // Loader #2
	kw::move_raw(8000, 8000);
	pros::delay(100);
	pros::Task([] {
		pros::delay(300);
		stopIntake();
		loaderPiston.set_value(false);
		pros::delay(600);
		intakeMacro("R1");
	});
	kw::moveToPoint(18, 54, 1000, false, 127); // long Goal #2
	kw::move_raw(-8000, -8000);


}

void sawp() {
	toggleColourSort = false;
	pros::Task([] {
		intakeMacro("L1");
		blockerPiston.set_value(true);
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(0, 30.75, 1000, true, 127);
	kw::turnToAngle(90, 700); // turn to face loader
	kw::moveToPoint(13.81, 33.4, 1000, true,50); // Loader #1
	kw::move_raw(5000, 5000);
	pros::delay(80);
	pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(600);
		intakeMacro("R1");
	});
	kw::moveToPoint(-18.24, 33.3, 1500, false, 127); // long Goal #1
	kw::move_raw(-7000, -7000);
	pros::delay(1200);
	loaderPiston.set_value(false);
	kw::turnToAngle(205, 800, true, 90); // turn to face cluster
	pros::Task([] {
		intakeMacro("L1");
		pros::delay(300);
		loaderPiston.set_value(true);
		pros::delay(300);
		loaderPiston.set_value(false);
		pros::delay(800);
		loaderPiston.set_value(true);
	});
	kw::boomerang(-25.95, 11.37, 180, 0.2, 1500, true, 70); // Mid Cluster 1
	// kw::turnToAngle(182, 500);
	kw::driveTo(30, 1000, 127, false);
	kw::moveToPoint(-25.11, -33.70, 1000, true, 70); // Mid Cluster 2
	pros::Task([] {
		pros::delay(800);
		intakeMacro("R2");
		pros::delay(1200);
		intake.move_voltage(0);
		intakePullDownPiston.set_value(false);
		pros::delay(700);
		intakeMacro("L1");
	});
	kw::boomerang(-37.12, -23.68, 135, 0.3, 1000, false, 80); // Mid Goal
	kw::move_raw(-2000, -2000);
	pros::delay(1200);
	kw::moveToPoint(2, -58.01, 1500, true, 127); // Mid to Loader
	kw::turnToAngle(90, 900); // Turning to Loader #2
	kw::moveToPoint(23.24, -59.81, 1000, true, 50); // Loader #2
	kw::move_raw(5000, 5000);
	pros::delay(60);
	pros::Task([] {
		pros::delay(300);
		stopIntake();
		loaderPiston.set_value(false);
		pros::delay(400);
		intakeMacro("R1");
	});
	kw::moveToPoint(-17.38, -61.35, 1000, false, 127); // long Goal #2

	kw::move_raw(-6000, -6000);

}
void legacy_sawp() {
	// toggleColourSort = false;

	// /* travel to loader */
	// intakeMacro("L1");
	// kw::driveTo(31.0, 2500, 127); // drive to loader
	// loaderPiston.set_value(true);
	// kw::turnToAngle(90, 700); // turn to face loader
	// pros::delay(50);

	// /* get balls from loader */
	// kw::driveTo(11.5,800, 60); // drive into loader
	// kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
	// pros::delay(100); // stay at matchloader

	// /* score on long goal */
	// //kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	// //kw::moveToPoint(-18, 34, 2000, false, 90); // drive backwards into long goal
	// double turn_angle = kw::normalize_target(kw::to_deg(atan2(-20 - kw::x_pos, 31 - kw::y_pos))) + 180;
	// kw::turnToAngle(turn_angle, 1000); // turn towards long goal

	// pros::Task([] { // prep to score early via task
	// 	kw::moveToPoint(-20, 32.0, 1000, false, 127); // drive backwards into long goal
	// 	//kw::driveTo(-33, 1500); // drive backwards into long goal
	// });
	// pros::delay(500); // ASYNC wait to arrive at goal
	// intakeMacro("R1"); // score on long goal
	// loaderPiston.set_value(false); // retract matchloader

	// // /* drive to group of 3 */
	// pros::delay(1500);
	// // kw::driveTo(1.5, 1000, 127, false); // drive fwd from long goal
	// kw::turnToAngle(225, 800); // swing to face group of three #1
	// pros::Task([] {
	// 	intakeMacro("L1"); // intake into hoard
	// 	toggleColourSort = false;
	// });

	// kw::driveTo(8.3, 1000, 127, false);
	// kw::turnToAngle(180, 1000);
	// kw::driveTo(30, 1500, 127, false);
	// loaderPiston.set_value(true); // lower matchloader to prevent balls from rolling away
	// kw::turnToAngle(140, 1000);
	// //kw::correct_angle = kw::normalize_target(140.6);
	// kw::moveToPoint(-38.1, -24, 1000, false);
	// pros::Task([] {
	// 	intakeMacro("R2"); // intake into hoard4
	// 		intakeTop.move_voltage(-5000);
	// 		pros::delay(725);
	// 	intakeMacro("L1");
	// });
	// pros::Task([] {
	// 	double turn_angle = kw::normalize_target(kw::to_deg(atan2(-3.5 - kw::x_pos, -61.95 - kw::y_pos)));
	// 	kw::turnToAngle(turn_angle, 1000);
	// });
	// pros::delay(750);

	// kw::moveToPoint(-3.5, -63.25 , 1500, true); // 
	// pros::delay(50);
	// kw::correct_angle = kw::normalize_target(152);
	// toggleColourSort = true;
	// kw::turnToAngle(90, 600); // face long goal
	// kw::driveTo(15, 800, 90); // drive into loader
	// kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
	// pros::delay(450);
	// 	turn_angle = kw::normalize_target(kw::to_deg(atan2(-23 - kw::x_pos, -63 - kw::y_pos))) + 180;
	// 	kw::turnToAngle(turn_angle, 1000);
		
	// 	kw::moveToPoint(-23, -63.74, 1000, false); // drive backwards into long goal
	// 	//kw::driveTo(-33, 1000);

	// 	intakeMacro("R1");
	// 	wingPiston.set_value(true); // deploy wings for driver
	// 	kw::move_raw(-6000, -6000);

	// 	wingStatus = true;
	// 	loaderStatus = true;
}


void left_half() { // Left Side Half Solo AWP
	toggleColourSort = false;
	pros::Task([] {
		intakeMacro("L1");
		blockerPiston.set_value(true);
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(0, 30.75, 1000, true, 127);
	kw::turnToAngle(270, 700); // turn to face loader
	kw::moveToPoint(-13.81, 33.4, 1000, true,50); // Loader #1
	kw::move_raw(5000, 5000);
	pros::delay(85);
	pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(400);
		intakeMacro("R1");
	});
	kw::moveToPoint(17.74, 33.7, 1500, false, 127); // long Goal #1
	kw::move_raw(-6000, -6000);
	pros::delay(1200);
	loaderPiston.set_value(false);
	kw::turnToAngle(155, 800, true, 90); // turn to face cluster
	pros::Task([] {
		intakeMacro("L1");
		pros::delay(300);
		loaderPiston.set_value(true);
		pros::delay(3000);
		loaderPiston.set_value(false);
	});
	kw::boomerang(25.95, 0.37, 180, 0.2, 2000, true, 80); // Mid Cluster 1
	kw::turnToAngle(315, 700);
	kw::moveToPoint(35.48, -5.4, 1000, false, 90); // Mid Cluster 1
	kw::move_raw(-3000, -3000);
	intakeMacro("R2");
	pros::delay(1500);
	intakeMacro("L1");
	intake.move_voltage(0);
	// kw::moveToPoint(14, 20, 1000, true, 127); // Mid Goal
	// kw::turnToAngle(270, 1000);
	// kw::moveToPoint(37, 22, 8000, false, 40); // Loader #2
	// kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);

}

void right_half() { // Right Side Half Solo AWP
toggleColourSort = false;
	pros::Task([] {
		intakeMacro("L1");
		blockerPiston.set_value(true);
		loaderPiston.set_value(true);
	});
	kw::moveToPoint(0, 30.75, 1000, true, 127);
	kw::turnToAngle(90, 700); // turn to face loader
	kw::moveToPoint(13.81, 33.4, 1000, true,50); // Loader #1
	kw::move_raw(5000, 5000);
	pros::delay(80);
	pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(600);
		intakeMacro("R1");
	});
	kw::moveToPoint(-18.24, 33.3, 1500, false, 127); // long Goal #1
	kw::move_raw(-7000, -7000);
	pros::delay(1400);
	loaderPiston.set_value(false);
	kw::turnToAngle(205, 800, true, 90); // turn to face cluster
	pros::Task([] {
		intakeMacro("L1");
		pros::delay(300);
		loaderPiston.set_value(true);
		pros::delay(300);
		loaderPiston.set_value(false);
	});
	kw::boomerang(-25.95, 11.37, 180, 0.2, 1500, true, 70); // Mid Cluster 1
	kw::moveToPoint(-33.48, -1.03, 1000, true, 90); // Mid Cluster 1
	kw::turnToAngle(225, 800);
	kw::driveTo(3, 1000, 127);
	pros::delay(100);
	intakeMacro("L2");
	pros::delay(1500);
	intake.move_voltage(0);
	kw::moveToPoint(-11, 22, 1000, false, 127); // Mid Goal
	kw::turnToAngle(270, 1000);
	kw::moveToPoint(-38, 23, 1000, true, 70); // Loader #2
	kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
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