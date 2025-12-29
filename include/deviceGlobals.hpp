#pragma once
#include "main.h"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain

// v2
inline pros::MotorGroup leftDrive({-20, -9, 10});
inline pros::MotorGroup rightDrive({2, 11, -1});

// Intake
inline pros::Motor intakeMiddleLower(-12); // very top roller
inline pros::Motor intakeMiddleUpper(0); // yes
inline pros::Motor intakeTop(-18); // 11w flexwheel for goal height
inline pros::Motor intakeBottom(-19); // preroller

// Pneumatics
inline pros::adi::Pneumatics loaderPiston('B', false); // matchloader
inline pros::adi::Pneumatics wingPiston('C', false);
inline pros::adi::Pneumatics intakePullDownPiston('A', false);

/* Declare sensors */
inline pros::Imu inertial1(13); // should always be the less scuffed one
inline pros::Imu inertial2(16); // less scuffed one
inline pros::Optical optical(7);

inline pros::Distance fwdDistance(0);
inline pros::Distance rightDistance(17);
inline pros::Distance intakeDistance(3);

inline pros::Rotation verticalEncoder(14);
inline pros::Rotation horizontalEncoder(-8);
//hello world it is 210K secret note iykyk :D