#include "deviceGlobals.hpp"
#include "main.h"
#include "libKW/api.hpp"
using namespace kw;

// kw::lookup_table intake_lut({
//     {-600, -12000}, {-565, -11000}, {-520, -10000}, {-460, -9000}, {-400, -8000}, {-345, -7000}, 
//     {-288, -6000}, {-230, -5000}, {-175, -4000}, {-115, -3000}, {-50, -2000}, {0, -1000}, {0, 0},
//     {0, 1000}, {50, 2000}, {115, 3000}, {175, 4000}, {230, 5000}, {290, 6000}, {350, 7000},
//     {400, 8000}, {460, 9000}, {520, 10000}, {560, 11000}, {600, 12000}
// });

// kw::PID vel_pid(20, 5, 0);
// kw::velocity_controller intake_velocity(intake_lut, vel_pid, 11000);

std::string intakeMacroStatus = "";
bool midShift = 0; //0 is normal, 1 is fast -> THERE WILL BE A SLOW MODE FOR SKILLS
void intakeMacro(std::string str) {
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){ //midshift hold
		midShift = 0;
	} else {
		midShift = 1;
	}

	intakeMacroStatus = str;
	if(str == "R0") { // score on long goal
		//intake_velocity.set_target(12000);
		trapdoorPiston.set_value(true);
		intakeMain.move_voltage(12000);
		intakeSub.move_voltage(12000);
		intakeCounterRoller.move_voltage(12000);
	} else if (str == "R2" && midShift == 0) { // score on mid goal NORMAL
		//intake_velocity.set_target(12000);
		trapdoorPiston.set_value(false);
		intakeMain.move_voltage(7000);
		intakeSub.move_voltage(7000);
		intakeCounterRoller.move_voltage(-5100);
	} else if (str == "R2" && midShift == 1) { // score on mid goal FAST
		//intake_velocity.set_target(12000);
		trapdoorPiston.set_value(false);
		intakeMain.move_voltage(12000);
		intakeSub.move_voltage(12000);
		intakeCounterRoller.move_voltage(-12000);
	} else if (str == "L1") { // intake up to long goal scoring
		//intake_velocity.set_target(12000);
		trapdoorPiston.set_value(false);
		intakeMain.move_voltage(12000);
		intakeSub.move_voltage(12000);
		intakeCounterRoller.move_voltage(12000);
	} else if (str == "L2") { // outtake out of intake
		//intake_velocity.set_target(-12000);
		intakeMain.move_voltage(-12000);
		intakeSub.move_voltage(-12000);
		intakeCounterRoller.move_voltage(-12000);
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
			// intakePullDownPiston.set_value(false); // pull down intake band
			intakeMain.move_voltage(0);
			intakeCounterRoller.move_voltage(0);
			intakeSub.move_voltage(0);
			//intake_velocity.set_target(0);
			// trapdoorPiston.set_value(false); // close trapdoor
		}
	}
}

bool loaderStatus = false; // matchloader frame/tongue mech
void refreshSubsys2() { //TOGGLE
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) && midShift == 0) {
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