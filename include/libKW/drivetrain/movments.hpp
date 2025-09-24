#pragma once
#include "main.h"

namespace kw {
	enum LateralDirection { CW = 1, CCW = -1 };
	void turnToAngle(double turn_angle, double time_limit_msec, double max_output = 127, bool exit = true);
	void moveTo(double distance_in, double time_limit_msec, double max_output = 127, bool exit = true);

	void moveToPoint(double x, double y, double time_limit_msec, bool forwards, double max_output = 127, bool exit = true, bool overturn = false);
}