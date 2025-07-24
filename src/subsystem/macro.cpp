#include "main.h"

void scoreOwnColour(int timeout) { // intended to be called in auton
	int timer = 0;
	// red range: 8-25
	// blue range: 200-230
	intake.move_voltage(12000);
	trapdoorPiston.set_value(true); // disengage ratchet

	if (alliance == "red") {
		while (!(optical.get_hue() > 200 && optical.get_hue() < 230) && timer < timeout) {
			pros::delay(10);
			timer += 10;
		}
	} else if (alliance == "blue") {
		while (!(optical.get_hue() > 8 && optical.get_hue() < 30) && timer < timeout) {
			pros::delay(10);
			timer += 10;
		}
	}

	trapdoorPiston.set_value(false); // engage ratchet
	intake.brake();
	pros::delay(200);
	intake.move_voltage(0);
}