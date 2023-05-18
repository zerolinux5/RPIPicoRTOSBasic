#include <memory>

// Free RTOS
#include <FreeRTOS.h>
#include <task.h>

// Pico

// User
#include "motor_task.hpp"
#include "classes/l298n.hpp"
#include "classes/motordirection.hpp"


void motor_task(void *pvParameters) {
    int ena = 4;
    int int1 = 3;
    int int2 = 2;
    int enb = 6;
    int int3 = 8;
    int int4 = 7;
    std::unique_ptr<L298n> motors = std::make_unique<L298n>(ena, int1, int2, enb, int3, int4, 500);
    const uint32_t delay = 1000;
    // Needed to keep looping
    while (1) {
        motors->setDirection(MotorDirection::FORWARD);
        motors->setSpeed(50);
        vTaskDelay(delay);
        motors->stop();
        vTaskDelay(delay);
    }
}
