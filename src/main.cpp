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
	bool telemToggle = true; // for switching tele output on controller screen
	toggleHoard();

	while (true) { // Main continuous loop
		/* Drive */
		kw::drive_arcade(0, 0, 1);

		/* Subsystem Listeners */
		refreshIntake();
		refreshLoader();

		// Report temperature telemetry 😭
		double drivetrainTemps = kw::vector_average(leftDrive.get_temperature_all());

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			telemToggle = !telemToggle; // Toggle telemetry display
		}
		if(!telemToggle) {
			controller.print(0, 0, "DT%.0lf|INT%.0lf|T%.0lf  ", drivetrainTemps, intakeBottom.get_temperature(), kw::theta);
		} else {
			controller.print(0, 0, "X:%.0lf Y:%.0lf T:%.0lf   ", kw::x_pos, kw::y_pos, kw::theta);
		}

		pros::delay(10); // Delay to save resources on brain
	}
}