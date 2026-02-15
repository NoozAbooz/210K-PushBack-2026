#pragma once
#include "main.h"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain

// v2
inline pros::MotorGroup leftDrive({-8, -9, 10});
inline pros::MotorGroup rightDrive({1, 3, -2});

// Intake
inline pros::Motor intakeMiddleLower(-0); // very top roller
inline pros::Motor intakeMiddleUpper(0); // yes
inline pros::Motor intakeTop(-0); // 11w flexwheel for goal height
inline pros::Motor intakeBottom(-0); // preroller
inline pros::MotorGroup intake({20, -11}, pros::v5::MotorGears::ratio_6_to_1);

// Pneumatics
inline pros::adi::Pneumatics loaderPiston('F', false); // matchloader
inline pros::adi::Pneumatics trapdoorPiston('A', false);
inline pros::adi::Pneumatics intakePullDownPiston('B', false); // midgoal
inline pros::adi::Pneumatics wingPiston('G', false);
inline pros::adi::Pneumatics blockerPiston('H', false);

/* Declare sensors */
inline pros::Imu inertial1(16); // should always be the less scuffed one
inline pros::Imu inertial2(15); // less scuffed one
inline pros::Optical optical(0);

inline pros::Distance bwdDistance(6);
inline pros::Distance leftDistance(18);
inline pros::Distance rightDistance(5);
inline pros::Distance fwdDistance(19);

inline pros::Rotation verticalEncoder(7);
inline pros::Rotation horizontalEncoder(-4);
//hello world it is 210K secret note iykyk :D
