#include <memory>

// Free RTOS
#include <FreeRTOS.h>
#include <task.h>

// Pico

// User
#include "motor_task.hpp"
#include "classes/motor.hpp"


void motor_task(void *pvParameters) {
    std::unique_ptr<Motor> m1 = std::make_unique<Motor>(3, 2, 4, 500);
    std::unique_ptr<Motor> m2 = std::make_unique<Motor>(8, 7, 6, 500);
    const uint32_t delay = 1000;
    // Needed to keep looping
    while (1) {
        m1->setDirection(MotorDirection::FORWARD);
        m1->setSpeed(50);
        m2->setDirection(MotorDirection::FORWARD);
        m2->setSpeed(50);
        vTaskDelay(delay);
        m1->stop();
        m2->stop();
        vTaskDelay(delay);
    }
}
