#pragma once
#include "main.h"

namespace kw {
	extern double distance_between_wheels;
	extern double wheel_distance_in;

	// PID Constants for movement
	// distance_* : Linear PID for straight driving
	// turn_*     : PID for turning in place
	// heading_correction_* : PID for heading correction during linear movement
	extern double distance_kp, distance_ki, distance_kd;
	extern double turn_kp, turn_ki, turn_kd;
	extern double heading_correction_kp, heading_correction_ki, heading_correction_kd;

	// Enable or disable the use of tracking wheels
	extern bool using_horizontal_tracker;  // Set to true if a horizontal tracking wheel is installed and used for odometry
	extern bool using_vertical_tracker;   // Set to true if a vertical tracking wheel is installed and used for odometry

	// Horizontal distance from the center of the bot to the vertical tracking wheel (in inches, positive is when the wheel is behind the center of the robot)
	extern double horizontal_tracker_dist_from_center;
	extern double horizontal_tracker_diameter; // Diameter of the horizontal tracker wheel (in inches)

	// Vertical distance from the center of the bot to the horizontal tracking wheel (in inches, positive is when the wheel is to the right of the center)
	extern double vertical_tracker_dist_from_center;
	extern double vertical_tracker_diameter; // Diameter of the vertical tracker wheel (in inches)

	// ============================================================================
	// ADVANCED TUNING (OPTIONAL)
	// ============================================================================

	extern bool heading_correction; // Use heading correction when the bot is stationary
	// Set to true for more accuracy and smoothness, false for more speed
	extern bool dir_change_start;   // Less accel/decel due to expecting direction change at start of movement
	extern bool dir_change_end;     // Less accel/decel due to expecting direction change at end of movement

	extern double min_output; // Minimum output voltage to motors while chaining movements

	// Maximum allowed change in voltage output per 10 msec during movement
	extern double max_slew_accel_fwd;
	extern double max_slew_decel_fwd;
	extern double max_slew_accel_rev;
	extern double max_slew_decel_rev;

	// Prevents too much slipping during boomerang movements
	// Decrease if there is too much drifting and inconsistency during boomerang
	// Increase for more speed during boomerang
	extern double chase_power;
}