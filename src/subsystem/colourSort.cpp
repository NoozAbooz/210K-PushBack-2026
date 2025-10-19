#include "main.h"

bool toggleColourSort = false;
bool intakeLock = false;
void initColourSort() { // intended to be called in auton
	pros::Task ([] {
		while (true) {
			// if (toggleColourSort) {
			// 	// red range: 8-25
			// 	// blue range: 200-230
			
			// 	if (((alliance == "red" || alliance == "na") && (optical.get_hue() > 200 && optical.get_hue() < 230))) {
			// 		intakeLock = true;

			// 		intakeMacro("HOARD_L1");
			// 		pros::delay(800);
			// 		intakeMacro("L1");

			// 		intakeLock = false;
			// 	}
			// }
			pros::delay(10);
		}
	});
}