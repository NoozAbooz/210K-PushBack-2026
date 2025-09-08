#include "main.h"

bool toggleColourSort = true;
void initColourSort(int timeout) { // intended to be called in auton
	pros::Task ([] {
		while (true) {
			if (toggleColourSort) {
				// red range: 8-25
				// blue range: 200-230
				intake.move_voltage(12000);

				if (alliance == "red" || alliance == "na") {
					while (!(optical.get_hue() > 200 && optical.get_hue() < 230) && timer < timeout) {
						pros::delay(10);
					}
				} else if (alliance == "blue") {
					while (!(optical.get_hue() > 8 && optical.get_hue() < 30) && timer < timeout) {
						pros::delay(10);
					}
				}
			
				if () {

				} else {
					
				}
			}
			pros::delay(10);
		}
	});
}