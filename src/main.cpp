#include "main.h"
#include "abstractGlobals.hpp"
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
	field_status = "opcontrol";
	pros::Task([] { // run only in competition
		if (pros::competition::is_connected() && pros::competition::is_field_control()) {
			Gif* gif = new Gif("/usd/evernight.gif", rd_view_obj(gifview));
			rd_view_focus(gifview);
			console.println("Launching gif...");
		}
	});

	leftDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
	rightDrive.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
	toggleColourSort = false;

	while (true) { // Main continuous loop
		/* Drive */
		kw::drive_arcade(0, 0, 0.85);

		/* Subsystem Listeners */
		refreshIntake();
		refreshLoader();
		refreshBlocker();
		refreshWing();

		pros::delay(10); // Delay to save resources on brain
	}
}