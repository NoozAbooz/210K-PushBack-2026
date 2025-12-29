#include "main.h"
using namespace kw;

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