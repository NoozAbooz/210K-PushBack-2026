#include "main.h"

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
		if (field_status == "competition") {
			Gif* gif = new Gif("/usd/nokotan.gif", rd_view_obj(gifview));
			rd_view_focus(gifview);
			console.println("Launching gif...");
		}
	});
	bool telemToggle = false;

	while (true) { // Main continuous loop
		/* Drive */
		ks::arcadeDrive(0, 0, 1.2);

		/* Subsystem Listeners */
		refreshIntake();
		refreshLift();
		refreshTrapdoor();
		refreshLoader();

		// Report temperature telemetry 😭
		double drivetrainTemps = ks::vector_average(leftDrive.get_temperature_all());
		double theta = fmod(chassis.getPose().theta, 360); // wrap to [0, 360) for user view
    	if (theta < 0) {
       		theta += 360;
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			telemToggle = !telemToggle; // Toggle telemetry display
		}
		if(!telemToggle) {
			controller.print(0, 0, "DT%.0lf|INT%.0lf|T%.0lf  ", drivetrainTemps, intake.get_temperature(1), theta);
		} else {
			controller.print(0, 0, "X:%.0lf Y:%.0lf T:%.0lf   ", chassis.getPose().x, chassis.getPose().y, theta);
		}

		pros::delay(10); // Delay to save resources on brain
	}
}