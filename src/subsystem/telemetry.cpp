#include "main.h"

bool telemToggle = true; // for switching tele output on controller screen
std::string rumble_pattern = "";

void initTelemetry() {
	pros::Task([] {
		while (true) {
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

			pros::delay(50);

			if (!rumble_pattern.empty()) {
				controller.rumble(rumble_pattern.c_str());
				rumble_pattern.clear();
				pros::delay(50);
			}
		}
	});
}