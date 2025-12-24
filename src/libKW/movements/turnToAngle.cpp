#include "main.h"
using namespace kw;

/*
 * Turns the robot to a specified angle using PID control.
 * - turn_angle: Target angle to turn to (in degrees).
 * - time_limit_msec: Maximum time allowed for the turn (in milliseconds).
 * - exit: If true, stops the robot at the end; if false, allows chaining.
 * - max_output: Maximum output to motors. (0, 127]
 * - min_speed: Minimum speed to turn at (0, 127]
 * - async: If true, runs the turn in a separate task and returns immediately.
 */
void kw::turnToAngle(double turn_angle, double time_limit_msec, double max_output, double min_speed, bool exit, bool async) {
  if(async) {
    pros::Task task([&]() { 
      kw::turnToAngle(turn_angle, time_limit_msec, max_output, min_speed, exit);
    });
    pros::delay(10);
    return;
  }

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

      if(std::fabs(output) < min_speed) {
        output = (output > 0) ? min_speed : -min_speed;
      }
      
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