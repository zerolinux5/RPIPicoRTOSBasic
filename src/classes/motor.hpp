#pragma once

#include "pwm.hpp"
#include "motordirection.hpp"

class Motor {
        int chan;
        MotorDirection direction;
        int frequency;
        int pin1;
        int pin2;
        int pinSpeed;
        int resolution;
        int slice_num;
        int speed;
        PWM pwm;
        void basicInit();
    public:
        Motor(int pin1, int pin2, int pinSpeed);
        Motor(int pin1, int pin2, int pinSpeed, int frequency);
        void setFrequency(int frequency);
        void setSpeed(int speed);
        void setDirection(MotorDirection direction);
        void stop();
};
