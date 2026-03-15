#include "main.h"

bool toggleColourSort = false;
bool intakeLock = false;
void initColourSort() { // intended to be called in auton
	pros::Task ([] {
		while (true) {
			if (toggleColourSort) {
				// red range: 8-25
				// blue range: 200-230
			
				if (((alliance == "red" || alliance == "na") && (optical.get_hue() > 215 && optical.get_hue() < 225)) || 
					((alliance == "blue") && (optical.get_hue() > 8 && optical.get_hue() < 25))) {
					//pros::delay(50); // debounce
					std::string initialStatus = intakeMacroStatus;
					console.println("Coloursort triggered");
					intakeLock = true;
					intakeMacro("R2");
					pros::delay(150);
					intakeLock = false;

					if (initialStatus == "L1") {
						intakeMacro("L1");
					} else {
						intakeMacro("R1");
					}
				}
			}
			pros::delay(20);
		}
	});
}