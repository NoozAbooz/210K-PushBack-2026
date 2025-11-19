#pragma once
#include "main.h"

namespace kw
{
	extern double x_pos; // global X
    extern double y_pos; // global Y
    extern double theta; // global theta [0, 360)

    extern double correct_angle;
    extern bool update_odom;

    extern double get_imu_rotation();
    extern double get_vertical_distance_traveled();
    extern double get_horizontal_distance_traveled();

    extern void reset_chassis();
    extern void initialize_odom();
    extern pros::Task odom_task;
    extern void set_odom_position(double x_new, double y_new, double theta_new = 360);
    extern void odom_update();

    inline pros::Mutex encoder_mutex = pros::Mutex();
    inline pros::Mutex odom_mutex = pros::Mutex();
}