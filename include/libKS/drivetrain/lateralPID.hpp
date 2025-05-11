#pragma once
#include "main.h"

namespace ks {
	// class LateralPID {
	// 	public:
	// 		LateralPID();
	// 		double kp;
	// 		double ki;
	// 		double kd;
	// 		double timeOut;

	// 		void set_lateral_constants(double kp, double ki, double kd, double timeOut);
	// 		void move_lateral_pid(double target, double maxSpeed, double minSpeed);	
	// };
	
	namespace LateralPID {
		void set_lateral_constants(double kp, double ki, double kd, double timeOut);
		void move_lateral_pid(double target, double maxSpeed, double minSpeed);	
	}
	// extern LateralPID pid;
}
