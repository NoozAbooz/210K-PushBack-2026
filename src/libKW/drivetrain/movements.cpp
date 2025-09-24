#include "main.h"
using namespace kw;

// ============================================================================
// INTERNAL STATE (DO NOT CHANGE)
// ============================================================================
bool is_turning = false;
double prev_left_output = 0, prev_right_output = 0;

// ============================================================================
// MAIN DRIVE AND TURN FUNCTIONS
// ============================================================================
// Sidenote: These functions do voltage calcultions in volts, then convert to millivolts for motor commands
// input values (such as [-127, 127]) are converted to volts internally in the functions

/*
 * Turns the robot to a specified angle using PID control.
 * - turn_angle: Target angle to turn to (in degrees).
 * - time_limit_msec: Maximum time allowed for the turn (in milliseconds).
 * - exit: If true, stops the robot at the end; if false, allows chaining.
 * - max_output: Maximum output to motors. (0, 127]
 */
void turnToAngle(double turn_angle, double time_limit_msec, double max_output, bool exit) {
  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  // Prepare for turn
  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST);
  is_turning = true;
  double threshold = 1;
  kw::PID pid = kw::PID(kw::turn_kp, kw::turn_ki, kw::turn_kd);

  // Normalize and set PID target
  turn_angle = kw::normalizeTarget(turn_angle);
  pid.setTarget(turn_angle);
  pid.setIntegralMax(0);  
  pid.setIntegralRange(3);
  pid.setSmallBigErrorTolerance(threshold, threshold * 3);
  pid.setSmallBigErrorDuration(50, 250);
  pid.setDerivativeTolerance(threshold * 4.5);

  // PID loop for turning
  double start_time = pros::millis();
  double output;
  double current_heading = kw::get_imu_rotation();
  double previous_heading = 0;
  if(exit == false && correct_angle < turn_angle) {
    // Turn right without stopping at end
    while (kw::get_imu_rotation() < turn_angle && pros::millis() - start_time <= time_limit_msec) {
      current_heading = kw::get_imu_rotation();
      output = pid.update(current_heading); // PID update for heading

      previous_heading = current_heading;
      // Clamp output
      if(output < min_output) output = min_output;
      if(output > max_output) output = max_output;
      else if(output < -max_output) output = -max_output;

	  output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
      kw::move_raw(output, -output); // send mv value
      pros::delay(10);
    }
  } else if(exit == false && correct_angle > turn_angle) {
    // Turn left without stopping at end
    while (kw::get_imu_rotation() > turn_angle && pros::millis() - start_time <= time_limit_msec) {
      current_heading = kw::get_imu_rotation();
      output = pid.update(current_heading);
	  
      previous_heading = current_heading;
      if(output < min_output) output = min_output;
      if(output > max_output) output = max_output;
      else if(output < -max_output) output = -max_output;
      
	  output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
      kw::move_raw(-output, output); // send mv value
      pros::delay(10);
    }
  } else {
    // Standard PID turn
    while (!pid.targetArrived() && pros::millis() - start_time <= time_limit_msec) {
      current_heading = kw::get_imu_rotation();
      output = pid.update(current_heading);

      previous_heading = current_heading;
      if(output > max_output) output = max_output;
      else if(output < -max_output) output = -max_output;
      
	  output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
      kw::move_raw(output, -output); // send mv value
      pros::delay(10);
    }
  }
  if(exit) {
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
  }
  correct_angle = turn_angle;
  is_turning = false;
}

/*
 * Drives the robot a specified distance (in inches) using PID control.
 * - distance_in: Target distance to drive (positive or negative).
 * - time_limit_msec: Maximum time allowed for the move (in milliseconds).
 * - exit: If true, stops the robot at the end; if false, allows chaining.
 * - max_output: Maximum voltage output to motors.
 */
void driveTo(double distance_in, double time_limit_msec, double max_output, bool exit) {
  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  // Store initial dist travelled (function comes from odom.cpp)
  double start_vertical_pos = kw::get_vertical_distance_traveled();
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
      max_slew_fwd = drive_direction > 0 ? 24 : max_slew_decel_rev;
      max_slew_rev = drive_direction > 0 ? max_slew_decel_fwd : 24;
    }
    if(dir_change_start && !dir_change_end) {
      max_slew_fwd = drive_direction > 0 ? max_slew_accel_fwd : 24;
      max_slew_rev = drive_direction > 0 ? 24 : max_slew_accel_rev;
      min_speed = true;
    }
    if(!dir_change_start && !dir_change_end) {
      max_slew_fwd = 24;
      max_slew_rev = 24;
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
  pid_distance.setSmallBigErrorDuration(50, 250);
  pid_distance.setDerivativeTolerance(5);

  pid_heading.setTarget(normalizeTarget(correct_angle));
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
    current_distance = fabs(get_vertical_distance_traveled() - start_vertical_pos);
    current_angle = kw::get_imu_rotation();
    left_output = pid_distance.update(current_distance) * drive_direction;
    right_output = left_output;
    correction_output = pid_heading.update(current_angle);

    // Minimum Output Check
    if(min_speed) {
      scaleToMin(left_output, right_output, min_output);
    }
    if(!exit) {
      left_output = 24 * drive_direction;
      right_output = 24 * drive_direction;
    }

    left_output += correction_output;
    right_output -= correction_output;

    // Max Output Check
    scaleToMax(left_output, right_output, max_output);

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

/*
 * moveToPoint
 * Moves the robot to a specific point in the field, adjusting heading as needed.
 * - x, y: Coordinates of the target point.
 * - time_limit_msec: Maximum time allowed for the move (in milliseconds).
 * - forwards: Direction to move in (true (default) for forward, false for backward).
 * - exit: If true, stops the robot at the end; if false, allows chaining.
 * - max_output: Maximum voltage output to motors.
 * - overturn: If true, allows overturning for sharp turns.
 */
void moveToPoint(double x, double y, double time_limit_msec, bool forwards, double max_output, bool exit, bool overturn) {
  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST); // Stop chassis before moving
  is_turning = true;                  // Set turning state
  double threshold = 0.5;
  int add = forwards ? 0 : 180; // if driving backwards, add 180 degrees to heading
  double max_slew_fwd = forwards ? max_slew_accel_fwd : max_slew_decel_rev; // switch slew rate used based on direction
  double max_slew_rev = forwards ? max_slew_decel_fwd : max_slew_accel_rev;
  bool min_speed = false;
  if(!exit) {
    // Adjust slew rates and min speed for chaining
    if(!dir_change_start && dir_change_end) {
      max_slew_fwd = forwards ? 24 : max_slew_decel_rev;
      max_slew_rev = forwards ? max_slew_decel_fwd : 24;
    }
    if(dir_change_start && !dir_change_end) {
      max_slew_fwd = forwards ? max_slew_accel_fwd : 24;
      max_slew_rev = forwards ? 24 : max_slew_accel_rev;
      min_speed = true;
    }
    if(!dir_change_start && !dir_change_end) {
      max_slew_fwd = 24;
      max_slew_rev = 24;
      min_speed = true;
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
  
  pid_heading.setTarget(normalizeTarget(kw::to_deg(atan2(x - x_pos, y - y_pos)) + add));
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
    pid_heading.setTarget(normalizeTarget(kw::to_deg(atan2(x - x_pos, y - y_pos)) + add));
    pid_distance.setTarget(hypot(x - x_pos, y - y_pos));
    current_angle = kw::get_imu_rotation();
    // Calculate drive output based on heading and distance
    left_output = pid_distance.update(0) * cos(kw::to_rad(atan2(x - x_pos, y - y_pos) * 180 / M_PI + add - current_angle)) * (forwards ? 1 : -1); // multiply by -1 if driving backwards
    right_output = left_output;
    // Check if robot has crossed the perpendicular line to the target
    perpendicular_line = ((y_pos - y) * -cos(kw::to_rad(normalizeTarget(current_angle + add))) <= (x_pos - x) * sin(kw::to_rad(normalizeTarget(current_angle + add))) + exittolerance);
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

    // Minimum Output Check
    if(min_speed) {
      scaleToMin(left_output, right_output, min_output);
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
    scaleToMax(left_output, right_output, max_output);

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

    left_output = kw::volt_to_milivolt(left_output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
	right_output = kw::volt_to_milivolt(right_output);
    kw::move_raw(left_output, right_output); // send mv value
    pros::delay(10);
  }
  if(exit == true) {
    prev_left_output = 0;
    prev_right_output = 0;
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD); // Stop at end if required
  }
  correct_angle = kw::get_imu_rotation(); // Update global heading
  is_turning = false;                   // Reset turning state
}