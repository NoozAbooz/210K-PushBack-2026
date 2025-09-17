#pragma once
#include "main.h"
#include <deque>
#include <vector>
#include <numeric>  // for std::accumulate
#include <algorithm>
#include <deque>
#include <cmath>

namespace kw
{
	inline double vector_average(const std::vector<double>& v) {
	    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
	}

	inline double median_filter(std::deque<double>& buffer, double newVal, int windowSize) {
		buffer.push_back(newVal);
		if (buffer.size() > windowSize) {
		    buffer.pop_front();
		}  	
		std::vector<double> data(buffer.begin(), buffer.end());
		std::sort(data.begin(), data.end());   	
		return data[windowSize / 2];
	}

	inline bool is_driver_control() {
		return pros::competition::is_connected() && !pros::competition::is_autonomous() && !pros::competition::is_disabled();
	}

	inline double reduce_0_to_360(double angle) {
	  while(!(angle >= 0 && angle < 360)) {
	    if( angle < 0 ) { angle += 360; }
	    if(angle >= 360) { angle -= 360; }
	  }
	  return(angle);
	}

	inline double reduce_negative_180_to_180(double angle) {
	  while(!(angle >= -180 && angle < 180)) {
	    if( angle < -180 ) { angle += 360; }
	    if(angle >= 180) { angle -= 360; }
	  }
	  return(angle);
	}

	inline double reduce_negative_90_to_90(double angle) {
	  while(!(angle >= -90 && angle < 90)) {
	    if( angle < -90 ) { angle += 180; }
	    if(angle >= 90) { angle -= 180; }
	  }
	  return(angle);
	}

	inline double to_rad(double angle_deg){
	  return(angle_deg/(180.0/M_PI));
	}

	inline double to_deg(double angle_rad){
	  return(angle_rad*(180.0/M_PI));
	}

	inline double mm_to_in(double mm) {
	  return(mm / 25.4);
	}

	inline double get_radius(double x, double y, double x1, double y1, double angle) {
	  double delta_x = x1 - x;
	  double delta_y = y1 - y;
	  if((2 * delta_y * sin(to_rad(90 - angle))) == 0) {
	    return 999;
	  }
	  return (delta_x * delta_x + delta_y * delta_y) / (2 * delta_y * sin(to_rad(90 - angle)));
	}

	inline double clamp(double input, double min, double max){
	  if( input > max ){ return(max); }
	  if(input < min){ return(min); }
	  return(input);
	}

  	inline float to_milivolt(float input){
      return(input * (12000.0/127.0));
  	}

	inline double largest_abs(double a, double b) {
		if (std::abs(a) > std::abs(b)) {
			return a;
		} else if (std::abs(b) > std::abs(a)) {
			return b;
		}
		return 0.0; // or return a or b, depending on your needs
	}
}