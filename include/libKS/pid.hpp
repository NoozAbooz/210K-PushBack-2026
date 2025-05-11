using namespace std;
#pragma once
#include <cmath> // Include cmath for fabs()

namespace ks {
    class PIDConstants {
        public:
            PIDConstants(double kP, double kI, double kD);

            void setPIDConstants(double kP, double kI, double kD);
            double kP;
            double kI;
            double kD;
    };

    class PID {
        public:
            PID();
            PID(PIDConstants* constants);

            void reset();

            double output(double error);

            void setConstants(double kP, double kI, double kD);

        protected:
            double integral;
            double prevError;
            double derivative;
            PIDConstants* constants;
    };
}