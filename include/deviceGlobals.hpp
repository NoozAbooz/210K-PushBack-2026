#pragma once
#include "main.h"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain

// v1
inline pros::MotorGroup leftDrive({-11, -12, 13});
inline pros::MotorGroup rightDrive({-16, 15, 14});

// Intake
inline pros::Motor intakeMiddleLower(-4); // yes
inline pros::Motor intakeMiddleUpper(8); // yes
inline pros::Motor intakeTop(10); // 11w flexwheel for goal height
inline pros::Motor intakeBottom(9); // preroller

// Pneumatics
inline pros::adi::Pneumatics knockerPiston('X', false);
inline pros::adi::Pneumatics loaderPiston('X', false); // matchloader
inline pros::adi::Pneumatics intakeLiftPiston('X', false);

/* Declare sensors */
inline pros::Imu inertial1(7);
inline pros::Imu inertial2(19);
inline pros::Optical optical(17);

inline pros::Distance fwdDistance(11);
inline pros::Distance rightDistance(18);

inline pros::Rotation verticalEncoder(5);
inline pros::Rotation horizontalEncoder(-20);
//hello world it is 210K secret note iykyk :D

namespace kw {
// ============================================================================
// USER-CONFIGURABLE PARAMETERS
// ============================================================================
// Distance between the middles of the left and right wheels of the drive (in inches)
inline double distance_between_wheels = 12.3;

// motor to wheel gear ratio * wheel diameter (in inches) * pi
inline double wheel_distance_in = (36.0 / 48.0) * 3.17 * M_PI;

// PID Constants for movement
// distance_* : Linear PID for straight driving
// turn_*     : PID for turning in place
// heading_correction_* : PID for heading correction during linear movement
inline double distance_kp = 1.1, distance_ki = 0.1, distance_kd = 7;
inline double turn_kp = 0.3, turn_ki = 0, turn_kd = 2.5;
inline double heading_correction_kp = 0.6, heading_correction_ki = 0, heading_correction_kd = 4;

// Enable or disable the use of tracking wheels
inline bool using_horizontal_tracker = true;  // Set to true if a horizontal tracking wheel is installed and used for odometry
inline bool using_vertical_tracker = true;   // Set to true if a vertical tracking wheel is installed and used for odometry

// IGNORE THESE IF YOU ARE NOT USING TRACKING WHEELS
// These comments are in the perspective of a top down view of the robot when the robot is facing upwards on your view

// Horizontal distance from the center of the bot to the vertical tracking wheel (in inches, positive is when the wheel is to the right of the center)
inline double horizontal_tracker_dist_from_center = 2.71875;
inline double horizontal_tracker_diameter = 1.975; // Diameter of the horizontal tracker wheel (in inches)

// Vertical distance from the center of the bot to the horizontal tracking wheel (in inches, positive is when the wheel is behind the center of the robot)
inline double vertical_tracker_dist_from_center = -0.03125;
inline double vertical_tracker_diameter = 1.975; // Diameter of the vertical tracker wheel (in inches)

// ============================================================================
// ADVANCED TUNING (OPTIONAL)
// ============================================================================

inline bool heading_correction = true; // Use heading correction when the bot is stationary
// Set to true for more accuracy and smoothness, false for more speed
inline bool dir_change_start = true;   // Less accel/decel due to expecting direction change at start of movement
inline bool dir_change_end = true;     // Less accel/decel due to expecting direction change at end of movement

inline double min_output = 10; // Minimum output voltage to motors while chaining movements

// Maximum allowed change in voltage output per 10 msec during movement
inline double max_slew_accel_fwd = 24;
inline double max_slew_decel_fwd = 24;
inline double max_slew_accel_rev = 24;
inline double max_slew_decel_rev = 24;

// Prevents too much slipping during boomerang movements
// Decrease if there is too much drifting and inconsistency during boomerang
// Increase for more speed during boomerang
inline double chase_power = 2;
}