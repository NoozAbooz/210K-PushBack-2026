#include "main.h"

// Button L1 -> intake normal (no hoard)
// button L2 -> Outtake
// button right (left paddle trigger) -> toggle between going into storage/and normal intake (SET DEFAULT TO NO HOARD)

// button R1 -> score on long goal (emptying hoard, scoring into top goal)
// button R2 -> score on mid goal (empting hoard, scoring into mid goal)
// Button Y (right paddle trigger) -> match loader

// Not confirmed build
// Button A -> hood blocker thingy

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
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) || controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
		trapdoorStatus = !trapdoorStatus;
		trapdoorPiston.set_value(trapdoorStatus);
	}
}

bool loaderStatus = false; // matchloader frame/tongue mech
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