#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "libKW/drivetrain/odom.hpp"
#include "main.h"
#include "libKW/api.hpp"
#include "pros/rtos.hpp"

void skills(){

    // Park Zone Balls
    pros::Task([]{
        intakeMacro("L1");
        wingPiston.set_value(false); // retract wing
    });
    kw::driveTo(3.8, 3000, 70);
    pros::delay(1000);
    kw::driveTo(3.8, 3000, 70);
    pros::delay(1000);
    kw::driveTo(-20, 1500);
    kw::move_raw(5000, 5000);
    kw::set_odom_position(0, 0, 0);

    // Mid Goal
    kw::driveTo(-28, 1000);
    kw::turnToAngle(97, 800);
    kw::moveToPoint(15.45, -31.55, 1000, true, 80);
    kw::turnToAngle(45, 600);
    kw::moveToPoint(12.23, -37.99, 1000, false, 110);
    kw::move_raw(-3000, -3000);
    intakeMacro("R2");
    pros::delay(6000);
    kw::driveTo(5, 1000);
    pros::Task([]{
        intakeMacro("L1");
        pros::delay(600);
        loaderPiston.set_value(true);
    });

    // First Loader
    kw::moveToPoint(45.07, -3.86, 1500, true, 127);
    kw::turnToAngle(0, 600);
    kw::moveToPoint(45.71, 7.73, 1000, true, 90);
    kw::move_raw(3000, 3000);
    pros::delay(1500);

    // Driving To First Goal
    kw::moveToPoint(58.59, -23.18, 1500, false, 127);
    stopIntake();
    kw::moveToPoint(56.66, -90.78,1500, false);
    kw::turnToAngle(270, 700);
    kw::moveToPoint(45.71, -91.42, 1000, true);
    kw::turnToAngle(180, 700);

    // First Goal
    kw::moveToPoint(45.71, -79.83, 1000, false);
    kw::move_raw(-5000, -5000);
    kw::set_odom_position(0, 0, 0);
    intakeMacro("R1");
    pros::delay(2000);

    // Second Loader + Goal
    intakeMacro("L1");
    kw::moveToPoint(0.00, 20.40, 1000);
    kw::driveTo(6, 1000, 60);
    kw::move_raw(3000, 3000);
    pros::delay(1500);
    kw::moveToPoint(0, 0, 1000, false);
    intakeMacro("R1");
    pros::delay(2000);

    // Driving To Third Loader
    loaderPiston.set_value(false);
    kw::boomerang(16.10, 9.66, 90, 0.5, 1500, true, 70);
    stopIntake();
    kw::moveToPoint(93.35, 9.01, 2000, true);
    loaderPiston.set_value(true);
    intakeMacro("L1");
    kw::turnToAngle(0, 700);

    // Third Loader
    kw::moveToPoint(93.35, 20.04, 1000, true, 127);
    kw::driveTo(6, 1000, 60);
    kw::move_raw(3000, 3000);
    pros::delay(1500);

    // Driving To Third Goal
    kw::moveToPoint(107.52, -0.64, 1500, false, 127);
    kw::turnToAngle(0, 700);
    kw::moveToPoint(102.37, -73.39, 2000, false);
    kw::turnToAngle(270, 700);
    kw::moveToPoint(94.00, -72.11, 1000, true);
    kw::turnToAngle(180, 700);

    // Third Goal
    kw::moveToPoint(94.00, -60.52, 1000, false);
    kw::move_raw(-5000, -5000);
    kw::set_odom_position(0, 0, 0);
    intakeMacro("R1");
    pros::delay(2000);

    // Fourth Loader + Goal
    intakeMacro("L1");
    kw::moveToPoint(0.00, 20.40, 1000);
    kw::driveTo(6, 1000, 60);
    kw::move_raw(3000, 3000);
    pros::delay(1500);
    kw::moveToPoint(0, 0, 1000, false);
    intakeMacro("R1");
    pros::delay(2000);
    loaderPiston.set_value(false);

    // Parking
    kw::swing(50, 700);
    kw::moveToPoint(14.81, 7.73, 1500, true, 127);
    kw::turnToAngle(90, 700);
    kw::moveToPoint(47.64, 8.37, 1500, true, 127);
    kw::turnToAngle(90, 800);
    kw::move_raw(12000, 12000);
    pros::delay(4000);
    kw::move_raw(0, 0);

}

void Legacy_skills() {
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
    //knockerPiston.set_value(true);
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
    //knockerPiston.set_value(false);
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
    //knockerPiston.set_value(true);
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


