#include "deviceGlobals.hpp"
#include "main.h"

// L1 Intake fast cycle (no hoard)
// L2 Outtake

// Left trigger (right arrow) - toggle to go hoard

// button a, toggle for emptying hoard
// R1 - Score on long goal (default you jsut run intake normally and lift the hood, if button A was triggered you empty hoard and score)
// R2- score on mid(default you jsut run intake normally for mid goal, if button A was triggered you empty hoard and score)

// right trigger (Y) - match load ✅

bool hoardStatus = false; // for toggling hoard mode
bool parkStatus = false; // for toggling park mode
void toggleHoard() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		hoardStatus = !hoardStatus;
		if (hoardStatus) {
			console.println("Hoard mode: ON");
		} else {
			console.println("Hoard mode: OFF");
		}
	}
}

void park() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
		parkStatus = !parkStatus;
		if (parkStatus) {
			intakeLiftPiston.set_value(true); // lift intake
		} else {
			intakeLiftPiston.set_value(false); // lower intake
		}
	}
}

void intakeMacro(std::string str) {
	if(str == "R1") { // score on long goal
		knockerPiston.set_value(true); // open knocker
		intakeBottom.move_voltage(12000);
		intakeTop.move_voltage(12000);
		intakeMiddleUpper.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
	} else if (str == "R2") { // score on mid goal
		intakeTop.move_voltage(-6000);
		intakeBottom.move_voltage(12000);
		intakeMiddleUpper.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
	} else if (str == "L1") { // intake up to long goal scoring
		knockerPiston.set_value(false); // shut knocker	
		intakeBottom.move_voltage(12000);
		intakeMiddleUpper.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
	} else if (str == "L2") { // outtake out of intake
		intakeBottom.move_voltage(-12000);
		intakeMiddleUpper.move_voltage(-12000);
		intakeMiddleLower.move_voltage(-12000);
	// hoard mode
	} else if(str == "HOARD_R1") { // score on long goal
		knockerPiston.set_value(true); // open knocker
		intakeTop.move_voltage(12000);
		intakeBottom.move_voltage(-2000);
		intakeMiddleUpper.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		rumble_pattern = ".";
	} else if (str == "HOARD_R2") { // score on mid goal
		intakeTop.move_voltage(-6000);
		intakeBottom.move_voltage(-2000);
		intakeMiddleUpper.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
		rumble_pattern = ".";
	} else if (str == "HOARD_L1") { // intake into hoard
		knockerPiston.set_value(false); // shut knocker		
		//intakeTop.move_voltage(12000);
		intakeBottom.move_voltage(12000);
		intakeMiddleUpper.move_voltage(-12000);
		intakeMiddleLower.move_voltage(12000);
		rumble_pattern = ".";
	} else if (str == "HOARD_L2") { // outtake out of intake from hoard
		intakeBottom.move_voltage(-12000);
		intakeMiddleUpper.move_voltage(12000);
		intakeMiddleLower.move_voltage(-12000);
		rumble_pattern = ".";
	} else if (str == "HOARD_LOAD_R1") { // preparing to score on long goal from hoard
		intakeBottom.move_voltage(-4000);
		intakeMiddleUpper.move_voltage(12000);
		intakeMiddleLower.move_voltage(12000);
	} else if (str == "HOARD_LOAD_R2") { // preparing to score on mid goal from hoard
		intakeBottom.move_voltage(-4000);
		intakeMiddleUpper.move_voltage(4000);
		intakeMiddleLower.move_voltage(12000);
	}
}

// Intake Hold (no hoard) to score
void refreshIntake() {
	if(hoardStatus == false && intakeLock == false) { // normal mode
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			intakeMacro("R1");
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intakeMacro("R2");
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intakeMacro("L1");
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intakeMacro("L2");
		} else {
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
			intakeMiddleUpper.move_voltage(0);
			intakeMiddleLower.move_voltage(0);
		}
	} else if (intakeLock == false) { // hoard mode
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			intakeMacro("HOARD_R1");
			rumble_pattern = ".";
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intakeMacro("HOARD_R2");
			rumble_pattern = ".";
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intakeMacro("HOARD_L1");
			rumble_pattern = ".";
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intakeMacro("HOARD_L2");
			rumble_pattern = ".";
		} else {
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
			intakeMiddleLower.move_voltage(0);
			intakeMiddleUpper.move_voltage(0);
		}
	}
}

bool loaderStatus = false; // matchloader frame/tongue mech
void refreshLoader() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		loaderStatus = !loaderStatus;
		loaderPiston.set_value(loaderStatus);
	}
}