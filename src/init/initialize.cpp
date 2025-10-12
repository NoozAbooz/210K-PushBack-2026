#include "deviceGlobals.hpp"
#include "main.h"

std::string field_status;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    rdconfig_init();
    pros::delay(10);

    /* Configurations */
    kw::update_odom = true; // toggle kw::odom alg
    pros::Task([] {
        // chassis.calibrate();
        kw::initialize_odom();
    });

    optical.set_integration_time(10);
    pros::delay(20);
    optical.set_led_pwm(100);
    //odomLiftPiston.set_value(false);

    pros::Task([] {

    });

    std::vector<int> left_motors = {11, 12, 14};
    std::vector<int> right_motors = {13, 15, 16};
    //maelstrom::logging::init(true, false, left_motors, right_motors, 5);
    //pros::Task error_logger(maelstrom::logging::robot_faults_log);

    if (kw::update_odom == false) {
        rd_view_alert(sensorview, "[BIG FAT WARNING] update_odom is DISABLED!! You better know what you're doing!");
        rumble_pattern = "---";
    }
    console.println("Robot initialized");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    field_status = "disabled";
   // odomLiftPiston.set_value(false);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competitionTelemtryRefresh() {
    auto auton = gui_selector.get_auton();
    const char* auton_name = auton->name.c_str();
    controller.print(0, 0, "%s|%s|%.0lf   ", alliance.c_str(), auton_name, kw::theta);
}

void competition_initialize() {
    rd_view_focus(allianceview);
    field_status = "competition";
    
    //odomLiftPiston.set_value(false); // we dont need odom pods for driver

    gui_selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
        competitionTelemtryRefresh();
    });
}
