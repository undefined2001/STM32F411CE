#include "gpio.h"

const uint8_t led_pin = 13;
const uint8_t button_pin = 0;

int main()
{
    GPIO_Config_Typedef led_config;
    led_config.pin = led_pin;
    led_config.mode = GPIO_OUTPUT;
    led_config.speed = GPIO_OUT_FAST_SPEED;
    led_config.otype = GPIO_OUT_PP;

    GPIO_Config_Typedef btn_config;
    btn_config.pin = button_pin;
    btn_config.mode = GPIO_INPUT;
    btn_config.pupd = GPIO_PULLUP;

    gpio_clock_init(GPIOC, ENABLE);
    gpio_clock_init(GPIOA, ENABLE);
    gpio_init(GPIOC, led_config);
    gpio_init(GPIOA, btn_config);

    while (1)
    {
        gpio_toggle_pin(GPIOC, led_pin, 1000);
    }
}

// if (!gpio_read_pin(GPIOA, button_pin))
//         {
//             gpio_write_pin(GPIOC, led_pin, LOW);
//         }
//         else
//         {
//             gpio_write_pin(GPIOC, led_pin, HIGH);
//         }