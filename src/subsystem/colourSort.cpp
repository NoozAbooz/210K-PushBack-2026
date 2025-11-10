#include "main.h"

bool toggleColourSort = false;
bool intakeLock = false;
void initColourSort() { // intended to be called in auton
	pros::Task ([] {
		while (true) {
			if (toggleColourSort) {
				// red range: 8-25
				// blue range: 200-230
			
				if (((alliance == "red" || alliance == "na") && (optical.get_hue() > 200 && optical.get_hue() < 230)) || 
					((alliance == "blue") && (optical.get_hue() > 8 && optical.get_hue() < 25))) {
					pros::delay(50); // debounce
					intakeLock = true;
					intakeMacro("R2");
					pros::delay(500);
					intakeLock = false;
					intakeMacro("R1");
				}
			}
			pros::delay(10);
		}
	});
}