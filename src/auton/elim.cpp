#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "libKW/api.hpp"
#include "pros/motors.h"

void right_elim() {
    intakeMacro("L1");
    wingPiston.set_value(true);
    kw::driveTo(28.5, 2000, 50);
    kw::moveToPoint(14, 48, 1000);
    pros::delay(400);
    kw::moveToPoint(0, 22, 1000, false);
    kw::turnToAngle(124, 1000);
    kw::moveToPoint(31, 17, 2000);
    loaderPiston.set_value(true);
    kw::turnToAngle(160, 1000);    
    kw::driveTo(20, 1000, 70);
    //kw::moveToPoint(35.0, 2.7, 1500, true, 60);
    kw::move_raw(3000, 3000);
    pros::delay(150);
    //kw::driveTo(-33, 1000);
    kw::moveToPoint(25.9, 33.3, 1000, false);
    stopIntake();
    kw::move_raw(-8000, -8000);
    stopIntake();
    pros::delay(100);
        intakeMacro("L2");
        pros::delay(100);
        intakeMacro("R1");
    pros::delay(1500);
    loaderPiston.set_value(false);
    kw::move_raw(0,0);
    pros::delay(2000);
    stopIntake();
    wingPiston.set_value(false);
    kw::moveToPoint(+37, 30, 1000);
    kw::turnToAngle(167, 1000);
    //kw::moveToPoint(+28.0, 57, 8000, false, 70);
    kw::driveTo(-30, 3000, 80);
    kw::turnToAngle(161, 1000);

}

void left_elim() {
    pros::Task([] {
        intakeMacro("L1");
        pros::delay(610);
        loaderPiston.set_value(true);
        blockerPiston.set_value(true);
        pros::delay(300);
        loaderPiston.set_value(false);
    });
    kw::moveToPoint(-6.0, 21.67, 1000, true, 90, false); // Loader #1
    kw::boomerang(-35, 38.20, 270, 0.4, 2500, true, 50);
    pros::delay(500);
    kw::moveToPoint(-17, 21.67, 1000, false, 80, false);
    kw::boomerang(-36, 9, 180, 0.5, 2000, false, 70);
    pros::Task([]{
        pros::delay(450);
            intakeMacro("R1");
            pros::delay(1500);
            intakeMacro("L1");
    });
    kw::moveToPoint(-37.5, 18, 1000, false);
    loaderPiston.set_value(true);
    kw::move_raw(-7000, -7000);
    pros::delay(1500);
    kw::moveToPoint(-37.5, -5, 1000, true, 127, false);
    kw::moveToPoint(-37.5, -13, 900, true, 60);
    kw::move_raw(6000, 6000);
    // pros::delay(100);
    pros::Task([]{
        pros::delay(2000);
        intakeMacro("R2");
        pros::delay(1500);
        intakeMacro("L1");
        intake.move_voltage(0);
    });
    kw::boomerang(-2, 34 , 215, 0.3, 2000 , false, 90);
    kw::move_raw(-6000, -6000);
    // pros::delay(600);
    // kw::moveToPoint(-28, 17, 1000);
    // kw::turnToAngle(180, 700);
    // kw::moveToPoint(-30, 37, 1000, false);



}

void left_7() {

   pros::Task([] {
        intakeMacro("L1");
        pros::delay(600);
        loaderPiston.set_value(true);
        blockerPiston.set_value(true);
    });
    kw::moveToPoint(-5.8, 21.67, 1000, true, 90, false); // Loader #1
    kw::turnToAngle(233, 700);
    kw::moveToPoint(-30.59, 1.93, 2000, true, 127); 
    kw::turnToAngle(180, 700);
    kw::moveToPoint(-32.95, -10, 1100, true, 70); // Long Goal #1
    //kw::driveTo(3, 1000, 70);
    kw::move_raw(7000, 7000);
    pros::delay(170);
    pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(400);
		intakeMacro("R1");
	});
    kw::moveToPoint(-32.79, 24.45, 1000, false, 127);
    kw::move_raw(-5000, -5000);
    pros::delay(1600);
    kw::moveToPoint(-23.23, 16.94, 1000, true, 120);
    kw::turnToAngle(180, 700);
    intake.move_voltage(0);
    kw::moveToPoint(-23.73, 33.34, 8000, false);
    // kw::turnToAngle(180, 700);
    //kw::driveTo(-1, 1000, 70);
    stopIntake();
    loaderPiston.set_value(false);
    kw::boomerang(-25, 31, 226, 0.3, 1000, true, 100);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);

    
   // **old Stuff below**
   
    //  toggleColourSort = true;
    //  intakeMacro("L1");
    //  pros::Task([] {
    //     pros::delay(750);
    //     loaderPiston.set_value(true);
    // });
    // kw::driveTo(28.5, 2000, 60);
    // kw::turnToAngle(236, 1000);
    // kw::moveToPoint(-30, 17, 2000);
    // kw::turnToAngle(200, 1000);    
    // kw::moveToPoint(-34.37, 2.7, 1000, true, 70);
    // kw::move_raw(3000, 3000);
    // pros::delay(70);
    // //pros::delay(50);
    // //kw::driveTo(-33, 1000);
    // kw::moveToPoint(-25.2, 33.3, 1000, false);
    // kw::move_raw(-10000, -10000);
    // //stopIntake();
    // pros::delay(200);
    // //toggleColourSort = true;
    // intakeMacro("R1");
    // loaderPiston.set_value(false);
    // pros::delay(2300);
    // stopIntake();
    // kw::moveToPoint(-20.7, 10, 1000);
    // kw::turnToAngle(204, 1000);
    // kw::moveToPoint(-8.7, 48, 8000, false, 60);
    //     kw::turnToAngle(204, 1000);
    // //kw::driveTo(-7, 1000);

}

void right_7() {
pros::Task([] {
        intakeMacro("L1");
        pros::delay(600);
        loaderPiston.set_value(true);
        blockerPiston.set_value(true);
    });
    kw::moveToPoint(5.8, 21.67, 1000, true, 90, false); // Loader #1
    kw::turnToAngle(127, 700);
    kw::moveToPoint(30.59, 1.93, 2000, true, 127); 
    kw::turnToAngle(180, 700);
    kw::moveToPoint(32.95, -10, 1100, true, 70); // Long Goal #1
    //kw::driveTo(3, 1000, 70);
    kw::move_raw(7000, 7000);
    pros::delay(170);
    pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(400);
		intakeMacro("R1");
	});
    kw::moveToPoint(32.79, 24.45, 1000, false, 127);
    kw::move_raw(-5000, -5000);
    pros::delay(1600);
    kw::moveToPoint(47.5, 6, 1000, true);
    kw::turnToAngle(180, 700);
        intake.move_voltage(0);
    kw::moveToPoint(48, 36, 8000, false, 100);
    kw::turnToAngle(180, 700);
    kw::driveTo(-1, 1000, 70);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
    //old stuff below

//     toggleColourSort = false;
//      intakeMacro("L1");
//     kw::driveTo(28.5, 2000, 60);
//     kw::turnToAngle(124, 1000);
//     kw::moveToPoint(30, 17, 2000);
//     loaderPiston.set_value(true);
//     kw::turnToAngle(160, 1000);    
//     kw::moveToPoint(34.87, 2.7, 1500, true, 70);
//     kw::move_raw(7000, 7000);
//     pros::delay(50);
//     //kw::driveTo(-33, 1000);
//     kw::moveToPoint(25.0, 33.3, 1000, false);
//     kw::move_raw(-8000, -8000);
//     //stopIntake();
//     pros::delay(200);
//     toggleColourSort = true;
//     intakeMacro("R1");
//     loaderPiston.set_value(false);
//     pros::delay(2200);
//     stopIntake();
//     kw::moveToPoint(+38.1, 23.53, 1000);
//     kw::turnToAngle(164, 1000);
//     kw::moveToPoint(+30.0, 51, 8000, false, 70);
//     kw::driveTo(-7, 1000);
//     kw::turnToAngle(164, 1000);
}