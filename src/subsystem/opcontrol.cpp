#include "deviceGlobals.hpp"
#include "main.h"

// L1 Intake fast cycle (no hoard)
// L2 Outtake

// Left trigger (right arrow) - toggle to go hoard

// button a, toggle for emptying hoard
// R1 - Score on long goal (default you jsut run intake normally and lift the hood, if button A was triggered you empty hoard and score)
// R2- score on mid(default you jsut run intake normally for mid goal, if button A was triggered you empty hoard and score)

// right trigger (Y) - match load ✅

bool telemToggle = true; // for switching tele output on controller screen
bool hoardStatus = false; // for toggling hoard mode
void toggleHoard() {
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

			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
				hoardStatus = !hoardStatus;
				if (hoardStatus) {
					console.println("Hoard mode: ON");
					controller.rumble(".");
					pros::delay(100);
				} else {
					console.println("Hoard mode: OFF");
					controller.rumble("..");
					pros::delay(100);
				}
			}
		}
	});

}

// Intake Hold (no hoard) to score
void refreshIntake() {
		if(hoardStatus == false)
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			knockerPiston.set_value(true); // open knocker
			intakeBottom.move_voltage(12000);
			intakeTop.move_voltage(12000);
			intakeMiddleUpper.move_voltage(12000);
			intakeMiddleLower.move_voltage(12000);
			} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intakeTop.move_voltage(-12000);
			intakeBottom.move_voltage(12000);
			intakeMiddleUpper.move_voltage(12000);
			intakeMiddleLower.move_voltage(12000);
			} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			knockerPiston.set_value(false); // shut knocker	
			intakeBottom.move_voltage(12000);
			intakeMiddleUpper.move_voltage(12000);
			intakeMiddleLower.move_voltage(12000);
			} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intakeBottom.move_voltage(-12000);
			intakeMiddleUpper.move_voltage(-12000);
			intakeMiddleLower.move_voltage(-12000);
			} else {
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
			intakeMiddleUpper.move_voltage(0);
			intakeMiddleLower.move_voltage(0);
		}
		else // hoard mode
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			knockerPiston.set_value(true); // open knocker
			intakeTop.move_voltage(12000);
			intakeBottom.move_voltage(-12000);
			intakeMiddleUpper.move_voltage(12000);
			intakeMiddleLower.move_voltage(12000);
			} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intakeTop.move_voltage(-12000);
			intakeBottom.move_voltage(-12000);
			intakeMiddleUpper.move_voltage(12000);
			intakeMiddleLower.move_voltage(12000);
			} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			knockerPiston.set_value(false); // shut knocker		
			//intakeTop.move_voltage(12000);
			intakeBottom.move_voltage(12000);
			intakeMiddleUpper.move_voltage(-12000);
			intakeMiddleLower.move_voltage(12000);
			} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intakeBottom.move_voltage(-12000);
			intakeMiddleUpper.move_voltage(12000);
			intakeMiddleLower.move_voltage(-12000);
			} else {
			intakeTop.move_voltage(0);
			intakeBottom.move_voltage(0);
			intakeMiddleLower.move_voltage(0);
			intakeMiddleUpper.move_voltage(0);
		}
	}

bool loaderStatus = false; // matchloader frame/tongue mech
void refreshLoader() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		loaderStatus = !loaderStatus;
		loaderPiston.set_value(loaderStatus);
	}
}