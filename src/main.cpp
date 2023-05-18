// Free RTOS
#include <FreeRTOS.h>
#include <task.h>

// General
#include <stdio.h>
#include <memory>

// Pico
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

// User made
#include "tasks/led_task.hpp"
#include "tasks/motor_task.hpp"

int main() {
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    xTaskCreate(led_task, "LED Task", 256, NULL, 1, NULL);
    xTaskCreate(motor_task, "Motor Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}

// Notes: