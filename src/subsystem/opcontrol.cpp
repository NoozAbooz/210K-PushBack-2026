#include "main.h"

// Intake (hold down button to spin motor)
void refreshIntake() {
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move_voltage(12000);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move_voltage(-12000);
		} else {
			intake.move_voltage(0);
		}
}
bool level = false;
void scorelevel() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
	level = !level;
		levelPiston.set_value(level);
	}
}

bool toptrap = false;
void toptrapdoor() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		toptrap = !toptrap;
		top_trapdoor.set_value(toptrap);
	}
}
