#include "gpio.h"
#include "util.h"

uint8_t led_pin = 13;

int main()
{
    GPIO_Config_Typedef config;
    config.pin = led_pin;
    config.mode = GPIO_OUTPUT;
    config.speed = GPIO_OUT_FAST_SPEED;
    config.otype = GPIO_OUT_PP;

    gpio_clock_init(GPIOC, ENABLE);
    gpio_init(GPIOC, config);

    while (1)
    {
        gpio_write_pin(GPIOC, led_pin, LOW);
        delay_ms(1000);
        gpio_write_pin(GPIOC, led_pin, HIGH);
        delay_ms(1000);
    }
}