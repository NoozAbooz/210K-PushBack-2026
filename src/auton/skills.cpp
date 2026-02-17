#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/api.hpp"
#include "main.h"

void skills(){
    toggleColourSort = false;

	intakeMacro("L1");
    wingPiston.set_value(true); // deploy wings for driver
    blockerPiston.set_value(true);

    double reset_x_coord;
	double reset_y_coord;

	kw::move_raw(9000, 9000);
    pros::delay(400);
    
    kw::move_raw(-4000, -4000);
    pros::delay(200);
    kw::move_raw(12000, 12000);
    pros::delay(800);
    kw::move_raw(-4000, -4000);
    pros::delay(300);
    kw::move_raw(12000, 12000);
    pros::delay(900);
    
    kw::turnToAngle(0, 500);
    
    loaderPiston.set_value(true);
    kw::move_raw(-11000, -11000);
    pros::delay(700);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(100);
    kw::turnToAngle(0, 500);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
    wingPiston.set_value(false);
    pros::delay(300);

    // dist reset #1
    reset_x_coord = -(kw::getDistance(rightDistance) - 65.4);
	reset_y_coord = -kw::getDistance(fwdDistance);
    kw::set_odom_position(reset_x_coord, reset_y_coord);
    //console.printf("rightDist: %.2f fwdDist: %.2f\n", kw::getDistance(rightDistance), kw::getDistance(fwdDistance));
    console.printf("resetX: %.2f resetY: %.2f\n", reset_x_coord, reset_y_coord);
    loaderPiston.set_value(false);

    // move to midgoal
    kw::moveToPoint(7.6, -70, 1500, false);
    kw::swing(48, 800, false);

    // // grab 1 blue ball, score all 7
    kw::driveTo(9, 800);
    kw::driveTo(-10, 800);
    intakeMacro("R2");
    // intake_velocity.set_target(500); // sketchy workaround to make velo controller work

    // pros::delay(4000);
    // kw::driveTo(5, 800, 127, false);
    // intakeMacro("L1");

    // kw::moveToPoint(-27, -21, 2000);
    // kw::turnToAngle(90, 1000);

}

void Legacy_skills() {
	toggleColourSort = false;
	pros::Task([] {
		intakeMacro("L1");
		blockerPiston.set_value(true);
		loaderPiston.set_value(true);
        //wingPiston.set_value(true);
	});
	kw::moveToPoint(0, 30.75, 1000, true, 127);
	kw::turnToAngle(270, 700); // turn to face loader
	kw::moveToPoint(-13.81, 33.4, 1000, true,50); // Loader #1
	kw::move_raw(5000, 5000);
    // pros::delay(50);
    // kw::move_raw(-6000, -6000);
    // pros::delay(50);
    // kw::move_raw(6000, 6000);


    pros::delay(1200);

	/* score on long goal */
	kw::driveTo(-10, 1000, 80); // slowly drive back from loader
    loaderPiston.set_value(false);
    kw::turnToAngle(235, 1500);
	kw::moveToPoint(18, 46, 1000, false); // drive backwards into alley
    kw::turnToAngle(270, 1000);
    stopIntake();
    kw::driveTo(-70, 3000);

    kw::turnToAngle(0, 1000); // face the wall for reset
    kw::driveTo(-10.0, 1000);
    kw::turnToAngle(90, 1000);
    kw::driveTo(-15,1000, 60); // drive into loader
    pros::delay(200);
    intakeMacro("R1");
     kw::move_raw(-8000, -8000);
    pros::delay(3000);
    kw::turnToAngle(90, 800);
    loaderPiston.set_value(true);
    kw::set_odom_position(0, 0, 0);

    // get from loader #2
    intakeMacro("L1");
    kw::moveToPoint(0.5, 28.4, 2000, true, 70);
    kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    pros::delay(1500);
    // back to long goal
    kw::moveToPoint(0, -6, 1000, false, 60);
    pros::delay(200);
    intakeMacro("R1");
     kw::move_raw(-8000, -8000);
    pros::delay(3000);

    stopIntake();
    // kw::driveTo(5, 1000);
    // //knockerPiston.set_value(true);
    // pros::delay(200);
    // kw::driveTo(-5.5, 2000, 60);
    // kw::move_raw(-5000, -5000);
    pros::delay(400);
    //kw::set_odom_position(0, 0, 0);
    //loaderPiston.set_value(false);
   
    // move to loader 3
    kw::driveTo(12, 1000);
    kw::turnToAngle(90, 1000);
    //loaderPiston.set_value(true);
    kw::moveToPoint(95, 14, 3500, true, 90); // limit speed
    kw::turnToAngle(0, 1000);

    // get from loader #3
    intakeMacro("L1");
    kw::driveTo(18.12, 2000, 60);
    kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    pros::delay(1500);

    // move to loader 4
    kw::driveTo(-10, 1000);
    loaderPiston.set_value(false);
    kw::moveToPoint(111, 5, 2000, false, 90);
    kw::turnToAngle(0, 1000);
    stopIntake();
    //knockerPiston.set_value(false);
    kw::driveTo(-74, 3000);
    kw::turnToAngle(90, 1000);
    // wall reset location
    kw::driveTo(-10.0, 1000);
    kw::turnToAngle(180, 1000);
    kw::driveTo(-18.5,1000, 60); // drive into loader
    pros::delay(200);
    intakeMacro("R1");
    kw::turnToAngle(180, 800);
    kw::move_raw(-8000, -8000); // keep driving into loader to prevent bounceback

    pros::delay(3000);
    loaderPiston.set_value(true);
    kw::set_odom_position(0, 0, 0);

    // get from loader #2
    intakeMacro("L1");
    kw::moveToPoint(0, 26.4, 1000, true, 70);
    kw::move_raw(4000, 4000); // keep driving into loader to prevent bounceback
    pros::delay(1500);

   // back to long goal
    kw::moveToPoint(0, -1, 1000, false, 60);
    pros::delay(200);
    intakeMacro("R1");
     kw::move_raw(-8000, -8000);
    pros::delay(3000);
    stopIntake();
    // kw::driveTo(5, 1000);
    // //knockerPiston.set_value(true);
    // pros::delay(200);
    // kw::driveTo(-5.5, 2000, 60);
    // pros::delay(200);
   // kw::set_odom_position(0, 0, 0);
    kw::driveTo(15, 1000);
    kw::boomerang(34, 34, 270, 0.4, 1500, false, 70);
    kw::turnToAngle(270, 1000);
//     kw::turnToAngle(235, 1000);
//     kw::moveToPoint(30, 35.4, 1000, false); // drive backwards into alley
//     kw::swing(90, 1000, false);
loaderPiston.set_value(false);
wingPiston.set_value(true);
kw::driveTo(10, 1000);
kw::moveToPoint(44, 37, 5000, false, 127, true, false, false, 127);
kw::driveTo(-8, 5000, 127, true, 127);
//    intakeMacro("L1");
    // kw::move_raw(-9000, -9000);
    // pros::delay(1300);
    kw::move_raw(0,0);

   

}


