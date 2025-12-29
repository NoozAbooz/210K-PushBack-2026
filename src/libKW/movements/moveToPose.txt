#include "main.h"
using namespace kw;

void kw::moveToPose() {
    // Calculate angle error in compass frame (0 = +Y)
    float dx = target.x - kw::x_pos;
    float dy = target.y - kw::y_pos;
    compass_degrees angle_to_point = compass_degrees(miku::atan2(dy, dx));
    if (!forwards) angle_to_point = (angle_to_point + 180.0f).wrap();

    float current_deg = compass_degrees(Miku.get_heading()).wrap();

    float turn_error = (angle_to_point - current_deg).wrap();
    // Distance error
    float drive_error = current.distance_to(target);
    if (params.cutoff > 0 && drive_error < params.cutoff) {
        done = true;
        return;
    }

    standard_radians angle_error = (miku::atan2(dy, dx) - Miku.get_heading()).wrap();

    drive_patience_exit.update(drive_error);

    // PID outputs
    float drive_out = std::clamp(drive_pid.update(drive_error), -params.drive_max_volt_pct / 100.0f * 12000, params.drive_max_volt_pct / 100.0f * 12000);
    float turn_out = std::clamp(turn_pid.update(turn_error), -params.turn_max_volt_pct / 100.0f * 12000, params.turn_max_volt_pct / 100.0f * 12000);
    float drive_scale = std::cos(angle_error);
    if(sign(drive_scale) != sign(std::pow(drive_scale, params.cos_scale))) drive_out *= -1.0 * std::pow(drive_scale, params.cos_scale);
    else drive_out *= std::pow(drive_scale, params.cos_scale);

    if(fabs(drive_error) < 6.0) {
        int side = sign(dx * cos(Miku.get_heading()) + dy * sin(Miku.get_heading()));
        if(side != start_side) {
            done = true;
            Miku.stop();
            return;
        }
        turn_out *= pow((drive_error / 6.0), 4);
    }

    if(params.min_volt_pct > 0) {
        if(drive_out > 0 && drive_out < fabs(params.min_volt_pct / 100.0f * 12000)) drive_out = params.min_volt_pct / 100.0f * 12000;
        if(drive_out < 0 && drive_out > -fabs(params.min_volt_pct / 100.0f * 12000)) drive_out = -params.min_volt_pct / 100.0f * 12000;
    }

    float left_out = drive_out + turn_out;
    float right_out = drive_out - turn_out;

    // Final motor outputs
    Miku.move_voltage(left_out, right_out);

    if(drive_patience_exit.get_exit() || timer.is_done()) {
        done = true;
        Miku.stop();
        return;
    }
}