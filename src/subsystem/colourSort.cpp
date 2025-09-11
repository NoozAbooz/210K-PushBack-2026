#include "main.h"

bool toggleColourSort = true;
bool intakeLock = false;
void initColourSort(int timeout) { // intended to be called in auton
	pros::Task ([] {
		while (true) {
			if (toggleColourSort) {
				// red range: 8-25
				// blue range: 200-230
			
				if (((alliance == "red" || alliance == "na") && (optical.get_hue() > 200 && optical.get_hue() < 230)) || 
					((alliance == "blue") && (optical.get_hue() > 8 && optical.get_hue() < 30))) {
					intakeLock = true;

					intakeLock = false;
				}
			}
			pros::delay(10);
		}
	});
}