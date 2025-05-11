#include "main.h"

void ks::moveRaw(int voltage, int time) {
	leftDrive.move_voltage(voltage);
	rightDrive.move_voltage(voltage);

	pros::delay(time);

	leftDrive.move_voltage(0);
	rightDrive.move_voltage(0);
}

void ks::moveStraight(float length, int timeout, lemlib::MoveToPointParams params) {
    if (chassis.isInMotion()) chassis.waitUntilDone();
    params.forwards = length > 0;
    lemlib::Pose pose = chassis.getPose();
    chassis.moveToPoint(pose.x + length * sin(lemlib::degToRad(pose.theta)),
                           pose.y + length * cos(lemlib::degToRad(pose.theta)), timeout, params);
}

// opcontrol
double ks::driveCurve(double input, double curve) {
    return (std::pow(2.718, -(curve / 10)) + std::pow(2.718, (std::fabs(input) - 127) / 10) * (1 - std::pow(2.718, -(curve / 10)))) * input;
}

void ks::arcadeDrive(int linCurve, int rotCurve, double turnScale) {
    double power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double rawTurn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    if (linCurve != 0) {
        // poll joystick input and convert to mv, then run through drivecurve function
        power = ks::driveCurve(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), linCurve);
    }
    if (rotCurve != 0) {
        // poll joystick input and convert to mv, then run through drivecurve function
        rawTurn = ks::driveCurve(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), rotCurve);
    }

    // move motors based on direction (eg move left more when turn is positive)
    leftDrive.move_voltage((power + rawTurn * turnScale) * (12000.0 / 127));
    rightDrive.move_voltage((power - rawTurn * turnScale) * (12000.0 / 127));
}