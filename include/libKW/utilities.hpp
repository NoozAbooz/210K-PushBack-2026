#pragma once
#include "main.h"
#include "libKW/PID.hpp"
#include <vector>
#include <initializer_list>

namespace kw {
	extern double getDistance(pros::Distance& sensor);
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

	// Lookup Table for voltage-velocity mapping
	class lookup_table {
		public:
			// Constructor with initializer list of {velocity, voltage} pairs
			lookup_table(std::initializer_list<std::pair<double, double>> data);

			// Get interpolated voltage value for a given velocity
			double get_value(double velocity);

		private:
			std::vector<std::pair<double, double>> table; // {velocity, voltage} pairs
	};

	// Velocity Controller for motor control with feedforward and PID
	class velocity_controller {
		public:
			// Constructor
			velocity_controller(lookup_table voltage_lut, kw::PID velocity_pid, double max_voltage);

			// Destructor
			~velocity_controller();

			// Set the desired target velocity
			void set_target(double new_target);

			// Update the current velocity towards the target
			// Returns the current velocity after the update
			double update();

			// Get the current velocity
			double get_velocity();

		private:
			lookup_table voltage_lut;      // Feedforward lookup table
			PID velocity_pid;             // PID controller
			double target;                // Target velocity
			double max_voltage;           // Maximum voltage
			double last_commanded_velocity; // Last commanded velocity
			bool running;                 // Task loop control
			pros::Task* task;             // Update task
	};
}