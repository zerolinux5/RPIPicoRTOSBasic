// Pico
#include "hardware/pwm.h"
#include "pico/stdlib.h"

// User
#include "motor.hpp"

void Motor::basicInit() {
    // Basic output GPIO pins
    gpio_init(pin1);
    gpio_set_dir(pin1, GPIO_OUT);
    gpio_init(pin2);
    gpio_set_dir(pin2, GPIO_OUT);
    // PWM GPIO pin
    slice_num = pwm_gpio_to_slice_num(pinSpeed);
    chan = pwm_gpio_to_channel(pinSpeed);
    gpio_set_function(pinSpeed, GPIO_FUNC_PWM);
    pwm_set_enabled(slice_num, true);
    pwm = PWM();
}

Motor::Motor(int pin1, int pin2, int pinSpeed):
        direction(MotorDirection::STOPPED),
        frequency(0),
        pin1(pin1),
        pin2(pin2),
        pinSpeed(pinSpeed),
        resolution(0),
        speed(0) {
    basicInit();
}

Motor::Motor(int pin1, int pin2, int pinSpeed, int frequency):
        direction(MotorDirection::STOPPED),
        frequency(0),
        pin1(pin1),
        pin2(pin2),
        pinSpeed(pinSpeed),
        resolution(0),
        speed(0) {
    basicInit();
    setFrequency(frequency);
}

void Motor::setFrequency(int frequency) {
    if (frequency != this->frequency) {
        this->frequency = frequency;
        this->resolution = pwm.pwm_set_freq(slice_num, chan, frequency);
    }
}

void Motor::setSpeed(int speed) {
    if (speed != this->speed) {
        this->speed = speed;
        pwm.pwm_set_duty(slice_num, chan, speed);
    }
}

void Motor::setDirection(MotorDirection direction) {
    if (direction != this->direction) {
        this->direction = direction;
        if (direction == MotorDirection::FORWARD) {
            gpio_put(pin1, 0);
            gpio_put(pin2, 1);
        } else {
            gpio_put(pin1, 1);
            gpio_put(pin2, 0);
        }
    }
}

void Motor::stop() {
    this->speed = 0;
    this->direction = MotorDirection::STOPPED;
    gpio_put(pin1, 0);
    gpio_put(pin2, 0);
}

// 53
// 157