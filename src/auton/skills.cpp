#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"

void skills() {
	alliance = "red";
    toggleColourSort = false;
    wingPiston.set_value(true); // retract wings

    kw::distance_kp = 1, kw::distance_ki = 0, kw::distance_kd = 8;
    kw::turn_kp = 0.3, kw::turn_ki = 0, kw::turn_kd = 2.6;

	/* travel to loader */
	intakeMacro("L1");
	kw::driveTo(31.7, 2500, 127); // drive to loader
	loaderPiston.set_value(true);
	kw::turnToAngle(90, 700); // turn to face loader
	pros::delay(50);

	/* get balls from loader */
	kw::driveTo(11.4,800, 60); // drive into loader
	kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
   //ros::delay(50);
    // kw::move_raw(-3000, -3000);
    // pros::delay(80);
    // kw::move_raw(6000, 6000);


	pros::delay(550); // stay at matchloader
    kw::move_raw(1000, 1000);
    pros::delay(1000);

	/* score on long goal */
	kw::driveTo(-10, 1000, 80); // slowly drive back from loader
    loaderPiston.set_value(false);
    kw::turnToAngle(125, 1500);
	kw::moveToPoint(-18, 46, 1000, false); // drive backwards into long goal
    kw::turnToAngle(90, 1000);
    stopIntake();
    kw::driveTo(-70, 3000);
    kw::turnToAngle(0, 1000);
    kw::move_raw(6000, 6000);
    pros::delay(400);
    kw::driveTo(-14.2, 1000);
    kw::turnToAngle(270, 1000);
    kw::driveTo(-13,1000, 60); // drive into loader
    pros::delay(200);
    intakeMacro("R1");
    pros::delay(2400);
    loaderPiston.set_value(true);
    intakeMacro("L1");
    kw::driveTo(26.4, 1000, 70);
    kw::move_raw(4000, 4000);
    pros::delay(2000);
    kw::driveTo(-27, 2000, 600);
    pros::delay(200);
    intakeMacro("R1");
    pros::delay(2000);
    kw::driveTo(5, 1000);
    knockerPiston.set_value(true);
    kw::driveTo(-5.5, 2000, 40);
    //kw::moveToPoint(-75, 32.8, 2000, false, 70);
	// 	//kw::driveTo(-33, 1500); // drive backwards into long goal

    // // move to 2nd loader
    // kw::turnToAngle(266, 1000);

    // kw::driveTo(63,800, 60); // drive into loader
}