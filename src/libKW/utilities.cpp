#include "main.h"

#include <deque>
#include <vector>
#include <numeric>  // for std::accumulate
#include <algorithm>
#include <deque>
#include <cmath>

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
double kw::normalizeTarget(double angle) {
  // Adjust angle to be within +/-180 degrees of the inertial sensor's rotation
  if (angle - inertial1.get_rotation() > 180) {
    while (angle - inertial1.get_rotation() > 180) angle -= 360;
  } else if (angle - inertial1.get_rotation() < -180) {
    while (angle - inertial1.get_rotation() < -180) angle += 360;
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
void kw::scaleToMin(double& left_output, double& right_output, double min_output) {
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
void kw::scaleToMax(double& left_output, double& right_output, double max_output) {
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
