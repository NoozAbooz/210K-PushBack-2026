#include "main.h"
using namespace kw;

// ============================================================================
// INTERNAL STATE (DO NOT CHANGE)
// ============================================================================
bool is_turning = false;
double prev_left_output = 0, prev_right_output = 0;
double current_movement_error = 0; // distance to target, stored as non-abs value

void kw::waitUntilDistance(double dist_to_target_in, double time_limit_msec) {
    double start_time = pros::millis();
    while (std::fabs(current_movement_error) > std::fabs(dist_to_target_in) && (pros::millis() - start_time) <= time_limit_msec) {
        pros::delay(10);
    }
}

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
void kw::turnToAngle(double turn_angle, double time_limit_msec, double max_output, double min_speed, bool exit) {
  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  // Prepare for turn
  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST);
  is_turning = true;
  double threshold = 1;
  kw::PID pid = kw::PID(kw::turn_kp, kw::turn_ki, kw::turn_kd);

  // Normalize and set PID target
  turn_angle = kw::normalize_target(turn_angle);
  pid.setTarget(turn_angle);
  pid.setIntegralMax(0);  
  pid.setIntegralRange(3);
  pid.setSmallBigErrorTolerance(threshold, threshold * 3);
  pid.setSmallBigErrorDuration(50, 150);
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

      if(output < min_speed) output = min_speed;
      else if (output > -min_speed) output = -min_speed;
      
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
void kw::driveTo(double distance_in, double time_limit_msec, double max_output, bool exit) {
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
    current_distance = fabs(get_vertical_distance_traveled() - start_vertical_pos);
    current_movement_error = distance_in - (get_vertical_distance_traveled() - start_vertical_pos); // used for kw::waitUntilDistance
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
void kw::moveToPoint(double x, double y, double time_limit_msec, bool forwards, double max_output, bool exit, bool overturn) {
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

void kw::swing(double swing_angle, double time_limit_msec, bool forwards, double max_output, bool exit) {
  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST); // Stop chassis before moving
  is_turning = true;                  // Set turning state
  double threshold = 1;
  PID pid = PID(turn_kp, turn_ki, turn_kd); // Initialize PID for turning

  swing_angle = normalize_target(swing_angle); // Normalize target angle
  pid.setTarget(swing_angle);                 // Set PID target
  pid.setIntegralMax(0);  
  pid.setIntegralRange(5);

  pid.setSmallBigErrorTolerance(threshold, threshold * 3);
  pid.setSmallBigErrorDuration(50, 250);
  pid.setDerivativeTolerance(threshold * 4.5);

  // Start the PID loop
  double start_time = pros::millis();
  double output;
  double current_heading = correct_angle;
  double previous_heading = 0;
  int choice = 1;

  // Determine which side to swing and direction
  if(swing_angle - correct_angle < 0 && forwards == true) {
    choice = 1;
  } else if(swing_angle - correct_angle > 0 && forwards == true) {
    choice = 2;
  } else if(swing_angle - correct_angle < 0 && forwards == false) {
    choice = 3;
  } else {
    choice = 4;
  }

  // Swing logic for each case, chaining (exit == false)
  if(choice == 1 && exit == false) {
    // Swing left, forward
    while (current_heading > swing_angle && pros::millis() - start_time <= time_limit_msec) {
      current_heading = kw::get_imu_rotation();
      output = pid.update(current_heading);

      previous_heading = current_heading;

      // Clamp output
      if(output < min_output) output = min_output;
      if(output > max_output) output = max_output;
      else if(output < -max_output) output = -max_output;

      leftDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD); // Hold left, swing right
      leftDrive.brake();

	    output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
      kw::move_raw(0, output); // send mv value
      pros::delay(10);
    }
  } else if(choice == 2 && exit == false) {
    // Swing right, forward
    while (current_heading < swing_angle && pros::millis() - start_time <= time_limit_msec) {
      current_heading = kw::get_imu_rotation();
      output = pid.update(current_heading);

      previous_heading = current_heading;

      // Clamp output
      if(output < min_output) output = min_output;
      if(output > max_output) output = max_output;
      else if(output < -max_output) output = -max_output;

      rightDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD); // Hold right, swing left
      rightDrive.brake();

	    output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
      kw::move_raw(output, 0); // send mv value
      pros::delay(10);
    }
  } else if(choice == 3 && exit == false) {
    // Swing left, backward
    while (current_heading > swing_angle && pros::millis() - start_time <= time_limit_msec) {
      current_heading = kw::get_imu_rotation();
      output = pid.update(current_heading);

      previous_heading = current_heading;

      // Clamp output
      if(output < min_output) output = min_output;
      if(output > max_output) output = max_output;
      else if(output < -max_output) output = -max_output;

      rightDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD); // Hold right, swing left
      rightDrive.brake();

	    output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
      kw::move_raw(output, 0); // send mv value
      pros::delay(10);
    }
  } else {
    // Swing right, backward
    while (current_heading < swing_angle && pros::millis() - start_time <= time_limit_msec && exit == false) {
      current_heading = kw::get_imu_rotation();
      output = pid.update(current_heading);

      previous_heading = current_heading;

      // Clamp output
      if(output < min_output) output = min_output;
      if(output > max_output) output = max_output;
      else if(output < -max_output) output = -max_output;

      leftDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD); // Hold left, swing right
      leftDrive.brake();

	    output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
      kw::move_raw(0, output); // send mv value
      pros::delay(10);
    }
  }

  // PID loop for exit == true (stop at end)
  while (!pid.targetArrived() && pros::millis() - start_time <= time_limit_msec && exit == true) {
    current_heading = kw::get_imu_rotation();
    output = pid.update(current_heading);

    previous_heading = current_heading;

    // Clamp output
    if(output > max_output) output = max_output;
    else if(output < -max_output) output = -max_output;

    // Apply output to correct side based on swing direction
    output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts
    switch(choice) {
    case 1:
      leftDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
      leftDrive.brake();
      kw::move_raw(0, -output * (forwards ? 1 : -1));
      break;
    case 2:
      rightDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
      rightDrive.brake();
      kw::move_raw(output * (forwards ? 1 : -1), 0);
      break;
    case 3:
      rightDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
      rightDrive.brake();
      kw::move_raw(-output * (forwards ? 1 : -1), 0);
      break;
    case 4:
      leftDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
      leftDrive.brake();
      kw::move_raw(0, output * (forwards ? 1 : -1));
      break;
    }
    pros::delay(10);
  }
  if(exit == true) {
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD); // Stop chassis at end if required
  }
  correct_angle = swing_angle; // Update global heading
  is_turning = false;          // Reset turning state
}

void kw::boomerang(double x, double y, double a, double dlead, double time_limit_msec, bool forwards, double max_output, bool exit, bool overturn) {
  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST); // Stop chassis before moving
  is_turning = true;                  // Set turning state
  double threshold = 0.5;
  int add = forwards ? 0 : 180;
  double max_slew_fwd = forwards ? max_slew_accel_fwd : max_slew_decel_rev;
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

  pid_distance.setTarget(0); // Target is dynamically updated
  pid_distance.setIntegralMax(3);  
  pid_distance.setSmallBigErrorTolerance(threshold, threshold * 3);
  pid_distance.setSmallBigErrorDuration(50, 250);
  pid_distance.setDerivativeTolerance(5);

  pid_heading.setTarget(normalize_target(kw::to_deg(atan2(x - x_pos, y - y_pos))));
  pid_heading.setIntegralMax(0);  
  pid_heading.setIntegralRange(1);
  pid_heading.setSmallBigErrorTolerance(0, 0);
  pid_heading.setSmallBigErrorDuration(0, 0);
  pid_heading.setDerivativeTolerance(0);
  pid_heading.setArrive(false);

  double start_time = pros::millis();
  double left_output = 0, right_output = 0, correction_output = 0, slip_speed = 0, overturn_value = 0;
  double exit_tolerance = 3;
  bool perpendicular_line = false, prev_perpendicular_line = true;
  double current_angle = 0, hypotenuse = 0, carrot_x = 0, carrot_y = 0;

  // Main PID loop for boomerang path
  while ((!pid_distance.targetArrived()) && pros::millis() - start_time <= time_limit_msec) {
    hypotenuse = hypot(x_pos - x, y_pos - y); // Distance to target
    // Calculate carrot point for path leading
    carrot_x = x - hypotenuse * sin(kw::to_rad(a + add)) * dlead;
    carrot_y = y - hypotenuse * cos(kw::to_rad(a + add)) * dlead;
    pid_distance.setTarget(hypot(carrot_x - x_pos, carrot_y - y_pos) * (forwards ? 1 : -1));
    current_angle = kw::get_imu_rotation();
    // Calculate drive output based on carrot point
    left_output = pid_distance.update(0) * cos(kw::to_rad(atan2(carrot_x - x_pos, carrot_y - y_pos) * 180 / M_PI + add - current_angle));
    right_output = left_output;
    // Check if robot has crossed the perpendicular line to the target
    perpendicular_line = ((y_pos - y) * -cos(kw::to_rad(normalize_target(a))) <= (x_pos - x) * sin(kw::to_rad(normalize_target(a))) + exit_tolerance);
    if(perpendicular_line && !prev_perpendicular_line) {
      break;
    }
    prev_perpendicular_line = perpendicular_line;

    // Minimum Output Check
    if(min_speed) {
      scale_to_min(left_output, right_output, min_output);
    }

    // Heading correction logic based on distance to carrot/target
    if(hypot(carrot_x - x_pos, carrot_y - y_pos) > 8) {
      pid_heading.setTarget(normalize_target(kw::to_deg(atan2(carrot_x - x_pos, carrot_y - y_pos)) + add));
      correction_output = pid_heading.update(current_angle);
    } else if(hypot(x - x_pos, y - y_pos) > 6) {
      pid_heading.setTarget(normalize_target(kw::to_deg(atan2(x - x_pos, y - y_pos)) + add));
      correction_output = pid_heading.update(current_angle);
    } else {
      pid_heading.setTarget(normalize_target(a));
      correction_output = pid_heading.update(current_angle);
      if(exit && hypot(x - x_pos, y - y_pos) < 5) {
        break;
      }
    }

    // Limit slip speed for smoother curves
    slip_speed = sqrt(chase_power * kw::get_radius(x_pos, y_pos, carrot_x, carrot_y, current_angle) * 9.8);
    if(left_output > slip_speed) {
      left_output = slip_speed;
    } else if(left_output < -slip_speed) {
      left_output = -slip_speed;
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
  correct_angle = a;      // Update global heading
  is_turning = false;     // Reset turning state
}