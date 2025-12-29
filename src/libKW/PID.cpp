#include "main.h"
#include "libKW/api.hpp"

// Constructor
kw::PID::PID(double new_kp, double new_ki, double new_kd)
  : arrived(false), 
    arrive(true), 
    small_error_tolerance(1), 
    big_error_tolerance(3), 
    small_error_duration(100), 
    big_error_duration(500), 
    small_check_time(0), 
    big_check_time(0), 
    first_time(true), 
    integral_range(0), 
    integral_max(500) {
  // Set up the Coefficient.
  kp = new_kp;
  ki = new_ki;
  kd = new_kd;
  // Not arrived initially.
  arrived = false;
}

void kw::PID::setCoefficient(double new_kp, double new_ki, double new_kd) {
  kp = new_kp;
  ki = new_ki;
  kd = new_kd;
}

void kw::PID::setTarget(double new_target) { 
  target = new_target;
}

void kw::PID::setSmallBigErrorTolerance(double new_small_error_tolerance, double new_big_error_tolerance) { 
  small_error_tolerance = new_small_error_tolerance;
  big_error_tolerance = new_big_error_tolerance;
}

void kw::PID::setIntegralMax(double new_integral_max) { 
  integral_max = new_integral_max;
}

void kw::PID::setIntegralRange(double new_integral_range) { 
  integral_range = new_integral_range;
}

void kw::PID::clearSumError() { 
  sum_error = 0;
}

void kw::PID::setDerivativeTolerance(double new_derivative_tolerance) { 
  derivative_tolerance = new_derivative_tolerance;
}

void kw::PID::setSmallBigErrorDuration(double new_small_error_duration, double new_big_error_duration) { 
  small_error_duration = new_small_error_duration;
  big_error_duration = new_big_error_duration;
}

void kw::PID::setArrive(bool new_arrive) {
  arrive = new_arrive;
}

bool kw::PID::targetArrived() { 
  return arrived;
}

double kw::PID::getI() { 
  return ki;
}

double kw::PID::getOutput() { 
  return output;
}

int kw::PID::sign(double number) {
  if (number > 0) {
    return 1;
  } else if (number < 0) {
    return -1;
  }
  return 0;
}

double kw::PID::update(double input) {
  // Calculate current error
  current_error = target - input; 
  if (first_time) {
    // First time is tricky.
    first_time = false;

    // Need to skip derivative. 
    previous_error = current_error;
    sum_error = 0;
    small_check_time = pros::millis();
    big_check_time = pros::millis();
  }

  // Calculate proportional
  proportional = kp * current_error;
  
  // Calculate derivative
  derivative = kd * (current_error - previous_error); 
  
  // Record current error
  previous_error = current_error; 
  
  if (fabs(current_error) >= integral_range && integral_range != 0) { 
    // integral = 0 if proportinal > proportional_range
    sum_error = 0;
  } else { 
    sum_error += current_error;
    if (fabs(sum_error) * ki > integral_max && integral_max != 0) {
      // Limit integral to integral_max
      sum_error = sign(sum_error) * integral_max / ki;
    }
  }

  if (sign(sum_error) != sign(current_error) || 
      (fabs(current_error) <= small_error_tolerance)) {
    // Clear integral if overshoot or current_error is very small. 
    // This is to stablize the movement.
    sum_error = 0;
  }



  // Calculate integral
  integral = ki * sum_error;
  
  if (arrive == true && fabs(current_error) <= small_error_tolerance && 
      fabs(derivative) <= derivative_tolerance) { 
    // Exit when staying in tolerated region and 
    // maintaining a low enough speed for enough time
    if (pros::millis() - small_check_time >= small_error_duration) {
      arrived = true;
    }
  } else {
    small_check_time = pros::millis();
  }

  if (arrive == true && fabs(current_error) <= big_error_tolerance && 
      fabs(derivative) <= derivative_tolerance) { 
    // Exit when staying in tolerated region and 
    // maintaining a low enough speed for enough time
    if (pros::millis() - big_check_time >= big_error_duration) {
      arrived = true;
    }
  } else {
    big_check_time = pros::millis();
  }

  output = proportional + integral + derivative;

  return output;
}