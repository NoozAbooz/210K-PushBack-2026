#include "main.h"
#include "libKW/api.hpp"
using namespace kw;

/*
 * moveToPoint
 * Moves the robot to a specific point in the field, adjusting heading as needed.
 * - x, y: Coordinates of the target point.
 * - time_limit_msec: Maximum time allowed for the move (in milliseconds).
 * - forwards: Direction to move in (true (default) for forward, false for backward).
 * - max_output: Maximum voltage output to motors.
 * - exit: If true, stops the robot at the end; if false, allows chaining.
 * - overturn: If true, allows overturning for sharp turns.
 * - async: If true, runs the drive in a separate task and returns immediately.
 */
void kw::moveToPoint(double x, double y, double time_limit_msec, bool forwards, double max_output, bool exit, bool overturn, bool async, double minimum_speed) {
  if(async) {
    pros::Task task([&]() { 
      kw::moveToPoint(x, y, time_limit_msec, forwards, max_output, exit, overturn);
    });
    pros::delay(10);
    return;
  }

  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST); // Stop chassis before moving
  is_turning = true;                  // Set turning state
  double threshold = 1;
  int add = forwards ? 0 : 180; // if driving backwards, add 180 degrees to heading
  double max_slew_fwd = forwards ? max_slew_accel_fwd : max_slew_decel_rev; // switch slew rate used based on direction
  double max_slew_rev = forwards ? max_slew_decel_fwd : max_slew_accel_rev;
  bool min_speed = false;
  if(!exit) {
    // Adjust slew rates and min speed for chaining
    if(!dir_change_start && dir_change_end) {
      max_slew_fwd = forwards ? 12 : max_slew_decel_rev;
      max_slew_rev = forwards ? max_slew_decel_fwd : 12;
    }
    if(dir_change_start && !dir_change_end) {
      max_slew_fwd = forwards ? max_slew_accel_fwd : 12;
      max_slew_rev = forwards ? 12 : max_slew_accel_rev;
      min_speed = true;
    }
    if(!dir_change_start && !dir_change_end) {
      max_slew_fwd = 12;
      max_slew_rev = 12;
      min_speed = false;
    }
  }

  PID pid_distance = PID(distance_kp, distance_ki, distance_kd);
  PID pid_heading = PID(heading_correction_kp, heading_correction_ki, heading_correction_kd);

  // Set PID targets for distance and heading
  pid_distance.setTarget(hypot(x - x_pos, y - y_pos));
  pid_distance.setIntegralMax(0);  
  pid_distance.setIntegralRange(3);
  pid_distance.setSmallBigErrorTolerance(threshold, threshold * 3);
  pid_distance.setSmallBigErrorDuration(50, 250);
  pid_distance.setDerivativeTolerance(5);
  
  pid_heading.setTarget(normalize_target(kw::to_deg(atan2(x - x_pos, y - y_pos)) + add));
  pid_heading.setIntegralMax(0);  
  pid_heading.setIntegralRange(1);
  
  pid_heading.setSmallBigErrorTolerance(0, 0);
  pid_heading.setSmallBigErrorDuration(0, 0);
  pid_heading.setDerivativeTolerance(0);
  pid_heading.setArrive(false);

  // Reset the chassis
  double start_time = pros::millis();
  double left_output = 0, right_output = 0, correction_output = 0, prev_left_output = 0, prev_right_output = 0;
  double exittolerance = 1;
  bool perpendicular_line = false, prev_perpendicular_line = true;

  double current_angle = 0, overturn_value = 0;
  bool ch = true;

  // Main PID loop for moving to point
  while (pros::millis() - start_time <= time_limit_msec) {
    // Continuously update targets as robot moves
    //kw::odom_mutex.take();

    pid_heading.setTarget(normalize_target(kw::to_deg(atan2(x - x_pos, y - y_pos)) + add));
    pid_distance.setTarget(hypot(x - x_pos, y - y_pos));
    current_angle = kw::get_imu_rotation();
    // Calculate drive output based on heading and distance
    left_output = pid_distance.update(0) * cos(kw::to_rad(atan2(x - x_pos, y - y_pos) * 180 / M_PI + add - current_angle)) * (forwards ? 1 : -1); // multiply by -1 if driving backwards
    right_output = left_output;
    // Check if robot has crossed the perpendicular line to the target
    perpendicular_line = ((y_pos - y) * -cos(kw::to_rad(normalize_target(current_angle + add))) <= (x_pos - x) * sin(kw::to_rad(normalize_target(current_angle + add))) + exittolerance);
    if(perpendicular_line && !prev_perpendicular_line) {
      break;
    }
    prev_perpendicular_line = perpendicular_line;

    // Only apply heading correction if far from target
    if(hypot(x - x_pos, y - y_pos) > 8 && ch == true) {
      correction_output = pid_heading.update(current_angle);
    } else {
      correction_output = 0;
      ch = false;
    }
    //kw::odom_mutex.give();

    // Minimum Output Check
    if(min_speed) {
      scale_to_min(left_output, right_output, min_output);
    }

    // Overturn logic for sharp turns
    overturn_value = fabs(left_output) + fabs(correction_output) - max_output;
    if(overturn_value > 0 && overturn) {
      if(left_output > 0) {
        left_output -= overturn_value;
      }
      else {
        left_output += overturn_value;
      }
    }
    right_output = left_output;
    left_output = left_output + correction_output;
    right_output = right_output - correction_output;

    // Max Output Check
    scale_to_max(left_output, right_output, max_output);

    // Max Acceleration/Deceleration Check
    if(prev_left_output - left_output > max_slew_rev) {
      left_output = prev_left_output - max_slew_rev;
    }
    if(prev_right_output - right_output > max_slew_rev) {
      right_output = prev_right_output - max_slew_rev;
    }
    if(left_output - prev_left_output > max_slew_fwd) {
      left_output = prev_left_output + max_slew_fwd;
    }
    if(right_output - prev_right_output > max_slew_fwd) {
      right_output = prev_right_output + max_slew_fwd;
    }
    prev_left_output = left_output;
    prev_right_output = right_output;

    if (minimum_speed > 0.0) {
      left_output = (left_output > 0.0) ? std::max((float)left_output, (float)minimum_speed) : std::min((float)left_output, -(float)minimum_speed);
    }

    left_output = kw::volt_to_milivolt(left_output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
	  right_output = kw::volt_to_milivolt(right_output);
    kw::move_raw(left_output, right_output); // send mv value
    pros::delay(10);
  } 
  if(exit) {
    prev_left_output = 0;
    prev_right_output = 0;
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD); // Stop at end if required
  }
  correct_angle = kw::get_imu_rotation(); // Update global heading
  is_turning = false;                   // Reset turning state
}