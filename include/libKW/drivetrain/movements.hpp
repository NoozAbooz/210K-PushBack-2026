#pragma once
#include "main.h"

namespace kw {
	enum LateralDirection { CW = 1, CCW = -1 };

	/**
	 * @brief Delay execution until we are a certain distance AWAY from target
	 *
	 * @param dist_to_target_in Distance away from target at the point to continue execution (in inches)
	 * @param time_limit_msec Maximum time allowed for the wait (in milliseconds)
	 */
	extern void waitUntilDistance(double dist_to_target_in, double time_limit_msec);

	/**
	 * @brief Turn to global angle between [0, 360)
	 *
	 * @param turn_angle Target angle to turn to (in degrees)
	 * @param time_limit_msec Maximum time allowed for the turn (in milliseconds)
	 * @param max_output Maximum output to motors. (0, 127]
	 * @param exit If true, stops the robot at the end; if false, allows chaining
	 */
	extern void turnToAngle(double turn_angle, double time_limit_msec, double max_output = 127, bool exit = true);

	/**
	 * @brief Move laterally (forward and back)
	 *
	 * @param distance_in Distance to drive, either positive or negative (in inches)
	 * @param time_limit_msec Maximum time allowed for the movement (in milliseconds)
	 * @param max_output Maximum output to motors. (0, 127]
	 * @param exit If true, stops the robot at the end; if false, allows chaining
	 */
	extern void driveTo(double distance_in, double time_limit_msec, double max_output = 127, bool exit = true);

	/**
	 * @brief Move using odometry to specified cartesian coordinate
	 *
	 * @param x Distance to drive, either positive or negative (in inches)
	 * @param y Distance to drive, either positive or negative (in inches)
	 * @param time_limit_msec Maximum time allowed for the movement (in milliseconds)
	 * @param forwards Boolean to drive forwards or not (true or false)
	 * @param max_output Maximum output to motors. (0, 127]
	 * @param exit If true, stops the robot at the end; if false, allows chaining
	 * @param overturn If true, allows overturning for sharp turns.
	 */
	extern void moveToPoint(double x, double y, double time_limit_msec, bool forwards = true, double max_output = 127, bool exit = true, bool overturn = false);

	/**
	 * @brief Swing turn by moving only one side of the drivetrain
	 *
	 * @param swing_angle Target angle to swing to (in degrees)
	 * @param time_limit_msec Maximum time allowed for the movement (in milliseconds)
	 * @param forwards Boolean to drive forwards or not (true or false)
	 * @param max_output Maximum output to motors. (0, 127]
	 * @param exit If true, stops the robot at the end; if false, allows chaining
	 */
	extern void swing(double swing_angle, double time_limit_msec, bool forwards = true, double max_output = 127, bool exit = true);

	/**
	 * @brief Move using odometry to specified cartesian coordinate with a curved path
	 *
	 * @param x,y Coordinates to drive to (in inches)
	 * @param a Final angle of the robot (in degrees)
	 * @param dlead Distance to lead the target by (in inches, set higher for curvier path, don't set above 0.6).
	 * @param time_limit_msec Maximum time allowed for the movement (in milliseconds)
	 * @param forwards Boolean to drive forwards or not (true or false)
	 * @param max_output Maximum output to motors. (0, 127]
	 * @param exit If true, stops the robot at the end; if false, allows chaining
	 * @param overturn If true, allows overturning for sharp turns.
	 */
	extern void boomerang(double x, double y, double a, double dlead, double time_limit_msec, bool forwards = true, double max_output = 127, bool exit = true, bool overturn = false);
}