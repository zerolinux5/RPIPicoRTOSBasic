// Free RTOS
#include <FreeRTOS.h>
#include <task.h>

#include "pico/cyw43_arch.h"

#include "led_task.hpp"

void led_task(void *pvParameters) {
    const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;
    const uint delay = 50;
    while (1) {
        cyw43_arch_gpio_put(LED_PIN, 1);
        vTaskDelay(delay);
        cyw43_arch_gpio_put(LED_PIN, 0);
        vTaskDelay(delay);
    }
}
