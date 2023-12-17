#include "gpio.h"
#include "util.h"

//Defining the led pin for this board the led is on pin number 13
uint8_t led_pin = 13;

int main()
{
    /*
    Configuring the GPIO according to the needs
    1. pin is 13
    2. mode is output Mode
    3. spped is fast
    4. gpio output is push/pull mode
    */
    GPIO_Config_Typedef config;
    config.pin = led_pin;
    config.mode = GPIO_OUTPUT;
    config.speed = GPIO_OUT_FAST_SPEED;
    config.otype = GPIO_OUT_PP;

    /*Initializing the clock for GPIOC*/
    gpio_clock_init(GPIOC, ENABLE);

    /*Initializing the corresponding pin*/
    gpio_init(GPIOC, config);

    while (1)
    {
        //Writing high to the led pin
        gpio_write_pin(GPIOC, led_pin, LOW);
        //adding delay
        delay_ms(1000);
        //Writing low to the led pin
        gpio_write_pin(GPIOC, led_pin, HIGH);
        //adding delay
        delay_ms(1000);
    }
}