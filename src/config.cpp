#include "deviceGlobals.hpp"
#include "main.h"
#include "libKW/api.hpp"

// ============================================================================
// USER-CONFIGURABLE PARAMETERS
// ============================================================================
// Distance between the middles of the left and right wheels of the drive (in inches)
double kw::distance_between_wheels = 11.8;

// motor to wheel gear ratio * wheel diameter (in inches) * pi
double kw::wheel_distance_in = (36.0 / 48.0) * 3.17 * M_PI;

// PID Constants for movement
// distance_* : Linear PID for straight driving
// turn_*     : PID for turning in place
// heading_correction_* : PID for heading correction during linear movement
double kw::distance_kp = 1.05, kw::distance_ki = 0.0, kw::distance_kd = 7.2;
double kw::turn_kp = 0.31, kw::turn_ki = 0.0, kw::turn_kd = 2.4;
double kw::heading_correction_kp = 0.6, kw::heading_correction_ki = 0, kw::heading_correction_kd = 4;

// Enable or disable the use of tracking wheels
bool kw::using_horizontal_tracker = true;  // Set to true if a horizontal tracking wheel is installed and used for odometry
bool kw::using_vertical_tracker = true;  // Set to true if a vertical tracking wheel is installed and used for odometry

// IGNORE THESE IF YOU ARE NOT USING TRACKING WHEELS
// These comments are in the perspective of a top down view of the robot when the robot is facing upwards on your view
// 2" wheels are actually 2.125
// 2.75" and onwards are accurate

// Horizontal distance from the center of the bot to the vertical tracking wheel (in inches, positive is when the wheel is behind the center of the robot)
double kw::horizontal_tracker_dist_from_center = 0.00; // must change to 3.44, the actual offset
double kw::horizontal_tracker_diameter = 2.125; // Diameter of the horizontal tracker wheel (in inches)

// Vertical distance from the center of the bot to the horizontal tracking wheel (in inches, positive is when the wheel is to the right of the center)
double kw::vertical_tracker_dist_from_center = 0.00;
double kw::vertical_tracker_diameter = 2.125; // Diameter of the vertical tracker wheel (in inches)

// ============================================================================
// ADVANCED TUNING (OPTIONAL)
// ============================================================================

bool kw::heading_correction = true; // Use heading correction when the bot is stationary
// Set to true for more accuracy and smoothness, false for more speed
bool kw::dir_change_start = true;   // Less accel/decel due to expecting direction change at start of movement
bool kw::dir_change_end = true;     // Less accel/decel due to expecting direction change at end of movement

double kw::min_output = 2; // Minimum output voltage to motors while chaining movements

// Maximum allowed change in voltage output per 10 msec during movement
double kw::max_slew_accel_fwd = 16;
double kw::max_slew_decel_fwd = 20;
double kw::max_slew_accel_rev = 16;
double kw::max_slew_decel_rev = 20;

// Prevents too much slipping during boomerang movements
// Decrease if there is too much drifting and inconsistency during boomerang
// Increase for more speed during boomerang
double kw::chase_power = 4;
