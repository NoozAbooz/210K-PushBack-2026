#include "main.h"
#include "libKW/api.hpp"
using namespace kw;

/*
 * turnToPoint
 * Turns the robot to face a specific point in the field.
 * - x, y: Coordinates of the target point.
 * - direction: Direction to face the point (1 for forward, -1 for backward).
 * - time_limit_msec: Maximum time allowed for the turn (in milliseconds).
 */
void kw::turnToPoint(double x, double y, double time_limit_msec, bool forwards, double max_output, double min_speed, bool exit, bool async) {
  if(async) {
    pros::Task task([&]() { 
      kw::turnToPoint(x, y, time_limit_msec, forwards, max_output, min_speed, exit);
    });
    pros::delay(10);
    return;
  }

  // Prepare for turn
  max_output = max_output * (12.0 / 127.0); // convert from [-127, 127] decivolts to [-12, 12] volts
  min_speed = min_speed * (12.0 / 127.0); // convert from [0, 127] decivolts to [0, 12] volts

  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST);
  is_turning = true;                  // Set turning state
  double threshold = 1, add = 0;
  if(forwards == false) {
    add = 180; // Add 180 degrees if turning to face backward
  }
  // Calculate target angle using atan2 and normalize
  double turn_angle = kw::normalize_target(kw::to_deg(atan2(x - x_pos, y - y_pos))) + add;
  PID pid = PID(turn_kp, turn_ki, turn_kd);

  pid.setTarget(turn_angle); // Set PID target
  pid.setIntegralMax(0);  
  pid.setIntegralRange(3);

  pid.setSmallBigErrorTolerance(threshold, threshold * 3);
  pid.setSmallBigErrorDuration(50, 150);
  pid.setDerivativeTolerance(threshold * 4.5);

  // Start the PID loop
  double start_time = pros::millis();
  double output;
  double current_heading;
  double previous_heading = 0;
  int index = 1;
  while (!pid.targetArrived() && pros::millis() - start_time <= time_limit_msec) {
    pid.setCoefficient(kw::turn_kp, kw::turn_ki, kw::turn_kd);
    // Continuously update target as robot moves
    pid.setTarget(kw::normalize_target(kw::to_deg(atan2(x - x_pos, y - y_pos))) + add);
    current_heading = kw::get_imu_rotation();
    output = pid.update(current_heading);
    output = kw::volt_to_milivolt(output); // convert PID output from [-12, 12] decivolt to to [-12000, 12000] millivolts

    kw::move_raw(output, -output); // send mv value
    pros::delay(10);
  }
  if(exit == true) {
	  prev_left_output = 0;
	  prev_right_output = 0;
    stop_chassis(pros::E_MOTOR_BRAKE_HOLD); // Stop at end
  }
  correct_angle = kw::get_imu_rotation(); // Update global heading
  is_turning = false;                   // Reset turning state
}