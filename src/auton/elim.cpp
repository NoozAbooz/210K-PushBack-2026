#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void right_elim() {
    intakeMacro("L1");
    kw::driveTo(28.5, 1500, 70);
    kw::moveToPoint(13, 49, 1000);
    pros::delay(400);
    kw::moveToPoint(3, 33, 1000, false);
    kw::turnToAngle(124, 1000);
    kw::moveToPoint(31, 17, 2000);
    loaderPiston.set_value(true);
    kw::turnToAngle(160, 1000);    
    kw::moveToPoint(36.5, 3, 1500, true, 80);
    kw::move_raw(3000, 3000);
    pros::delay(200);
    //kw::driveTo(-33, 1000);
    kw::moveToPoint(25.8, 32.3, 1000, false);
    kw::move_raw(-8000, -8000);
    pros::delay(200);
    intakeMacro("R1");
    kw::move_raw(0,0);
    pros::delay(3000);
    stopIntake();
    kw::moveToPoint(+44, 19, 1000);
    kw::turnToAngle(159, 1000);
    kw::moveToPoint(+28, 54, 8000, false, 50);

}

void left_elim() {
    intakeMacro("L1");
    kw::driveTo(28.5, 1500, 70);
    kw::moveToPoint(-13, 49, 1000);
    pros::delay(400);
    kw::moveToPoint(-3, 33, 1000, false);
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

    intakeMacro("L1");
    kw::driveTo(28.5, 1500, 70);
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
    pros::delay(1500);
    stopIntake();
    kw::moveToPoint(-22.3, 10, 1000);
    kw::turnToAngle(200, 1000);
    kw::moveToPoint(-7, 46, 8000, false, 60);

}

void right_7() {

     intakeMacro("L1");
    kw::driveTo(28.5, 1500, 70);
    kw::turnToAngle(124, 1000);
    kw::moveToPoint(31, 17, 2000);
    loaderPiston.set_value(true);
    kw::turnToAngle(160, 1000);    
    kw::moveToPoint(36.5, 3, 1500, true, 80);
    kw::move_raw(3000, 3000);
    pros::delay(200);
    //kw::driveTo(-33, 1000);
    kw::moveToPoint(25.8, 32.3, 1000, false);
    kw::move_raw(-8000, -8000);
    pros::delay(200);
    intakeMacro("R1");
    pros::delay(2000);
    stopIntake();
    kw::moveToPoint(+44, 19, 1000);
    kw::turnToAngle(159, 1000);
    kw::moveToPoint(+28, 54, 8000, false, 50);
}