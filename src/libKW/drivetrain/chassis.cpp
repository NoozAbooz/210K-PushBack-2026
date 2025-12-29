#include "main.h"
#include "libKW/api.hpp"

// opcontrol
double kw::drive_curve(double input, double curve) {
    return (std::pow(2.718, -(curve / 10)) + std::pow(2.718, (std::fabs(input) - 127) / 10) * (1 - std::pow(2.718, -(curve / 10)))) * input;
}

void kw::drive_arcade(int linCurve, int rotCurve, double turnScale) {
    double power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double rawTurn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    if (linCurve != 0) {
        // poll joystick input and convert to mv, then run through drive_curve function
        power = kw::drive_curve(power, linCurve);
    }
    if (rotCurve != 0) {
        // poll joystick input and convert to mv, then run through drive_curve function
        rawTurn = kw::drive_curve(rawTurn, rotCurve);
    }

    // move motors based on direction (eg move left more when turn is positive)
    leftDrive.move_voltage((power + rawTurn * turnScale) * (12000.0 / 127));
    rightDrive.move_voltage((power - rawTurn * turnScale) * (12000.0 / 127));
}

void kw::move_raw(double left, double right) { // in millivolts, non-blocking
    leftDrive.move_voltage(left);
    rightDrive.move_voltage(right);
}

void kw::stop_chassis(pros::motor_brake_mode_e_t mode) {
    if (mode == pros::E_MOTOR_BRAKE_HOLD) {
        leftDrive.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rightDrive.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    } else if (mode == pros::E_MOTOR_BRAKE_COAST) {
        leftDrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        rightDrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    } else if (mode == pros::E_MOTOR_BRAKE_BRAKE) {
        leftDrive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        rightDrive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    }
    leftDrive.brake();
    rightDrive.brake();
}