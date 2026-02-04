#pragma once

// 3rd party libraries
#include "libKW/api.hpp"
#include "robodash/api.h"
extern rd::Console console;
extern rd_view_t *gifview;
extern rd_view_t *allianceview;
extern rd::Selector gui_selector;
extern rd_view_t *sensorview;
extern void rdconfig_init();

// libKW
extern std::string alliance;
extern std::string field_status;

extern void competitionTelemtryRefresh();
extern void initTelemetry();
extern std::string rumble_pattern;

extern kw::velocity_controller intake_velocity;

/* Functions */
extern void drive_arcade();

extern void refreshSubsys1();
extern void refreshSubsys2();
extern void refreshSubsys3();
extern void refreshSubsys4();
extern bool loaderStatus;
extern bool blockerStatus;
extern bool wingStatus;

/* Macros (mainly intended to be called in auton)*/
extern bool intakeLock; // true = disabled intaking, false = normal
extern void intakeMacro(std::string str); // put "R1", "R2", "L1", "L2" for normal mode, "HOARD_R1", "HOARD_R2", "HOARD_L1", "HOARD_L2" for hoard mode
extern std::string intakeMacroStatus;
extern void stopIntake(); // stops all intake motors
extern void initColourSort();
extern bool toggleColourSort; // true = enabled colour sorting, false = disabled

/* Autons */
// AWP Routines
extern void true_sawp();
extern void sawp();

extern void legacy_sawp();
extern void left_half();
extern void right_half();

// Skills Routines
extern void skills();
extern void Legacy_skills();

// Elim Routines
extern void right_elim();
extern void left_elim();
extern void left_7();
extern void right_7();
