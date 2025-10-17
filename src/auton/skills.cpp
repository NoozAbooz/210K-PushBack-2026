#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"

void skills() {
	alliance = "red";
    toggleColourSort = false;

	intakeMacro("HOARD_L1");
	kw::driveTo(32, 2500, 127); // drive to loader
	loaderPiston.set_value(true);
	kw::turnToAngle(90, 700); // turn to face loader
	pros::delay(100);

	kw::driveTo(6, 800, 127, false); // drive into loader
	kw::move_raw(1500, 1500); // keep driving into loader to prevent bounceback
	pros::delay(2000);
    kw::move_raw(-1000, -1000);
    pros::delay(100);
    kw::move_raw(2000, 2000);
    pros::delay(600);

	kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	//kw::moveToPoint(-18, 34, 2000, false, 90); // drive backwards into long goal
	pros::Task([] {
		kw::driveTo(-23, 1000); // drive backwards into long goal
	});

	pros::delay(1500); // wait to arrive at goal
	intakeMacro("HOARD_R1"); // score on long goal
	loaderPiston.set_value(false); // retract matchloader

	pros::delay(3000);
    intakeMacro("HOARD_L1"); // intake into hoard
	kw::driveTo(1, 1000, 127, false);
	kw::turnToAngle(220, 1500); // swing to face group of three #1
    pros::Task([] {
        pros::delay(1200);
            loaderPiston.set_value(true); // prevent balls from rolling away
            });
	kw::driveTo(28, 1500, 80);
    kw::driveTo(-27, 1500, 80);
    kw::turnToAngle(90, 1000);
    kw::driveTo(-18, 1000, 80);
    intakeMacro("HOARD_R1");
    pros::delay(2000);
    kw::driveTo(1, 1000, 127, false);
	kw::turnToAngle(220, 1500); // swing to face group of three #1
	intakeMacro("L1"); // intake into hoard
	kw::driveTo(28, 1500, 80);
    kw::turnToAngle(275, 1000);
    // kw::driveTo(65, 127);
    // kw::turnToAngle(315, 1000);
    // kw::moveToPoint(-105, 30, 1000, true, 80);

        
    // kw::boomerang(-45, 24, 0, 0.1, 4000, true, 80);
    // kw::turnToAngle(0, 1000);
    // kw::driveTo(3, 2000, 60);
    // pros::delay(1000);
    // kw::driveTo(-14, 1000, 60);
    // kw::turnToAngle(272, 1000);
    // kw::driveTo(25, 2000, 45);
    // kw::turnToAngle(315, 1000);
    // kw::moveToPoint(-95, 36, 1000, true, 127);
    // kw::moveToPoint(-73, 36, 2000, false, 70);
    // pros::delay(2000);
    // kw::moveToPoint(-105, 36, 1000, true, 127);
    // kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
    // pros::delay(600);
    // kw::moveToPoint(-73, 36, 2000, false, 70);
    // pros::delay(2000);
    // kw::driveTo(7, 1000, 127); // drive forward a bit to avoid bounceback
    // kw::turnToAngle(325, 1000); // turn to face neutral zone
    // kw::moveToPoint(-58, -3, 2000, false, 70);
    // pros::delay(4000);
    // kw::driveTo(14, 1200, 127);
    // kw::turnToAngle(180, 1000);
    // kw::driveTo(40, 3000, 127);
    // //loader here
    // kw::turnToAngle(245, 1000);
    // kw::moveToPoint(-90, -59.2, 4000, true, 80);
    // kw::turnToAngle(270, 1000);
    // kw::moveToPoint(-104, -59.5, 2000, true, 90);
    // kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
    // pros::delay(1000);
    // kw::moveToPoint(-71, -59.5, 2000, false, 70);
    // pros::delay(2000);
    // kw::driveTo(14, 1000, 127); // drive forward a bit to avoid bounceback
    // kw::turnToAngle(45, 1000); // turn to face neutral zone
    // kw::driveTo(30, 2000, 60);
    // kw::turnToAngle(90, 1000);
    // kw::driveTo(50, 2000, 60);
}