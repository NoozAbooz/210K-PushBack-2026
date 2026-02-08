#include "main.h"
#include "libKW/api.hpp"
using namespace kw;

/*
 * Drives the robot a specified distance (in inches) using PID control.
 * - distance_in: Target distance to drive (positive or negative).
 * - time_limit_msec: Maximum time allowed for the move (in milliseconds).
 * - max_output: Maximum voltage output to motors.
 * - exit: If true, stops the robot at the end; if false, allows chaining.
 * - async: If true, runs the drive in a separate task and returns immediately.
 */
void kw::driveTo(double distance_in, double time_limit_msec, double max_output, bool exit, bool async, double minimum_speed) {
  if(async) {
    pros::Task task([&]() { 
      kw::driveTo(distance_in, time_limit_msec, max_output, exit);
    });
    pros::delay(10);
    return;
  }

  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  // Store initial dist travelled (function comes from odom.cpp)
  kw::encoder_mutex.take();
  double start_vertical_pos = kw::get_vertical_distance_traveled();
  kw::encoder_mutex.give();

  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST); // Stop chassis before moving
  is_turning = true;
  double threshold = 0.5;
  int drive_direction = distance_in > 0 ? 1 : -1;
  double max_slew_fwd = drive_direction > 0 ? max_slew_accel_fwd : max_slew_decel_rev;
  double max_slew_rev = drive_direction > 0 ? max_slew_decel_fwd : max_slew_accel_rev;
  bool min_speed = false;
  if(!exit) {
    // Adjust slew rates and min speed for chaining
    if(!dir_change_start && dir_change_end) {
      max_slew_fwd = drive_direction > 0 ? 6 : max_slew_decel_rev;
      max_slew_rev = drive_direction > 0 ? max_slew_decel_fwd : 6;
    }
    if(dir_change_start && !dir_change_end) {
      max_slew_fwd = drive_direction > 0 ? max_slew_accel_fwd : 6;
      max_slew_rev = drive_direction > 0 ? 6 : max_slew_accel_rev;
      min_speed = true;
    }
    if(!dir_change_start && !dir_change_end) {
      max_slew_fwd = 6;
      max_slew_rev = 6;
      min_speed = true;
    }
  }

  distance_in = distance_in * drive_direction;
  PID pid_distance = PID(distance_kp, distance_ki, distance_kd);
  PID pid_heading = PID(heading_correction_kp, heading_correction_ki, heading_correction_kd);

  // Configure PID controllers
  pid_distance.setTarget(distance_in);
  pid_distance.setIntegralMax(3);  
  pid_distance.setSmallBigErrorTolerance(threshold, threshold * 3);
  pid_distance.setSmallBigErrorDuration(20, 100);
  pid_distance.setDerivativeTolerance(5);

  pid_heading.setTarget(normalize_target(correct_angle));
  pid_heading.setIntegralMax(0);  
  pid_heading.setIntegralRange(1);
  pid_heading.setSmallBigErrorTolerance(0, 0);
  pid_heading.setSmallBigErrorDuration(0, 0);
  pid_heading.setDerivativeTolerance(0);
  pid_heading.setArrive(false);

  double start_time = pros::millis();
  double left_output = 0, right_output = 0, correction_output = 0;
  double current_distance = 0, current_angle = 0;

  // Main PID loop for driving straight
  while (((!pid_distance.targetArrived()) && pros::millis() - start_time <= time_limit_msec && exit) || (exit == false && current_distance < distance_in && pros::millis() - start_time <= time_limit_msec)) {
    // Calculate current distance and heading
    kw::encoder_mutex.take();
    current_distance = fabs(get_vertical_distance_traveled() - start_vertical_pos);
    current_movement_error = distance_in - (get_vertical_distance_traveled() - start_vertical_pos); // used for kw::waitUntilDistance
    kw::encoder_mutex.give();

    current_angle = kw::get_imu_rotation();
    left_output = pid_distance.update(current_distance) * drive_direction;
    right_output = left_output;
    correction_output = pid_heading.update(current_angle);

    // Minimum Output Check
    if(min_speed) {
      scale_to_min(left_output, right_output, min_output);
    }
    
    if(!exit) {
      left_output = 24 * drive_direction;
      right_output = 24 * drive_direction;
    }

    left_output += correction_output;
    right_output -= correction_output;

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
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
  }
  is_turning = false;
}