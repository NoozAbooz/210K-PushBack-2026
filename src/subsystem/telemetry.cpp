#include "main.h"
#include "libKW/api.hpp"

int telemState = 0; // for switching tele output on controller screen
int timer = 0;
std::string rumble_pattern = "";

void initTelemetry() {
	pros::Task([] {
		while (true) {
			// Report temperature telemetry
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
				telemState++; // Toggle telemetry display
			}
			if (telemState > 2) {
				telemState = 0;
			}

			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
				gui_selector.next_auton();
			}
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
				gui_selector.prev_auton();
			}
			// if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			// 	alliance = (alliance == "red") ? "blue" : "red"; // toggle alliance
			// }

			if(telemState == 0) {
				double drivetrainAvgTemp = kw::vector_average(leftDrive.get_temperature_all());
				double intakeAvgTemp = kw::vector_average(intake.get_temperature_all());
				controller.print(0, 0, "DT%.0lf|INT%.0lf|T%.0lf  ", drivetrainAvgTemp, intakeAvgTemp, kw::theta);
			} else if (telemState == 1) {
				controller.print(0, 0, "X:%.0lf Y:%.0lf T:%.0lf   ", kw::x_pos, kw::y_pos, kw::theta);
			} else if (telemState == 2) {
				auto auton = gui_selector.get_auton();
				const char* auton_name = auton->name.c_str();
				controller.print(0, 0, "%s|%s      ", alliance.c_str(), auton_name);
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