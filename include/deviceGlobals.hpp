#pragma once
#include "main.h"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain

// v2
inline pros::MotorGroup leftDrive({-13, 12, -11});
inline pros::MotorGroup rightDrive({18, -19, 20});

// Intake
inline pros::MotorGroup intakeCounterRoller({-2}); // middle counter roller
inline pros::MotorGroup intakeMain({3}, pros::v5::MotorGears::ratio_6_to_1); // 11w
inline pros::MotorGroup intakeSub({10}); // 5.5w
inline pros::MotorGroup intake({0, 0}); //main 16.5W system

// Pneumatics
inline pros::adi::Pneumatics loaderPiston('F', false); // matchloader
inline pros::adi::Pneumatics trapdoorPiston('A', false);
inline pros::adi::Pneumatics intakePullDownPiston('B', false); // midgoal
inline pros::adi::Pneumatics wingPiston('G', false);
inline pros::adi::Pneumatics wing2Piston('E', false);
inline pros::adi::Pneumatics blockerPiston('H', false);

/* Declare sensors */
inline pros::Imu inertial1(15); // should always be the less scuffed one
inline pros::Imu inertial2(16); // less scuffed one
inline pros::Optical optical(0);
inline pros::Optical parkColour(0);

inline pros::Distance bwdDistance(0);
inline pros::Distance leftDistance(0);
inline pros::Distance rightDistance(0);
inline pros::Distance fwdDistance(0);

inline pros::Rotation verticalEncoder(-17);
inline pros::Rotation horizontalEncoder(14);
//hello world it is 210K secret note iykyk :D
