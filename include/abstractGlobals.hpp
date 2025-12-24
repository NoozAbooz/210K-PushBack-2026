#pragma once

// 3rd party libraries
#include "gif-pros/gifclass.hpp"
#include "robodash/api.h"
#include "liblvgl/lvgl.h"

extern rd::Console console;
extern rd_view_t *gifview;
extern rd_view_t *allianceview;
extern rd::Selector gui_selector;
extern rd_view_t *sensorview;
extern void rdconfig_init();

extern std::string alliance;
extern std::string field_status;

extern void competitionTelemtryRefresh();
extern void initTelemetry();
extern std::string rumble_pattern;

/* Functions */
extern void drive_arcade();

extern void refreshIntake();
extern void refreshLoader();
extern void refreshKnocker();
extern void refreshWing();
extern bool loaderStatus;
extern bool knockerStatus;
extern bool wingStatus;

/* Macros (mainly intended to be called in auton)*/
extern bool intakeLock; // true = disabled intaking, false = normal
extern void intakeMacro(std::string str); // put "R1", "R2", "L1", "L2" for normal mode, "HOARD_R1", "HOARD_R2", "HOARD_L1", "HOARD_L2" for hoard mode
extern std::string intakeMacroStatus;
extern void stopIntake(); // stops all intake motors
extern void initColourSort();
extern bool toggleColourSort; // true = enabled colour sorting, false = disabled

/* Autons */
extern void sawp();
extern void nooz_sawp();
 
extern void left_half();
extern void right_half();
extern void skills();
extern void right_elim();
extern void left_elim();
extern void left_7();
extern void right_7();
