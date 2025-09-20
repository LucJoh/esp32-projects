#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "dht.h"

#define DHT_PIN GPIO_NUM_4   // Change to the GPIO you use
#define DHT_TYPE DHT_TYPE_DHT11 // or DHT_TYPE_DHT11

void app_main(void)
{
    int16_t temperature = 0;
    int16_t humidity = 0;

    while (1) {
        esp_err_t ret = dht_read_data(DHT_TYPE, DHT_PIN, &humidity, &temperature);
        if (ret == ESP_OK) {
            printf("Temperature: %.1f°C, Humidity: %.1f%%\n", temperature / 10.0, humidity / 10.0);
        } else {
            printf("Could not read data from DHT sensor, err = %d\n", ret);
        }

        vTaskDelay(pdMS_TO_TICKS(2000)); // wait 2 seconds before next read
    }
}

