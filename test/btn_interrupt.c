#include "gpio.h"
#include "nvic.h"
const uint8_t led_pin = 13;
const uint8_t button_pin = 0;

int main()
{
    GPIO_Config_TypeDef led_config;
    led_config.pin = led_pin;
    led_config.mode = GPIO_OUTPUT;
    led_config.speed = GPIO_OUT_FAST_SPEED;
    led_config.otype = GPIO_OUT_PP;

    GPIO_Config_TypeDef btn_config;
    btn_config.pin = button_pin;
    btn_config.mode = GPIO_IT_FTSR;
    btn_config.pupd = GPIO_PULLUP;

    gpio_clock_init(GPIOC, ENABLE);
    gpio_clock_init(GPIOA, ENABLE);
    gpio_init(GPIOC, led_config);
    gpio_init(GPIOA, btn_config);
    nvic_enable_irq(EXTI0_IRQn);
    nvic_set_priority(EXTI0_IRQn, 15);

    while (1)
    {
        gpio_write_pin(GPIOC, led_pin, LOW);
        delay_ms(100);
        gpio_write_pin(GPIOC, led_pin, HIGH);
        delay_ms(100);
    }
}

void EXTI0_IRQHandler()
{
    gpio_irq_handler(button_pin);
    for (int i = 0; i < 5; i++)
    {
        gpio_toggle_pin(GPIOC, led_pin, 1000);
    }
}