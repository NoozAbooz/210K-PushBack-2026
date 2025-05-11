#include "main.h"

ks::PIDConstants::PIDConstants(double kP, double kI, double kD) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
}

void ks::PIDConstants::setPIDConstants(double kP, double kI, double kD) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
}

ks::PID::PID() {  
}

ks::PID::PID(PIDConstants* constants) {
    this->constants = constants;
}

void ks::PID::reset() {
    this->integral = 0;
    this->prevError = 0;
    this->derivative = 0;
}

void ks::PID::setConstants(double kP, double kI, double kD) {
    this->constants->kP = kP;
    this->constants->kI = kI;
    this->constants->kD = kD;
}

double ks::PID::output(double error) {
    this->derivative = error - prevError;
    this->integral += error;

    if (error / fabs(error) != this->prevError / fabs(this->prevError)) {
        this->integral = 0;
    }
    double output = (this->constants->kP * error) + (this->constants->kI * integral) + (this->constants->kD * derivative);
    this->prevError = error;
    return output;
}