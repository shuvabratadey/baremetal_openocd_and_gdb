#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

static const char *TAG = "LED_STRIP_BLINK";

typedef enum {
    LED_COLOUR_RED,
    LED_COLOUR_GREEN,
    LED_COLOUR_BLUE,
} led_colour_t;

#define BLINK_GPIO CONFIG_BLINK_GPIO

static led_strip_handle_t led_strip;

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO,
        .max_leds = 1, // at least one LED on board
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);
}

void app_main(void)
{
    /* Configure the peripheral according to the LED type */
    configure_led();

    while (1) {
        for(led_colour_t colour = LED_COLOUR_RED; colour <= LED_COLOUR_BLUE; colour++) {
            switch(colour) {
                case LED_COLOUR_RED:
                    led_strip_set_pixel(led_strip, 0, 255, 0, 0);
                    ESP_LOGI(TAG, "Led Colour: Red");
                    break;
                case LED_COLOUR_GREEN:
                    led_strip_set_pixel(led_strip, 0, 0, 255, 0);
                    ESP_LOGI(TAG, "Led Colour: Green");
                    break;
                case LED_COLOUR_BLUE:
                    led_strip_set_pixel(led_strip, 0, 0, 0, 255);
                    ESP_LOGI(TAG, "Led Colour: Blue");
                    break;
            }
            led_strip_refresh(led_strip);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}
