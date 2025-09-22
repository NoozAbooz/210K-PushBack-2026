#include "main.h"

// ============================================================================
// INTERNAL STATE (DO NOT CHANGE)
// ============================================================================
bool is_turning = false;
double prev_left_output = 0, prev_right_output = 0;

// opcontrol
double kw::driveCurve(double input, double curve) {
    return (std::pow(2.718, -(curve / 10)) + std::pow(2.718, (std::fabs(input) - 127) / 10) * (1 - std::pow(2.718, -(curve / 10)))) * input;
}

void kw::arcadeDrive(int linCurve, int rotCurve, double turnScale) {
    double power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double rawTurn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    if (linCurve != 0) {
        // poll joystick input and convert to mv, then run through drivecurve function
        power = kw::driveCurve(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), linCurve);
    }
    if (rotCurve != 0) {
        // poll joystick input and convert to mv, then run through drivecurve function
        rawTurn = kw::driveCurve(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), rotCurve);
    }

    // move motors based on direction (eg move left more when turn is positive)
    leftDrive.move_voltage((power + rawTurn * turnScale) * (12000.0 / 127));
    rightDrive.move_voltage((power - rawTurn * turnScale) * (12000.0 / 127));
}

void kw::moveStraight(float length, int timeout, lemlib::MoveToPointParams params) {
    if (chassis.isInMotion()) chassis.waitUntilDone();
    params.forwards = length > 0;
    lemlib::Pose pose = chassis.getPose();
    chassis.moveToPoint(pose.x + length * sin(lemlib::degToRad(pose.theta)),
                           pose.y + length * cos(lemlib::degToRad(pose.theta)), timeout, params);
}

