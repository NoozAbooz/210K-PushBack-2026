#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

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
    intakeMacro("L1");
    wingPiston.set_value(true);
    kw::driveTo(28.5, 2000, 50);
    kw::moveToPoint(-14, 48, 1000);
    pros::delay(400);
    kw::moveToPoint(0, 22, 1000, false);
    kw::turnToAngle(236, 1000);
    kw::moveToPoint(-31, 17, 2000);
    loaderPiston.set_value(true);
    kw::turnToAngle(200, 1000);    
    kw::moveToPoint(-36.5, 3, 1500, true, 80);
    kw::move_raw(3000, 3000);
    pros::delay(200);
    //kw::driveTo(-33, 1000);
    kw::moveToPoint(-25.8, 32.3, 1000, false);
    kw::move_raw(-8000, -8000);
    pros::delay(700);
    intakeMacro("R1");
    kw::move_raw(0,0);
    pros::delay(1500);
    stopIntake();
    kw::moveToPoint(-22.3, 10, 1000);
    kw::turnToAngle(200, 1000);
    kw::moveToPoint(-7, 46, 8000, false, 50);
}

void left_7() {

     toggleColourSort = true;
     intakeMacro("L1");
     pros::Task([] {
        pros::delay(750);
        loaderPiston.set_value(true);
    });
    kw::driveTo(28.5, 2000, 60);
    kw::turnToAngle(236, 1000);
    kw::moveToPoint(-30, 17, 2000);
    kw::turnToAngle(200, 1000);    
    kw::moveToPoint(-34.37, 2.7, 1500, true, 70);
    kw::move_raw(3000, 3000);
    pros::delay(150);
    //pros::delay(50);
    //kw::driveTo(-33, 1000);
    kw::moveToPoint(-25.2, 33.3, 1000, false);
    kw::move_raw(-10000, -10000);
    //stopIntake();
    pros::delay(200);
    //toggleColourSort = true;
    intakeMacro("R1");
    loaderPiston.set_value(false);
    pros::delay(2300);
    stopIntake();
    kw::moveToPoint(-20.7, 10, 1000);
    kw::turnToAngle(204, 1000);
    kw::moveToPoint(-8.7, 48, 8000, false, 60);
        kw::turnToAngle(204, 1000);
    //kw::driveTo(-7, 1000);

}

void right_7() {
    toggleColourSort = false;
     intakeMacro("L1");
    kw::driveTo(28.5, 2000, 60);
    kw::turnToAngle(124, 1000);
    kw::moveToPoint(30, 17, 2000);
    loaderPiston.set_value(true);
    kw::turnToAngle(160, 1000);    
    kw::moveToPoint(34.87, 2.7, 1500, true, 70);
    kw::move_raw(7000, 7000);
    pros::delay(50);
    //kw::driveTo(-33, 1000);
    kw::moveToPoint(25.0, 33.3, 1000, false);
    kw::move_raw(-8000, -8000);
    //stopIntake();
    pros::delay(200);
    toggleColourSort = true;
    intakeMacro("R1");
    loaderPiston.set_value(false);
    pros::delay(2200);
    stopIntake();
    kw::moveToPoint(+38.1, 23.53, 1000);
    kw::turnToAngle(164, 1000);
    kw::moveToPoint(+30.0, 51, 8000, false, 70);
    kw::driveTo(-7, 1000);
    kw::turnToAngle(164, 1000);
}