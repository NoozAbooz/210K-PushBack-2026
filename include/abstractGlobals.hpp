#pragma once

// 3rd party libraries
#include "gif-pros/gifclass.hpp"
#include "robodash/api.h"
#include "liblvgl/lvgl.h"
#include "maelstrom/api.hpp"

extern rd::Console console;
extern rd_view_t *gifview;
extern rd_view_t *allianceview;
extern rd::Selector gui_selector;
extern rd_view_t *sensorview;
void rdconfig_init();

extern std::string alliance;
extern std::string field_status;

extern void competitionTelemtryRefresh();
extern void initTelemetry();
extern std::string rumble_pattern;

/* Functions */
void drive_arcade();

void refreshIntake();
void toggleHoard();
void park();
void refreshLoader();

/* Macros (mainly intended to be called in auton)*/
extern bool intakeLock; // true = disabled intaking, false = normal
void intakeMacro(std::string str); // put "R1", "R2", "L1", "L2" for normal mode, "HOARD_R1", "HOARD_R2", "HOARD_L1", "HOARD_L2" for hoard mode
void stopIntake(); // stops all intake motors
extern bool toggleColourSort; // true = enabled colour sorting, false = disabled

/* Autons */
void sawp();
void nooz_sawp();

void left_half();
void right_half();
void skills();
void right_elim();
void left_elim();
