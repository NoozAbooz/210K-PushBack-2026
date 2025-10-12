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

/* Macros */
extern bool intakeLock;
void intakeMacro(std::string str);
void stopIntake();

/* Autons */
void sawp();
void sawp_12();

void left_half();
void right_half();
void skills();
void right_elim();
void left_elim();
