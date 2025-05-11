#pragma once
#include "main.h"
#include <deque>
#include <vector>
#include <numeric>  // for std::accumulate
#include <algorithm>
#include <deque>
#include <cmath>

namespace ks
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

	// prolly dont use this 💀
	inline double tripleIMUHeading(double heading1, double heading2, double heading3, double threshold) { 
		// Run through median filter
	    int windowSize = 20;
		std::deque<double> buffer1;
		std::deque<double> buffer2;
		std::deque<double> buffer3;
		heading1 = ks::median_filter(buffer1, heading1, windowSize);
		heading2 = ks::median_filter(buffer2, heading2, windowSize);
		heading3 = ks::median_filter(buffer3, heading3, windowSize);
	    // Calculate the absolute differences between the headings
	    double diff12 = std::abs(heading1 - heading2);
	    double diff23 = std::abs(heading2 - heading3);
	    double diff13 = std::abs(heading1 - heading3);
	    // Check if one of the sensors is drifting
	    if (diff12 > threshold && diff13 > threshold) {
	        // Sensor 1 is drifting, return mean of sensor 2 and 3
	        return (heading2 + heading3) / 2.0;
	    } else if (diff12 > threshold && diff23 > threshold) {
	        // Sensor 2 is drifting, return mean of sensor 1 and 3
	        return (heading1 + heading3) / 2.0;
	    } else if (diff23 > threshold && diff13 > threshold) {
	        // Sensor 3 is drifting, return mean of sensor 1 and 2
	        return (heading1 + heading2) / 2.0;
	    } else {
	        // No sensor is drifting, return mean of all sensors 
			// (or all of them are drifing and we just gotta pray 💀)
	        return (heading1 + heading2 + heading3) / 3.0;
	    }
	}

	inline bool isDriverControl() {
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

	inline double clamp(double input, double min, double max){
	  if( input > max ){ return(max); }
	  if(input < min){ return(min); }
	  return(input);
	}

	inline bool isReversed(double input){
	  if(input<0) return(true);
	  return(false);
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