// Pico
#include "hardware/pwm.h"
#include "pico/stdlib.h"

// User
#include "l298n.hpp"

L298n::L298n (int ena, int int1, int int2, int enb, int int3, int int4)
    :direction(MotorDirection::STOPPED), frequency(0), left(int1, int2, ena), right(int3, int4, enb) {
}

L298n::L298n(int ena, int int1, int int2, int enb, int int3, int int4, int frequency)
    :direction(MotorDirection::STOPPED), frequency(frequency), left(int1, int2, ena, frequency), right(int3, int4, enb, frequency) {
}

void L298n::setFrequency(int frequency) {
    if (frequency != this->frequency) {
        this->frequency = frequency;
        left.setFrequency(frequency);
        right.setFrequency(frequency);
    }
}

void L298n::setSpeed(int speed) {
    left.setSpeed(speed);
    right.setSpeed(speed);
}

void L298n::setSpeed(int speed, MotorType motorType) {
    switch (motorType) {
        case MotorType::LEFT:
            left.setSpeed(speed);
            break;
        case MotorType::RIGHT:
            right.setSpeed(speed);
            break;
        default:
            break;
    }
}

void L298n::setDirection(MotorDirection direction) {
    // Don't set direction if already going that way
    if (direction != this->direction) {
        // Always set direction
        this->direction = direction;
        // Switch since left and right are only possible at his level
        switch (direction) {
            case MotorDirection::FORWARD:
            case MotorDirection::BACKWARD:
            case MotorDirection::STOPPED:
                left.setDirection(direction);
                right.setDirection(direction);
                break;
            case MotorDirection::LEFT:
                left.setDirection(MotorDirection::BACKWARD);
                right.setDirection(MotorDirection::FORWARD);
                break;
            case MotorDirection::RIGHT:
                left.setDirection(MotorDirection::FORWARD);
                right.setDirection(MotorDirection::BACKWARD);
                break;
            // When in doubt just stop
            default:
                stop();
                break;
        }
    }
}

void L298n::stop() {
    direction = MotorDirection::STOPPED;
    left.stop();
    right.stop();
}