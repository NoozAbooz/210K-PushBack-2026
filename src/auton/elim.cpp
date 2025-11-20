#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void right_elim() {
    intakeMacro("L1");
    kw::driveTo(26.5, 1500, 127, false);
  

}

void left_elim() {
    intakeMacro("L1");
    kw::driveTo(26.5, 1500, 127, false);
}