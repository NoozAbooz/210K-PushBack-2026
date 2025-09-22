#pragma once
#include "main.h"

namespace kw {
	extern double x_pos; // global X
	extern double y_pos; // global Y
	extern double theta; // global theta [0, 359]
	extern double correct_angle; // normalized
}

#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/odom.hpp"

#include "libKW/utilities.hpp"