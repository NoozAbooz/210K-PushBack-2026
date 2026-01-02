#include "main.h"

std::string intakeMacroStatus = "";
void intakeMacro(std::string str) {
	intakeMacroStatus = str;
	if(str == "R1") { // score on long goal
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		intakeTop.move_voltage(12000);
	} else if (str == "R2") { // score on mid goal
		intakePullDownPiston.set_value(true); // pull down intake band
		intakeTop.move_voltage(-10000);
		intakeMiddleLower.move_voltage(12000);
		intakeBottom.move_voltage(12000);
	} else if (str == "L1") { // intake up to long goal scoring
		intakeBottom.move_voltage(12000);
		intakeMiddleLower.move_voltage(0);
		intakeTop.move_voltage(0);
	} else if (str == "L2") { // outtake out of intake
		intakeBottom.move_voltage(-12000);
		intakeMiddleLower.move_voltage(-12000);
		intakeTop.move_voltage(0);
	}
}

void refreshIntake() {
	if(intakeLock == false) { // normal mode
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			intakeMacro("R1");
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intakeMacro("R2");
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intakeMacro("L1");
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intakeMacro("L2");
		} else {
			intakePullDownPiston.set_value(false); // pull down intake band
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
			intakeMiddleUpper.move_voltage(0);
			intakeMiddleLower.move_voltage(0);
		}
	}
}

bool parkStatus = false; // for toggling park mode
void park() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
		parkStatus = !parkStatus;
		
	}
}

bool loaderStatus = false; // matchloader frame/tongue mech
void refreshLoader() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		loaderStatus = !loaderStatus;
		loaderPiston.set_value(loaderStatus);
	}
}
bool knockerStatus = false;
void refreshKnocker() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
		knockerStatus = !knockerStatus;
		
	}
}

bool wingStatus = false;
void refreshWing() {
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		// wingStatus = !wingStatus;
		if (!wingPiston.is_extended()) {
			wingPiston.retract();
		}
	} else {
		if (wingPiston.is_extended()) {
			wingPiston.extend();
		}
	}
}
