#include "abstractGlobals.hpp"
#include "main.h"

void skills(){
    // libKW MTPoint v0.1
    blockerPiston.set_value(true);
    intakeMacro("L1"); // Start Same as Left Elims

    pros::Task([] {
        pros::delay(650);
        stopIntake();
    });

    kw::moveToPoint(-5, 27, 1300); // Move To Four Stack
    intakeMacro("L1");
    kw::turnToAngle(230, 1000);
    kw::moveToPoint(4, 38, 900, false); // mid goal

    intakeMacro("R2");
    intake_velocity.set_target(12000);
    pros::delay(800);
    stopIntake();

    kw::turnToPoint(-32, 0, 1000); // move to loader 1
    loaderPiston.set_value(true);
    kw::moveToPoint(-30.5, 0, 1500);
    kw::turnToAngle(180, 1000);
    pros::delay(200);

    intakeMacro("L1");
    kw::driveTo(12, 900, 60);
    kw::move_raw(5000, 5000);
    pros::delay(1000);
    kw::boomerang(-47, 28, 180, 0.4, 1500, false, 70); // boomerang to alley
    kw::moveToPoint(-50, 91, 3000, false, 100); // move straight in alley
    kw::turnToAngle(90, 1000); // turn here keeping loader down
    kw::moveToPoint(-36, 94, 1500); // align with goal
    kw::turnToAngle(0, 1000); // turn to goal
    kw::moveToPoint(-34, 75, 1000, false);
    kw::turnToAngle(0, 1000);
    intakeMacro("R1");
    intake_velocity.set_target(12000);
     kw::turnToAngle(0, 1000);
     kw::move_raw(-7700, -7700); //-8000,-8000
    pros::delay(1500);
        kw::set_odom_position(0, 0, 0);
        pros::delay(1300);
    intakeMacro("L1");
    kw::moveToPoint(0.3, 28, 1000, true, 80);
   // kw::moveToPoint(-33.5, 104, 1500, true, 80); // loader
    kw::move_raw(8000, 8000);
    pros::delay(1300);
    // kw::moveToPoint(-32.8, 75, 1000, false); // score
    kw::moveToPoint(0, -2, 1000, false, 90);    
     kw::turnToAngle(0, 1000);
     kw::move_raw(-5700, -5700);
     intakeMacro("R1");
     intake_velocity.set_target(520);
     loaderPiston.set_value(false);
    kw::set_odom_position(0, 0, 0);
     pros::delay(2600);
     
    kw::boomerang(31, 35.5, 90, 0.35, 2000, true, 90);
    kw::turnToAngle(90, 900);
    loaderPiston.set_value(true);
    wingPiston.set_value(true);
    intakeMacro("L1");

    // go into zone
    
    pros::delay(260);
    kw::move_raw(6000, 6000);
    pros::delay(280);
    kw::move_raw(8000, 8000);
    pros::delay(230);
    kw::move_raw(4000, 4000);
    pros::delay(200);
    loaderPiston.set_value(false);
    pros::delay(700);

    kw::move_raw(6000, 6000);
    pros::delay(1200);
    kw::turnToAngle(90, 1000);
    kw::move_raw(-4000, -4000);
    wingPiston.set_value(false);
    pros::delay(1400);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(100);
    
    // // reset
    // reset_x_coord = 0;//(kw::getDistance(bwdDistance));
    // reset_y_coord = -(kw::getDistance(leftDistance));
    kw::set_odom_position(0, 0, 0);
    kw::turnToAngle(270,1000);
    kw::moveToPoint(30, -6, 1000, false);
    kw::turnToAngle(270,1000);
    intakeMacro("stop");
    intake_velocity.set_target(0);
    kw::boomerang(54, -5, 315, 0.3, 2000, false, 60);
    kw::move_raw(-4000, -4000);
    pros::delay(200);
    intakeMacro("R2");
    intake_velocity.set_target(560); // those who midgoal for control
    pros::delay(4500);
    pros::Task([] {
        pros::delay(200);
        intakeMacro("R1");
        //stopIntake();
    });
    kw::driveTo(15, 2000, 50);
    loaderPiston.set_value(true);

    kw::moveToPoint(16, 30, 1000);
        intakeMacro("L1");
    kw::turnToAngle(270, 1000);
    kw::moveToPoint(6, 31, 1000, true, 80);
    kw::move_raw(5000, 5000);
    pros::delay(1200);
    kw::boomerang(45, 47, 270, 0.4, 2000, false, 80);
    intakeMacro("stop");
    kw::moveToPoint(110, 47, 3000, false, 100);
    kw::turnToAngle(180, 1000);
    kw::moveToPoint(112, 33, 1000);
    kw::turnToAngle(90, 1000);
    kw::moveToPoint(91, 32, 1000, false);
    kw::move_raw(-8000, -8000);
    // intakeMacro("L2");
    // pros::delay(300);
    intakeMacro("R1");
        intake_velocity.set_target(12000);
    pros::delay(2500);
    //  kw::driveTo(3, 1000);
    // kw::driveTo(-3, 1000);
    // pros::delay(1000);
        kw::set_odom_position(0, 0, 0);
    intakeMacro("L1");
    kw::moveToPoint(0.3, 30, 1000, true, 80);
   // kw::moveToPoint(-33.5, 104, 1500, true, 80); // loader
    kw::move_raw(6000, 6000);
    pros::delay(1500);
    // kw::moveToPoint(-32.8, 75, 1000, false); // score
    kw::moveToPoint(0, -2, 1000, false, 90);    
     kw::turnToAngle(0, 1000);
     kw::move_raw(-5700, -5700);
     intakeMacro("R1");
     intake_velocity.set_target(550);
     loaderPiston.set_value(false);
    kw::set_odom_position(0, 0, 0);
    pros::delay(2000);

     kw::boomerang(31, 35.5, 90, 0.35, 2000, true, 90);
    kw::turnToAngle(90, 900);
    loaderPiston.set_value(true);
    wingPiston.set_value(true);
    intakeMacro("L1");

    // go into zone
    
    pros::delay(260);
    kw::move_raw(6000, 6000);
    pros::delay(280);
    kw::move_raw(8000, 8000);
    pros::delay(230);
    kw::move_raw(4000, 4000);
    pros::delay(200);
    loaderPiston.set_value(false);
    pros::delay(300);
    kw::move_raw(0, 0);
}
//     //Intake mid here
//     kw::moveToPoint(-31.86, -1.84, 2000 ); // loader movement
//     kw::moveToPoint(-31.86, -14.71, 2000 ); // loading
//  kw::moveToPoint(-45.96, 23.29, 2000, false); // boomerang to alley
//  kw::moveToPoint(-46.57, 82.11, 2000 ); // move straight in alley
//  //turn here keeping loader down
//  kw::moveToPoint(-32.48, 82.11, 2000 ); // align with goal
//  //turn to goal
//  kw::moveToPoint(-33.09, 71.08, 2000 ); // at goal now  
//  //score here
//  kw::moveToPoint(-31.86, 106.01, 2000 ); // loader
//  kw::moveToPoint(-33.09, 71.69, 2000 ); // score


// look at very bottom and reset after this second set of loading
// this motion is good for from the long goal to the park zone and make sure to tune htis
    // loaderPiston.set_value(false);
    // // kw::set_odom_position(0, 0, 0);
    // kw::boomerang(33, 34, 90, 0.4, 2000, 70);
    // loaderPiston.set_value(true);
    // wingPiston.set_value(true);
    // pros::delay(400);
    // kw::move_raw(8000, 8000);
    // pros::delay(1400);
    // loaderPiston.set_value(false);
    // kw::move_raw(6000, 6000);
    // pros::delay(700);
    // kw::move_raw(0, 0);

    // from here its reset and you will have to do everything from here on out



// this motion is good for from the long goal to the park zone and make sure to tune htis
    // loaderPiston.set_value(false);
    // // kw::set_odom_position(0, 0, 0);
    // kw::boomerang(33, 34, 90, 0.4, 2000, 70);
    // loaderPiston.set_value(true);
    // wingPiston.set_value(true);
    // pros::delay(400);
    // kw::move_raw(8000, 8000);
    // pros::delay(1400);
    // loaderPiston.set_value(false);
    // kw::move_raw(6000, 6000);
    // pros::delay(700);
    // kw::move_raw(0, 0);



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
kw::moveToPoint(44, 37, 5000, false, 127, true, false, false);
kw::driveTo(-8, 5000, 127, true, 127);
//    intakeMacro("L1");
    // kw::move_raw(-9000, -9000);
    // pros::delay(1300);
    kw::move_raw(0,0);

   

}


void driver_skills_macro() {
    wingPiston.set_value(true); // deploy wings for driver
    blockerPiston.set_value(true);
    intakeMacro("L1");

    double reset_x_coord;
	double reset_y_coord;

	kw::move_raw(9000, 9000);
    pros::delay(400);
    
    kw::move_raw(-4000, -4000);
    pros::delay(200);
    kw::move_raw(12000, 12000);
    pros::delay(600);
    kw::move_raw(-4000, -4000);
    pros::delay(300);
    kw::move_raw(10000, 10000);
    pros::delay(500);
    
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
    kw::moveToPoint(10.6, -70, 1500, false);
    kw::swing(48, 800, false);

    // // grab 1 blue ball, score all 7
    kw::driveTo(10, 800);
    // kw::moveToPoint(17, -64, 1500, true);
    // kw::moveToPoint(11, -70,1000, false);
    kw::driveTo(-12, 800);
}