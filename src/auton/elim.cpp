#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void right_elim() {
kw::boomerang(7, 17, 30, 0.8, 1000, true, 100, false);
kw::boomerang(34, 33, 90, 0.65, 2000, true, 90, true);
pros::Task([]{
    loaderPiston.set_value(true);
    });
pros::delay(400);
kw::moveToPoint(14, 32,  2000, false, 127);
pros::delay(1000);
kw::boomerang(34, -11, 158, 0.2, 3000, true, 90);
kw::turnToAngle(180, 1000);
kw::boomerang(33.0, 8, 180, 0.2, 3000, false , 60);
pros::delay(3000);
kw::boomerang(32.5, -25, 180, 0.2, 3000, true , 90);
pros::delay(1000);
kw::boomerang(33.0, 8, 180, 0.2, 3000, false , 60);

}

void left_elim() {

}