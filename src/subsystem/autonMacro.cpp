#include "main.h"

void stopIntake() {
	intakeTop.move_voltage(0);
	intakeBottom.move_voltage(0);
	intakeMiddleUpper.move_voltage(0);
	intakeMiddleLower.move_voltage(0);
}

// void scoreOwnColour(int timeout) { // intended to be called in auton
// 	int timer = 0;
// 	// red range: 8-25
// 	// blue range: 200-230
// 	intake.move_voltage(12000);
// 	trapdoorPiston.set_value(true); // disengage ratchet

// 	if (alliance == "red" || alliance == "na") {
// 		while (!(optical.get_hue() > 200 && optical.get_hue() < 230) && timer < timeout) {
// 			pros::delay(10);
// 			timer += 10;
// 		}
// 	} else if (alliance == "blue") {
// 		while (!(optical.get_hue() > 8 && optical.get_hue() < 30) && timer < timeout) {
// 			pros::delay(10);
// 			timer += 10;
// 		}
// 	}

// 	trapdoorPiston.set_value(false); // engage ratchet
// 	intake.brake();
// 	pros::delay(200);
// 	intake.move_voltage(0);
// }

// void scoreAmount(int amount, int timeout) { // intended to be called in auton
// 	int timer = 0;
// 	int count = 0;
// 	intake.move_voltage(12000);
// 	trapdoorPiston.set_value(true); // disengage ratchet

// 	while (count < amount && timer < timeout) {
// 		if (optical.get_hue() > 200 && optical.get_hue() < 230) {
// 			count++;
// 			pros::delay(100);
// 		}
// 		pros::delay(10);
// 		timer += 10;
// 	}

// 	trapdoorPiston.set_value(false); // engage ratchet
// 	intake.brake();
// 	pros::delay(200);
// 	intake.move_voltage(0);
// }