#pragma once
#include "main.h"

namespace ks
{
	class Position{
        public:
            double x;
            double y;
            double theta;
    };

    extern void odomUpdate();
    extern void setOdomPosition(double x_new, double y_new, double theta_new);
    extern void initializeOdom();
    extern pros::Task odom_task;
}