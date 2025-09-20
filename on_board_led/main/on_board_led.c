#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#define ON_BOARD_LED 2

void app_main(void)
{
    char *outTaskName = pcTaskGetName(NULL);

    ESP_LOGI(outTaskName, "Hello, starting up!\n");

    gpio_reset_pin(ON_BOARD_LED);
    gpio_set_direction(ON_BOARD_LED, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(ON_BOARD_LED, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        gpio_set_level(ON_BOARD_LED, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
