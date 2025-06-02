#include "main.h"

void sawp() {
    // libKS MTPoint v0.1
// Starting point: (-58.48 in, 15.34 in)
    chassis.moveToPoint(0.00, 0.00, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 1
    chassis.moveToPoint(-0.00, 30.26, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 2
    chassis.turnToheading(270, 1000);
    chassis.moveToPoint(31.55, 30.26, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 3
    chassis.moveToPoint(36.05, 7.08, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 4
    chassis.moveToPoint(48.93, -6.44, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 5
    chassis.moveToPoint(34.12, -39.92, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 6
    chassis.moveToPoint(48.93, -23.18, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 7
    chassis.moveToPoint(0.64, -62.45, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 8
    chassis.moveToPoint(-7.73, -63.09, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 9
    chassis.moveToPoint(34.12, -63.09, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}); // Point 10

}

void left_half() { // Left Side Half Solo AWP

}

void right_half() { // Right Side Half Solo AWP

}