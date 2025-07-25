#pragma once
#include "main.h"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain

// v1
inline pros::MotorGroup leftDrive({-1, -2, 3});
inline pros::MotorGroup rightDrive({-18, 19, 20});

// Intake
inline pros::MotorGroup intake({10, 9});
inline pros::Motor intakeTop(10);
inline pros::Motor intakeBottom(9);

// Pneumatics
inline pros::adi::Pneumatics liftPiston('A', false);
inline pros::adi::Pneumatics loaderPiston('B', false);
inline pros::adi::Pneumatics trapdoorPiston('C', false); // now for ratchet

/* Declare sensors */
inline pros::Imu inertial1(7);
inline pros::Imu inertial2(14);
inline pros::Optical optical(12);

inline pros::Rotation verticalEncoder(-5);
inline pros::Rotation horizontalEncoder(-6);
//hello world it is 210K secret note iykyk :D
// horizontal tracking wheel
inline lemlib::TrackingWheel vertical_tracking_wheel(&verticalEncoder, lemlib::Omniwheel::NEW_2, -0.244094);
// vertical tracking wheel
inline lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalEncoder, lemlib::Omniwheel::NEW_2, 0);

// drivetrain settings
inline lemlib::Drivetrain drivetrain(&leftDrive, // left motor group
                              &rightDrive, // right motor group
                              13.5, // track width
                              lemlib::Omniwheel::NEW_325,
                              450, // drivetrain rpm
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);
// lateral motion controller
inline lemlib::ControllerSettings lateralController(7.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              35, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);
// angular motion controller
inline lemlib::ControllerSettings angularController(5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              45, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
// sensors for odometry
// note that in this example we use internal motor encoders, so we don't pass vertical tracking wheels
inline lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to nullptr as we don't have one
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have one
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial1 // inertial sensor
);
// create the chassis
inline lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
