#include "deviceGlobals.hpp"
#include "main.h"

// L1 Intake fast cycle (no hoard)
// L2 Outtake

// Left trigger (right arrow) - toggle to go hoard

// button a, toggle for emptying hoard
// R1 - Score on long goal (default you jsut run intake normally and lift the hood, if button A was triggered you empty hoard and score)
// R2- score on mid(default you jsut run intake normally for mid goal, if button A was triggered you empty hoard and score)

// right trigger (Y) - match load ✅

// Intake Hold (no hoard) to score
void refreshIntake() {
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			trapdoorPiston.set_value(true); // open knocker
			intakeTop.move_voltage(12000);
			intakeBottom.move_voltage(12000);
			intakeMiddle.move_voltage(12000);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			trapdoorPiston.set_value(true); // open knocker
			intakeTop.move_voltage(-12000);
			intakeBottom.move_voltage(12000);
			intakeMiddle.move_voltage(12000);
		} else {
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
			intakeMiddle.move_voltage(0);
		}
}

// intake index
void indexintake() {
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			trapdoorPiston.set_value(false); // shut knocker		
			intakeTop.move_voltage(12000);
			intakeBottom.move_voltage(12000);
			intakeMiddle.move_voltage(12000);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intakeTop.move_voltage(-12000);
			intakeBottom.move_voltage(12000);
			intakeMiddle.move_voltage(12000);
		} else {
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
			intakeMiddle.move_voltage(0);
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
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { //|| controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
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