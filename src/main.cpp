#include "main.h"
#include "abstractGlobals.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled.
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will not resume 
 * the task from where it left off.
 */
void opcontrol() {
	field_status = "opcontrol";
	toggleColourSort = false;
	initTelemetry();

	while (true) { // Main continuous loop
		/* Drive */
		kw::drive_arcade(0, 0, 0.8);

		/* Subsystem Listeners */
		refreshIntake();
		refreshLoader();
		//toggleHoard();
		park();

		pros::delay(10); // Delay to save resources on brain
	}
}