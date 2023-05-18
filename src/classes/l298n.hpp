#pragma once

#include "motor.hpp"
#include "motordirection.hpp"

enum class MotorType {
    LEFT,
    RIGHT,
};

class L298n {
        MotorDirection direction;
        int frequency;
        Motor left;
        Motor right;
    public:
        L298n(int ena, int int1, int int2, int enb, int int3, int int4);
        L298n(int ena, int int1, int int2, int enb, int int3, int int4, int frequency);
        void setFrequency(int frequency);
        void setSpeed(int speed);
        void setSpeed(int speed, MotorType motorType);
        void setDirection(MotorDirection direction);
        void stop();
};
