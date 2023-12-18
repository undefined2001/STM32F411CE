#include "gpio.h"

const uint8_t led_pin = 13;
const uint8_t button_pin = 0;

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

    /*
    Configuring the GPIO according to the needs
    1. pin is 0
    2. mode is input Mode
    3. activating pull up 
    */
    GPIO_Config_TypeDef btn_config;
    btn_config.pin = button_pin;
    btn_config.mode = GPIO_INPUT;
    btn_config.pupd = GPIO_PULLUP;

    /*Initializing the clock for GPIOC*/
    gpio_clock_init(GPIOC, ENABLE);

    /*Initializing the clock for GPIOC*/
    gpio_clock_init(GPIOA, ENABLE);

    /*Initializing the corresponding pin*/
    gpio_init(GPIOC, led_config);

    /*Initializing the corresponding pin*/
    gpio_init(GPIOA, btn_config);

    while (1)
    {
        //Checking if the button is clicked 
        if (gpio_read_pin(GPIOA, button_pin))
        {
            //then turn the led on
            gpio_write_pin(GPIOC, led_pin, HIGH);
        }
        else
        {
            //then turn the led off otherwise
            gpio_write_pin(GPIOC, led_pin, LOW);
        }
    }
}