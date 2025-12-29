#include "main.h"
#include "libKW/api.hpp"

void skills() {
	alliance = "red";
    toggleColourSort = false;
    wingPiston.set_value(true); // retract wings

    kw::distance_kp = 1, kw::distance_ki = 0, kw::distance_kd = 8;
    kw::turn_kp = 0.3, kw::turn_ki = 0, kw::turn_kd = 2.6;

	/* travel to loader 1 */
	intakeMacro("L1");
	kw::driveTo(31.7, 2500, 127); // drive to loader
	loaderPiston.set_value(true);
	kw::turnToAngle(90, 700); // turn to face loader
	pros::delay(50);

	/* get balls from loader */
	kw::driveTo(11.7,800, 60); // drive into loader
	kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    // pros::delay(50);
    // kw::move_raw(-6000, -6000);
    // pros::delay(50);
    // kw::move_raw(6000, 6000);


	pros::delay(550); // stay at matchloader
    kw::move_raw(1000, 1000);
    pros::delay(1000);

	/* score on long goal */
	kw::driveTo(-10, 1000, 80); // slowly drive back from loader
    loaderPiston.set_value(false);
    kw::turnToAngle(125, 1500);
	kw::moveToPoint(-18, 46, 1000, false); // drive backwards into alley
    kw::turnToAngle(90, 1000);
    stopIntake();
    kw::driveTo(-70, 3000);

    kw::turnToAngle(0, 1000); // face the wall for reset
    kw::driveTo(-10.8, 1000);
    kw::turnToAngle(270, 1000);
    kw::driveTo(-15,1000, 60); // drive into loader
    pros::delay(200);
    intakeMacro("R1");
     kw::move_raw(-8000, -8000);
    pros::delay(2700);
    loaderPiston.set_value(true);
    kw::set_odom_position(0, 0, 0);

    // get from loader #2
    intakeMacro("L1");
    kw::moveToPoint(-0.5, 28.4, 2000, true, 70);
    kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    pros::delay(50);
    kw::move_raw(-4000, -4000);
    pros::delay(50);
    kw::move_raw(4000, 4000);
    pros::delay(2400);

    // back to long goal
    kw::moveToPoint(0, -6, 1000, false, 60);
    pros::delay(200);
    intakeMacro("R1");
    pros::delay(2700);
     kw::move_raw(-8000, -8000);
    stopIntake();
    kw::driveTo(5, 1000);
    knockerPiston.set_value(true);
    pros::delay(200);
    kw::driveTo(-5.5, 2000, 60);
    kw::move_raw(-5000, -5000);
    pros::delay(400);
    kw::set_odom_position(0, 0, 0);
    //loaderPiston.set_value(false);
   
    // move to loader 3
    kw::driveTo(12, 1000);
    kw::turnToAngle(270, 1000);
    //loaderPiston.set_value(true);
    kw::moveToPoint(-93.0, 13, 3500, true, 90); // limit speed
    kw::turnToAngle(0, 1000);

    // get from loader #3
    intakeMacro("L1");
    kw::driveTo(18.12, 2000, 60);
    kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    pros::delay(50);
    kw::move_raw(-4000, -4000);
    pros::delay(50);
    kw::move_raw(3000, 3000);
    pros::delay(2200);

    // move to loader 4
    kw::driveTo(-10, 1000);
    loaderPiston.set_value(false);
    kw::moveToPoint(-111, -1, 2000, false, 90);
    kw::turnToAngle(0, 1000);
    stopIntake();
    knockerPiston.set_value(false);
    kw::driveTo(-70, 3000);
    kw::turnToAngle(270, 1000);
    // wall reset location
    kw::driveTo(-10.4, 1000);
    kw::turnToAngle(180, 1000);
    kw::driveTo(-18.5,1000, 60); // drive into loader
    pros::delay(200);
    intakeMacro("R1");
    kw::move_raw(-8000, -8000); // keep driving into loader to prevent bounceback
    pros::delay(3000);
    loaderPiston.set_value(true);
    kw::set_odom_position(0, 0, 0);

    // get from loader #2
    intakeMacro("L1");
    kw::moveToPoint(0, 26.4, 1000, true, 70);
    kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    pros::delay(50);
    kw::move_raw(-6000, -6000);
    pros::delay(50);
    kw::move_raw(3000, 3000);
    pros::delay(2400);

   // back to long goal
    kw::moveToPoint(1, -6, 1000, false, 60);
    pros::delay(200);
    intakeMacro("R1");
     kw::move_raw(-8000, -8000);
    pros::delay(3000);
    stopIntake();
    kw::driveTo(5, 1000);
    knockerPiston.set_value(true);
    pros::delay(200);
    kw::driveTo(-5.5, 2000, 60);
    pros::delay(200);
    kw::set_odom_position(0, 0, 0);
    kw::driveTo(15, 1000);
    kw::turnToAngle(125, 1000);
    kw::moveToPoint(-30, 35.4, 1000, false); // drive backwards into alley
    kw::swing(90, 1000, false);
    loaderPiston.set_value(false);
    kw::driveTo(10, 1000);
    kw::moveToPoint(-44, 37, 5000, false);
    kw::driveTo(-2, 1000);
   

}
