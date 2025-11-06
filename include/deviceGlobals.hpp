#pragma once
#include "main.h"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain

// v2
inline pros::MotorGroup leftDrive({-11, -12, 14});
inline pros::MotorGroup rightDrive({13, 15, -16});

// Intake
inline pros::Motor intakeMiddleLower(-3); // yes
inline pros::Motor intakeMiddleUpper(10); // yes
inline pros::Motor intakeTop(-10); // 11w flexwheel for goal height
inline pros::Motor intakeBottom(-7); // preroller

// Pneumatics
inline pros::adi::Pneumatics knockerPiston('G', false);
inline pros::adi::Pneumatics loaderPiston('E', false); // matchloader
inline pros::adi::Pneumatics intakeLiftPiston('H', false);

/* Declare sensors */
inline pros::Imu inertial1(5); // should always be the less scuffed one
inline pros::Imu inertial2(9); // less scuffed one
inline pros::Optical optical(4);

inline pros::Distance fwdDistance(11);
inline pros::Distance rightDistance(18);

inline pros::Rotation verticalEncoder(6);
inline pros::Rotation horizontalEncoder(-17);
//hello world it is 210K secret note iykyk :D