#include "main.h"

// Intake (hold down button to spin motor)
void refreshIntake() {
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intakeTop.move_voltage(12000);
			intakeBottom.move_voltage(12000);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intakeTop.move_voltage(-12000);
			intakeBottom.move_voltage(-12000);
		} else {
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
		}
}

bool liftStatus = false;
void refreshLift() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		liftStatus = !liftStatus;
		liftPiston.set_value(liftStatus);
	}
}

bool trapdoorStatus = false; // ratchet
void refreshTrapdoor() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
		trapdoorStatus = !trapdoorStatus;
		trapdoorPiston.set_value(trapdoorStatus);
	}
}

bool loaderStatus = false; // matchloader frame
void refreshLoader() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		loaderStatus = !loaderStatus;
		loaderPiston.set_value(loaderStatus);
	}
}

bool odomLiftStatus = true; // should be up by default in opcontrol
void refreshOdomLift() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		odomLiftStatus = !odomLiftStatus;
		odomLiftPiston.set_value(odomLiftStatus);
	}
}