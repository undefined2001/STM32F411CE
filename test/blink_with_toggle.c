#include "gpio.h"

//Defining the led pin for this board the led is on pin number 13
const uint8_t led_pin = 13;

int main()
{
    /*
    Configuring the GPIO according to the needs
    1. pin is 13
    2. mode is output Mode
    3. spped is fast
    4. gpio output is push/pull mode
    */
    GPIO_Config_TypeDef led_config;
    led_config.pin = led_pin;
    led_config.mode = GPIO_OUTPUT;
    led_config.speed = GPIO_OUT_FAST_SPEED;
    led_config.otype = GPIO_OUT_PP;


    gpio_clock_init(GPIOC, ENABLE);
    gpio_init(GPIOC, led_config);


    while (1)
    {
        gpio_toggle_pin(GPIOC, led_pin, 1000);
    }
}