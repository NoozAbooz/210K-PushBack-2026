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
  	return(angle_deg/(180.0/M_PI));
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

float kw::volt_to_milivolt(float input){
  	return(input * (12000.0/127.0));
}

double kw::largest_abs(double a, double b) { // return the value with largest magnitude
	if (std::abs(a) > std::abs(b)) {
		return a;
	} else if (std::abs(b) > std::abs(a)) {
		return b;
	}
	return 0.0; // or return a or b, depending on your needs
}
