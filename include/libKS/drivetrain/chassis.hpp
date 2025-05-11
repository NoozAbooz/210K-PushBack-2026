#pragma once
#include "main.h"

namespace ks {
    void moveRaw(int voltage, int time);
    void moveStraight(float length, int timeout, lemlib::MoveToPointParams params);
    double driveCurve(double input, double curve);
    void arcadeDrive(int linCurve = 0, int rotCurve = 0, double turnScale = 1);
}