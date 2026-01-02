#include "main.h"
#include "deviceGlobals.hpp"
#include "libKW/api.hpp"
#include "gif-pros/gifclass.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled.
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will not resume 
 * the task from where it left off.
 */
void opcontrol() {
	wingPiston.set_value(true);
	pros::Task([] { // run only in competition
		if (pros::competition::is_connected() && pros::competition::is_field_control()) {
			Gif* gif = new Gif("/usd/evernight.gif", rd_view_obj(gifview));
			rd_view_focus(gifview);
			console.println("Launching gif...");
		}
	});

	field_status = "opcontrol";
	toggleColourSort = false;
	initTelemetry();

	while (true) { // Main continuous loop
		/* Drive */
		kw::drive_arcade(0, 0, 0.7);

		/* Subsystem Listeners */
		refreshIntake();
		refreshLoader();
		refreshKnocker();
		refreshWing();

		pros::delay(10); // Delay to save resources on brain
	}
}