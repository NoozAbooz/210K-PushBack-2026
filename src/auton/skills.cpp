#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"

void skills() {
	alliance = "red";
    toggleColourSort = false;

	intakeMacro("L1");
	kw::driveTo(31, 2500, 127); // drive to loader
	loaderPiston.set_value(true);
	kw::turnToAngle(90, 700); // turn to face loader
	pros::delay(100);

	/* get balls from loader */
	kw::driveTo(6, 800, 90, false); // drive into loader
	kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
	pros::delay(600); // stay at matchloader

	/* score on long goal */
	kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	//kw::moveToPoint(-18, 34, 2000, false, 90); // drive backwards into long goal
	pros::Task([] { // prep to score early via task
		kw::driveTo(-23, 1000, 100); // drive backwards into long goal
	});
	pros::delay(800); // ASYNC wait to arrive at goal
	intakeMacro("R1"); // score on long goall

	/* drive to group of 3 */
	pros::delay(2000);
    kw::driveTo(5, 1000, 127); // drive fwd from long goal
    kw::turnToAngle(90, 1000);
    kw::driveTo(28, 1000);
    intakeMacro("L1");
    kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
    pros::delay(800);
    kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	//kw::moveToPoint(-18, 34, 2000, false, 90); // drive backwards into long goal
	pros::Task([] { // prep to score early via task
		kw::driveTo(-23, 2000, 55); // drive backwards into long goal
	});
	pros::delay(800); // ASYNC wait to arrive at goal
	intakeMacro("R1"); // score on long goal
    pros::delay(1500);
	loaderPiston.set_value(false); // retract matchloader
	kw::driveTo(1.5, 1000, 127, false); // drive fwd from long goal
	kw::turnToAngle(219, 1500); // swing to face group of three #1
	intakeMacro("HOARD_L1"); // intake into hoard
	kw::driveTo(32, 2000, 50);
    pros::delay(400);
    kw::driveTo(-31, 1000);
    kw::turnToAngle(90, 1000);
    kw::driveTo(-20, 700, 55, true); // drive fwd from long goal
    intakeMacro("HOARD_R1");
    pros::delay(2000);
    intakeMacro("HOARD_L1");
    kw::driveTo(10, 800);
    kw::turnToAngle(0, 1000);
    kw::driveTo(13, 1000);
    kw::turnToAngle(275,1000);
    kw::driveTo(70, 3000);
    kw::turnToAngle(235, 1000);
    loaderPiston.set_value(true);
    kw::boomerang(-106, 31.7, 270, 0.2, 3000, true, 80);
    kw::turnToAngle(270, 1000);
    kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    kw::driveTo(-1, 800, 127); // slowly drive back from loader
    kw::driveTo(1, 1000);
    pros::delay(5000);
        kw::driveTo(-5, 2000, 80);
    kw::turnToAngle(264, 1000);
    kw::driveTo(-25, 2000, 80);
    intakeMacro("HOARD_R1");
    pros::delay(5000);
    kw::driveTo(10, 800);
    kw::turnToAngle(0, 1000);
    kw::driveTo(-15, 1000);
    kw::turnToAngle(90,1000);
    loaderPiston.set_value(false);
    kw::driveTo(80, 4000);
    kw::turnToAngle(0, 1000);
    kw::driveTo(-30.5, 1500);
    kw::turnToAngle(270, 1000);
  //  kw::driveTo(10, 800);
    kw::move_raw(-12000, -12000);
    pros::delay(4000);
    kw::move_raw(0, 0);
}