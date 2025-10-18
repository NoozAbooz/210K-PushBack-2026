#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void right_elim() {
    intakeMacro("HOARD_L1");

    kw::driveTo(19.5, 1500);
    pros::delay(350);

    kw::driveTo(22.65, 1500);

    kw::turnToAngle(62, 1000);
    //intakeMacro("L1");
    kw::driveTo(12, 1000, 127);
    kw::turnToAngle(72.5, 1000);
    loaderPiston.set_value(true); // lower matchloader to gather balls
    pros::delay(250);
    kw::driveTo(-10, 800);
    pros::delay(300);
    kw::turnToAngle(143.5, 1000);
    kw::driveTo(47.5, 2000);
    kw::turnToAngle(164, 1000);
    intakeMacro("L1");
    kw::driveTo(7, 500);
    pros::delay(400);
    kw::driveTo(-28, 1500, 127, false);
    pros::delay(1500);
    intakeMacro("HOARD_R1");
  

}

void left_elim() {

}