#include "main.h"
#include "libKW/api.hpp"
using namespace kw;

void kw::boomerang(double x, double y, double a, double dlead, double time_limit_msec,
                   bool forwards, double max_output, bool exit, bool overturn) {

  max_output = max_output * (12.0 / 127.0);
  kw::stop_chassis(pros::E_MOTOR_BRAKE_COAST);
  is_turning = true;

  int add = forwards ? 0 : 180;
  double max_slew_fwd = forwards ? max_slew_accel_fwd : max_slew_decel_rev;
  double max_slew_rev = forwards ? max_slew_decel_fwd : max_slew_accel_rev;

  PID pid_distance(distance_kp, distance_ki, distance_kd);
  PID pid_heading(heading_correction_kp, heading_correction_ki, heading_correction_kd);

  pid_distance.setIntegralMax(3);
  pid_heading.setIntegralMax(0);
  pid_heading.setArrive(false);

  double start_time = pros::millis();
  double left_output = 0, right_output = 0, correction_output = 0;
  double slip_speed = 0, overturn_value = 0;
  double current_angle = 0;
  double carrot_x = 0, carrot_y = 0;
  double hypotenuse = 0;

  bool final_heading_phase = false;  

  while (pros::millis() - start_time <= time_limit_msec) {

    hypotenuse = hypot(x_pos - x, y_pos - y);
    current_angle = kw::get_imu_rotation();

    // ================================
    // ENTER FINAL HEADING PHASE
    // ================================
    if (hypotenuse < 6 && !final_heading_phase) {    
      final_heading_phase = true;
      // Kill distance PID influence
    pid_distance.setIntegralMax(0);
    pid_distance.setTarget(0);

// Neutralize heading PID memory
    pid_heading.setIntegralMax(0);
    pid_heading.setTarget(current_angle);
    }

    // ================================
    // FINAL HEADING SETTLE MODE
    // ================================
    if (final_heading_phase) {                        
      pid_heading.setTarget(normalize_target(a));

      correction_output = pid_heading.update(current_angle);

      // Limit angular snap
      correction_output = std::clamp(correction_output, -6.0, 6.0);

      left_output  =  correction_output;
      right_output = -correction_output;

      scale_to_max(left_output, right_output, max_output);

      // Slew
      if (left_output - prev_left_output > max_slew_fwd)
        left_output = prev_left_output + max_slew_fwd;
      if (right_output - prev_right_output > max_slew_fwd)
        right_output = prev_right_output + max_slew_fwd;

      prev_left_output = left_output;
      prev_right_output = right_output;

      kw::move_raw(
        kw::volt_to_milivolt(left_output),
        kw::volt_to_milivolt(right_output)
      );

      // Exit condition
      if (fabs(normalize_target(current_angle - a)) < 1.0 &&
          fabs(prev_left_output) + fabs(prev_right_output) < 4) {
        break;
      }

      pros::delay(10);
      continue;
    }

    // ================================
    // NORMAL BOOMERANG PATH TRACKING
    // ================================
    carrot_x = x - hypotenuse * sin(kw::to_rad(a + add)) * dlead;
    carrot_y = y - hypotenuse * cos(kw::to_rad(a + add)) * dlead;

    pid_distance.setTarget(hypot(carrot_x - x_pos, carrot_y - y_pos) * (forwards ? 1 : -1));

    left_output = pid_distance.update(0) *
                  cos(kw::to_rad(
                    kw::to_deg(atan2(carrot_x - x_pos, carrot_y - y_pos)) + add - current_angle
                  ));

    right_output = left_output;

    // ===== Heading blending (smooth transition) =====
    double blend = std::clamp((hypotenuse - 4.0) / 8.0, 0.0, 1.0);
    double path_heading = normalize_target(
      kw::to_deg(atan2(carrot_x - x_pos, carrot_y - y_pos)) + add
    );

    double blended_heading =
      blend * path_heading + (1 - blend) * normalize_target(a);

    pid_heading.setTarget(normalize_target(blended_heading));
    correction_output = pid_heading.update(current_angle);

    // ===== Slip limiting =====
    slip_speed = sqrt(chase_power *
                      kw::get_radius(x_pos, y_pos, carrot_x, carrot_y, current_angle) * 9.8);

    left_output = std::clamp(left_output, -slip_speed, slip_speed);

    // ===== Combine outputs =====
    left_output  += correction_output;
    right_output -= correction_output;

    // Overturn protection
    overturn_value = fabs(left_output) + fabs(correction_output) - max_output;
    if (overturn_value > 0 && overturn) {
      left_output += (left_output > 0 ? -overturn_value : overturn_value);
    }

    scale_to_max(left_output, right_output, max_output);

    // Slew rate limiting
    if (left_output - prev_left_output > max_slew_fwd)
      left_output = prev_left_output + max_slew_fwd;
    if (right_output - prev_right_output > max_slew_fwd)
      right_output = prev_right_output + max_slew_fwd;

    prev_left_output = left_output;
    prev_right_output = right_output;

    kw::move_raw(
      kw::volt_to_milivolt(left_output),
      kw::volt_to_milivolt(right_output)
    );

    pros::delay(10);
  }

  if (exit) {
    prev_left_output = 0;
    prev_right_output = 0;
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
  }

  correct_angle = a;
  is_turning = false;
}