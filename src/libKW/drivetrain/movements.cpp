#include "main.h"
#include "libKW/api.hpp"
using namespace kw;

// ============================================================================
// INTERNAL STATE (DO NOT CHANGE)
// ============================================================================
bool kw::is_turning = false;
double kw::prev_left_output = 0, kw::prev_right_output = 0;
double kw::current_movement_error = 0; // distance to target, stored as non-abs value

void kw::waitUntilDistance(double dist_to_target_in, double time_limit_msec) {
    double start_time = pros::millis();
    while (std::fabs(current_movement_error) > std::fabs(dist_to_target_in) && (pros::millis() - start_time) <= time_limit_msec) {
        pros::delay(10);
    }
}