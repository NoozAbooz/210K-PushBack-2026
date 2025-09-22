#pragma once
#include "main.h"

namespace kw {
	extern double vector_average(const std::vector<double>& v);
	extern bool is_driver_control();
	extern double to_rad(double angle_deg);
	extern double to_deg(double angle_rad);
	extern double mm_to_in(double mm);
	extern double get_radius(double x, double y, double x1, double y1, double angle);
	extern double clamp(double input, double min, double max);
	extern float volt_to_milivolt(float input);
	extern double largest_abs(double a, double b);
}