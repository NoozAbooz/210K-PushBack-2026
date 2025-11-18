#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void right_elim() {
    kw::distance_kp = 1, kw::distance_ki = 0, kw::distance_kd = 8;
    kw::turn_kp = 0.3, kw::turn_ki = 0, kw::turn_kd = 2.8; // slime kp!!!!

    intakeMacro("L1");

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
    intakeBottom.move_voltage(-8000);
  

}

void left_elim() {
    intakeMacro("HOARD_L1");

    kw::driveTo(19.5, 1500);
    pros::delay(350);

    kw::driveTo(22.65, 1500);

    kw::turnToAngle(298, 1000);
    //intakeMacro("L1");
    kw::driveTo(12, 1000, 127);
    kw::turnToAngle(287.5, 1000);
    loaderPiston.set_value(true); // lower matchloader to gather balls
    pros::delay(250);
    kw::driveTo(-10, 800);
    pros::delay(300);
    kw::turnToAngle(216.5, 1000);
    kw::driveTo(47.5, 2000);
    kw::turnToAngle(196, 1000);
    intakeMacro("L1");
    kw::driveTo(7, 500);
    pros::delay(400);
    kw::driveTo(-28, 1500, 127, false);
    pros::delay(1500);
    intakeMacro("HOARD_R1");
    intakeBottom.move_voltage(-8000);
}