#include "main.h"

int telemState = 0; // for switching tele output on controller screen
int timer = 0;
std::string rumble_pattern = "";

void initTelemetry() {
	pros::Task([] {
		while (true) {
			// Report temperature telemetry 😭
			double drivetrainTemps = kw::vector_average(leftDrive.get_temperature_all());
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
				telemState = (telemState + 1) % 2; // Toggle telemetry display
			}

			// if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			// 	gui_selector.next_auton();
			// }
			// if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			// 	gui_selector.prev_auton();
			// }

			if(telemState == 0) {
				controller.print(0, 0, "DT%.0lf|INT%.0lf|T%.0lf  ", drivetrainTemps, intakeBottom.get_temperature(), kw::theta);
			} else if (telemState == 1) {
				controller.print(0, 0, "X:%.0lf Y:%.0lf T:%.0lf   ", kw::x_pos, kw::y_pos, kw::theta);
			} else if (telemState == 2) {
				auto auton = gui_selector.get_auton();
				const char* auton_name = auton->name.c_str();
				controller.print(0, 0, "%s|%s", alliance.c_str(), auton_name);
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