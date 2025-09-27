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
	extern double volt_to_milivolt(double input);
	extern double decivolt_to_milivolt(double input);
	extern double largest_abs(double a, double b);

	extern double normalize_target(double angle);
	extern void scale_to_min(double& left_output, double& right_output, double min_output);
	extern void scale_to_max(double& left_output, double& right_output, double max_output);
}