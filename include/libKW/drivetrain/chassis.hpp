#pragma once
#include "main.h"

namespace kw {
    extern double drive_curve(double input, double curve);
    extern void drive_arcade(int linCurve = 0, int rotCurve = 0, double turnScale = 1);

    extern void move_raw(double left, double right); // in millivolts, non-blocking
    extern void stop_chassis(pros::motor_brake_mode_e_t mode = pros::E_MOTOR_BRAKE_COAST);
}