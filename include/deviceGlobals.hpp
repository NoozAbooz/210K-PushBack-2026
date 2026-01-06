#pragma once
#include "main.h"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain

// v2
inline pros::MotorGroup leftDrive({-8, -9, 19});
inline pros::MotorGroup rightDrive({2, 3, -15});

// Intake
inline pros::Motor intakeMiddleLower(-0); // very top roller
inline pros::Motor intakeMiddleUpper(0); // yes
inline pros::Motor intakeTop(-0); // 11w flexwheel for goal height
inline pros::Motor intakeBottom(-0); // preroller
inline pros::MotorGroup intake({20, -11});

// Pneumatics
inline pros::adi::Pneumatics loaderPiston('D', false); // matchloader
inline pros::adi::Pneumatics trapdoorPiston('H', false);
inline pros::adi::Pneumatics intakePullDownPiston('A', false); // midgoal
inline pros::adi::Pneumatics wingPiston('B', false);
inline pros::adi::Pneumatics blockerPiston('G', false);

/* Declare sensors */
inline pros::Imu inertial1(16); // should always be the less scuffed one
inline pros::Imu inertial2(14); // less scuffed one
inline pros::Optical optical(0);

inline pros::Distance fwdDistance(0);
inline pros::Distance rightDistance(0);
inline pros::Distance intakeDistance(0);

inline pros::Rotation verticalEncoder(13);
inline pros::Rotation horizontalEncoder(-12);
//hello world it is 210K secret note iykyk :D