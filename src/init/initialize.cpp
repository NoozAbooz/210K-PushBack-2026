#include "deviceGlobals.hpp"
#include "main.h"

std::string field_status;
bool update_odom = false;

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
    update_odom = true; // toggle kw::odom alg
    pros::Task([] {
        // chassis.calibrate();
        kw::initializeOdom();
    });

    optical.set_integration_time(10);
    pros::delay(20);
    optical.set_led_pwm(100);
    //odomLiftPiston.set_value(false);

    pros::Task([] {

    });

    if (update_odom == false) {
        rd_view_alert(sensorview, "[BIG FAT WARNING] update_odom is DISABLED!! You better know what you're doing!");
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
    controller.print(0, 0, "%s|%s|%.0lf   ", alliance.c_str(), auton_name, chassis.getPose().theta);
}

void competition_initialize() {
    rd_view_focus(allianceview);
    field_status = "competition";
    
    //odomLiftPiston.set_value(false); // we dont need odom pods for driver

    gui_selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
        competitionTelemtryRefresh();
    });
}
