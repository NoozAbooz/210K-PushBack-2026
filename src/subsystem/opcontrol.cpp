#include "main.h"
#include "libKW/api.hpp"
using namespace kw;

kw::lookup_table intake_lut({
    {-600, -12000}, {-565, -11000}, {-520, -10000}, {-460, -9000}, {-400, -8000}, {-345, -7000}, 
    {-288, -6000}, {-230, -5000}, {-175, -4000}, {-115, -3000}, {-50, -2000}, {0, -1000}, {0, 0},
    {0, 1000}, {50, 2000}, {115, 3000}, {175, 4000}, {230, 5000}, {290, 6000}, {350, 7000},
    {400, 8000}, {460, 9000}, {520, 10000}, {560, 11000}, {600, 12000}
});

kw::PID vel_pid(20, 5, 0);
kw::velocity_controller intake_velocity(&intake, intake_lut, vel_pid, 12000);

std::string intakeMacroStatus = "";
void intakeMacro(std::string str) {
	intakeMacroStatus = str;
	if(str == "R1") { // score on long goal
		trapdoorPiston.set_value(true); // open trapdoor to score
		intake_velocity.set_target(12000);
	} else if (str == "R2") { // score on mid goal
		intakePullDownPiston.set_value(true); // pull down intake band
		intake_velocity.set_target(520);
		
	} else if (str == "L1") { // intake up to long goal scoring
		trapdoorPiston.set_value(false); // close trapdoor
		intakePullDownPiston.set_value(false); // pull down intake band
		intake_velocity.set_target(12000);
	} else if (str == "L2") { // outtake out of intake
		intake_velocity.set_target(-12000);
	}
}

void refreshSubsys1() { // intake
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
			//intake.move_voltage(0);
			intake_velocity.set_target(0);
			trapdoorPiston.set_value(false); // close trapdoor
		}
	}
}

bool loaderStatus = false; // matchloader frame/tongue mech
void refreshSubsys2() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		loaderStatus = !loaderStatus;
		loaderPiston.set_value(loaderStatus);
	}
}
bool blockerStatus = false; // blocker piston
void refreshSubsys3() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
		blockerStatus = !blockerStatus;
		blockerPiston.set_value(blockerStatus);
	}
}

bool wingStatus = false; // wing
void refreshSubsys4() {
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		wingStatus = !wingStatus;
		wingPiston.set_value(wingStatus);
	}
	// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
	// 	wingPiston.set_value(false);
	// } else {
	// 	wingPiston.set_value(true);
	// }
}