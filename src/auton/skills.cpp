#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
void skills() { /* NO COLOUR SORT */
	//intakeMacro("L1");
	kw::driveTo(30.5, 2000); // drive to loader
	//loaderPiston.set_value(true);
	kw::turnToAngle(90, 1000); // turn to face loader
	pros::delay(100);

	kw::driveTo(6, 800); // drive into loader
    kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
	pros::delay(1000);
    kw::driveTo(-10, 800, 127, false); // slowly drive back from loader
	kw::moveToPoint(-22, 33, 2000, false, 90); // drive backwards into long goal
	//kw::driveTo(-23, 1000);
	//stopIntake();
	pros::delay(1000);
	//intakeMacro("R1"); // score on long goal
	//loaderPiston.set_value(false); // retract matchloader
    kw::driveTo(7, 1000, 127); // drive forward a bit to avoid bounceback
    kw::turnToAngle(215, 1000); // turn to face neutral zone
    kw::moveToPoint(-20, 15, 2000, true, 90); // drive into neutral zone
    kw::driveTo(5, 2000, 60);
    kw::boomerang(-45, 24, 0, 0.1, 4000, true, 80);
    kw::turnToAngle(0, 1000);
    kw::driveTo(3, 2000, 60);
    pros::delay(1000);
    kw::driveTo(-14, 1000, 60);
    kw::turnToAngle(272, 1000);
    kw::driveTo(25, 2000, 45);
    kw::turnToAngle(315, 1000);
    kw::moveToPoint(-95, 36, 1000, true, 127);
    kw::moveToPoint(-73, 36, 2000, false, 70);
    pros::delay(2000);
    kw::moveToPoint(-105, 36, 1000, true, 127);
    kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
    pros::delay(600);
    kw::moveToPoint(-73, 36, 2000, false, 70);
    pros::delay(2000);
    kw::driveTo(7, 1000, 127); // drive forward a bit to avoid bounceback
    kw::turnToAngle(325, 1000); // turn to face neutral zone
    kw::moveToPoint(-58, -3, 2000, false, 70);
    pros::delay(4000);
    kw::driveTo(14, 1200, 127);
    kw::turnToAngle(180, 1000);
    kw::driveTo(40, 3000, 127);
    //loader here
    kw::turnToAngle(245, 1000);
    kw::moveToPoint(-90, -59.2, 4000, true, 80);
    kw::turnToAngle(270, 1000);
    kw::moveToPoint(-104, -59.5, 2000, true, 90);
    kw::move_raw(3000, 3000); // keep driving into loader to prevent bounceback
    pros::delay(1000);
    kw::moveToPoint(-71, -59.5, 2000, false, 70);
    pros::delay(2000);
    kw::driveTo(14, 1000, 127); // drive forward a bit to avoid bounceback
    kw::turnToAngle(45, 1000); // turn to face neutral zone
    kw::driveTo(30, 2000, 60);
    kw::turnToAngle(90, 1000);
    kw::driveTo(50, 2000, 60);
}