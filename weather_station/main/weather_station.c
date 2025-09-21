#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "dht.h"
#include "max7219.h"

#ifndef APP_CPU_NUM
#define APP_CPU_NUM PRO_CPU_NUM
#endif

#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 0, 0)
#define HOST    HSPI_HOST
#else
#define HOST    SPI2_HOST
#endif

#define CASCADE_SIZE 1
#define MOSI_PIN GPIO_NUM_23
#define CS_PIN GPIO_NUM_5
#define CLK_PIN GPIO_NUM_18

#define DHT_PIN GPIO_NUM_4   // Change to the GPIO you use
#define DHT_TYPE DHT_TYPE_DHT11 // or DHT_TYPE_DHT11
                                //
int16_t temperature = 0;
int16_t humidity = 8;

static const uint64_t symbols[] = {

    0x3c66666e76663c00, // digits 0-9
    0x7e1818181c181800,
    0x7e060c3060663c00,
    0x3c66603860663c00,
    0x30307e3234383000,
    0x3c6660603e067e00,
    0x3c66663e06663c00,
    0x1818183030667e00,
    0x3c66663c66663c00,
    0x3c66607c66663c00,

//    0x3c66766e66663c00, // 0
//    0x18181c1818187e00, // 1
//    0x3c606066300c067e, // 2
//    0x3c60606638663c00, // 3
//    0x18387c30307e3000, // 4
//    0x7e067e0600603c00, // 5
//    0x3c06663e66663c00, // 6
//    0x7e66303018181800, // 7
//    0x3c66663c66663c00, // 8
//    0x3c66667c60663c00, // 9


    0x383838fe7c381000, // arrow up
    0x10387cfe38383800, //arrow down
    0x10307efe7e301000, //arrow right
    0x1018fcfefc181000 //arrow left

};
static const size_t symbols_size = sizeof(symbols) - sizeof(uint64_t) * CASCADE_SIZE;

void max7219_task(void *pvParameter)
{
    spi_bus_config_t cfg = {
       .mosi_io_num = MOSI_PIN,
       .miso_io_num = -1,
       .sclk_io_num = CLK_PIN,
       .quadwp_io_num = -1,
       .quadhd_io_num = -1,
       .max_transfer_sz = 0,
       .flags = 0
    };
    ESP_ERROR_CHECK(spi_bus_initialize(HOST, &cfg, 1));

    max7219_t dev = {
       .cascade_size = CASCADE_SIZE,
       .digits = 0,
       .mirrored = false
    };
    ESP_ERROR_CHECK(max7219_init_desc(&dev, HOST, MAX7219_MAX_CLOCK_SPEED_HZ, CS_PIN));
    ESP_ERROR_CHECK(max7219_init(&dev));

    size_t offs = 0;

    while (1) {
        max7219_draw_image_8x8(&dev, 0, (const uint8_t *)&symbols[(humidity / 10) % 10]);
        vTaskDelay(pdMS_TO_TICKS(500));
        offs = (offs + 1) % symbols_size;
    }
}

void dht_task(void *pvParameter)
{
    while (1) {
        esp_err_t ret = dht_read_data(DHT_TYPE, DHT_PIN, &humidity, &temperature);
        if (ret == ESP_OK) {
            printf("Temperature: %.1f°C, Humidity: %.1f%%\n", temperature / 10.0, humidity / 10.0);
        } else {
            printf("Could not read data from DHT sensor, err = %d\n", ret);
        }
        // wait 2 seconds before next read
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    xTaskCreate(max7219_task, "task1", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(dht_task, "task2", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
