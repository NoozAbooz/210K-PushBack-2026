#include "main.h"
#include "libKW/api.hpp"

#include <deque>
#include <vector>
#include <numeric>  // for std::accumulate
#include <algorithm>
#include <deque>

double kw::getDistance(pros::Distance& sensor) {
    double weights = 0; // weighted average distance from keej https://github.com/8pxl/keejLib/blob/main/lib/src/keejLib/odom.cpp
    double weightedDist = 0;

    for (int i=0; i<3; i++) {
        double distReading = kw::mm_to_in(sensor.get_distance());
        double confidence = sensor.get_confidence();
        if (confidence <= 20) confidence = 2;
        weights += confidence;
        weightedDist += distReading * confidence;
        pros::delay(20);
        //console.printf("Dist: %.2f inches, Confid: %.2f\n", distReading, confidence);
    }
    return (double)(weightedDist / weights);
}

double kw::vector_average(const std::vector<double>& v) {
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

bool kw::is_driver_control() {
	return pros::competition::is_connected() && !pros::competition::is_autonomous() && !pros::competition::is_disabled();
}

double kw::to_rad(double angle_deg){
  	return(angle_deg*(M_PI/180.0));
}
double kw::to_deg(double angle_rad){
  	return(angle_rad*(180.0/M_PI));
}

double kw::mm_to_in(double mm) {
  	return(mm / 25.4);
}

double kw::get_radius(double x, double y, double x1, double y1, double angle) {
  	double delta_x = x1 - x;
  	double delta_y = y1 - y;
  	if((2 * delta_y * sin(to_rad(90 - angle))) == 0) {
		return 999;
  	}
  	return (delta_x * delta_x + delta_y * delta_y) / (2 * delta_y * sin(to_rad(90 - angle)));
}

double kw::clamp(double input, double min, double max){
  	if( input > max ){ return(max); }
  	if(input < min){ return(min); }
  	return(input);
}

double kw::volt_to_milivolt(double input){
  	return(input * 1000.0);
}

double kw::decivolt_to_milivolt(double input){
  	return(input * (12000.0 / 127.0));
}

double kw::largest_abs(double a, double b) { // return the value with largest magnitude
	if (std::abs(a) > std::abs(b)) {
		return a;
	} else if (std::abs(b) > std::abs(a)) {
		return b;
	}
	return 0.0; // or return a or b, depending on your needs
}

/*
 * Normalizes an angle to be within +/-180 degrees of the current heading.
 * - angle: The target angle to normalize.
 */
double kw::normalize_target(double angle) {
  // Adjust angle to be within +/-180 degrees of the inertial sensor's rotation
  if (angle - kw::get_imu_rotation() > 180) {
    while (angle - kw::get_imu_rotation() > 180) angle -= 360;
  } else if (angle - kw::get_imu_rotation() < -180) {
    while (angle - kw::get_imu_rotation() < -180) angle += 360;
  }
  return angle;
}

// ============================================================================
// OUTPUT SCALING HELPER FUNCTIONS
// ============================================================================

/*
 * Ensures output values are at least the specified minimum for both sides.
 * - left_output: Reference to left output voltage.
 * - right_output: Reference to right output voltage.
 * - min_output: Minimum allowed output voltage.
 */
void kw::scale_to_min(double& left_output, double& right_output, double min_output) {
  // Scale outputs to ensure minimum voltage is met for both sides
  if (fabs(left_output) <= fabs(right_output) && left_output < min_output && left_output > 0) {
    right_output = right_output / left_output * min_output;
    left_output = min_output;
  } else if (fabs(right_output) < fabs(left_output) && right_output < min_output && right_output > 0) {
    left_output = left_output / right_output * min_output;
    right_output = min_output;
  } else if (fabs(left_output) <= fabs(right_output) && left_output > -min_output && left_output < 0) {
    right_output = right_output / left_output * -min_output;
    left_output = -min_output;
  } else if (fabs(right_output) < fabs(left_output) && right_output > -min_output && right_output < 0) {
    left_output = left_output / right_output * -min_output;
    right_output = -min_output;
  }
}

/*
 * Ensures output values do not exceed the specified maximum for both sides.
 * - left_output: Reference to left output voltage.
 * - right_output: Reference to right output voltage.
 * - max_output: Maximum allowed output voltage.
 */
void kw::scale_to_max(double& left_output, double& right_output, double max_output) {
  // Scale outputs to ensure maximum voltage is not exceeded for both sides
  if (fabs(left_output) >= fabs(right_output) && left_output > max_output) {
    right_output = right_output / left_output * max_output;
    left_output = max_output;
  } else if (fabs(right_output) > fabs(left_output) && right_output > max_output) {
    left_output = left_output / right_output * max_output;
    right_output = max_output;
  } else if (fabs(left_output) > fabs(right_output) && left_output < -max_output) {
    right_output = right_output / left_output * -max_output;
    left_output = -max_output;
  } else if (fabs(right_output) > fabs(left_output) && right_output < -max_output) {
    left_output = left_output / right_output * -max_output;
    right_output = -max_output;
  }
}

// ============================================================================
// LOOKUP TABLE IMPLEMENTATION
// ============================================================================

/*
 * Constructor for LookupTable
 * - data: Initializer list of {velocity, voltage} pairs
 */
kw::lookup_table::lookup_table(std::initializer_list<std::pair<double, double>> data)
  : table(data) {}

/*
 * Get interpolated voltage value for a given velocity
 * - velocity: The velocity to look up
 * Returns: Interpolated voltage value
 */
double kw::lookup_table::get_value(double velocity) {
  // Handle edge cases
  if (table.empty()) return 0.0;
  if (table.size() == 1) return table[0].second;
  
  // If velocity is below the first point, return first voltage
  if (velocity <= table[0].first) {
    return table[0].second;
  }
  
  // If velocity is above the last point, return last voltage
  if (velocity >= table[table.size() - 1].first) {
    return table[table.size() - 1].second;
  }
  
  // Find the two points to interpolate between
  for (size_t i = 0; i < table.size() - 1; i++) {
    if (velocity >= table[i].first && velocity <= table[i + 1].first) {
      // Linear interpolation
      double v1 = table[i].first;
      double v2 = table[i + 1].first;
      double volt1 = table[i].second;
      double volt2 = table[i + 1].second;
      
      double ratio = (velocity - v1) / (v2 - v1);
      return volt1 + ratio * (volt2 - volt1);
    }
  }
  
  return 0.0;
}

// ============================================================================
// VELOCITY CONTROLLER IMPLEMENTATION
// ============================================================================

/*
 * Constructor for VelocityController
 * - motor: Pointer to the motor to control
 * - voltage_lut: Lookup table for feedforward control
 * - velocity_pid: PID controller for velocity error correction
 * - max_voltage: Maximum voltage to apply to the motor
 */
kw::velocity_controller::velocity_controller(pros::MotorGroup* motor_group, lookup_table voltage_lut, 
                                           kw::PID velocity_pid, double max_voltage) 
  : motor_group(motor_group), voltage_lut(voltage_lut), velocity_pid(velocity_pid), 
    target(0.0), max_voltage(max_voltage), last_commanded_velocity(0.0), running(true) {
  task = new pros::Task([this] {
    while (running) {
      this->update();
      pros::delay(10);
    }
  });
}

/*
 * Destructor for VelocityController
 */
kw::velocity_controller::~velocity_controller() {
  running = false;
  if (task != nullptr) {
    delete task;
  }
}

/*
 * Set the desired target velocity
 * - new_target: The target velocity to reach
 */
void kw::velocity_controller::set_target(double new_target) {
  target = new_target;
  velocity_pid.setTarget(new_target);
}

/*
 * Update the velocity controller with feedforward and PID
 * Returns: The current velocity after the update
 */
double kw::velocity_controller::update() {
  if (motor_group == nullptr) return 0.0;
  if (target == 0.0) {
    motor_group->move_voltage(0);
    last_commanded_velocity = 0.0;
    return 0.0;
  }
  if (fabs(target) == 12000) {
    int sign = (target > 0) ? 1 : -1;
    motor_group->move_voltage(sign * 12000);
    last_commanded_velocity = motor_group->get_actual_velocity();
    return motor_group->get_actual_velocity();
  }
  
  // Feedforward from lookup table
  float ff = voltage_lut.get_value(target);
    
  // PID control based on velocity error
  float pid_output = velocity_pid.update(kw::vector_average(motor_group -> get_actual_velocity_all()));
  
  // Combine feedforward and PID
  float total_voltage = ff + pid_output;
  total_voltage = clamp(total_voltage, -max_voltage, max_voltage);
  
  // Apply voltage to motor
  motor_group->move_voltage(static_cast<int>(total_voltage));
  last_commanded_velocity = target;

  //printf("Target: %.2f, CurrentVel: %.2f, FF: %.2f, PID: %.2f, Output: %.2f\n", target, kw::vector_average(motor_group -> get_actual_velocity_all()), ff, pid_output, total_voltage);
  
  return motor_group->get_actual_velocity();
}

/*
 * Get the target velocity
 */
double kw::velocity_controller::get_velocity() {
  if (motor_group == nullptr) return 0.0;
  return last_commanded_velocity;
}