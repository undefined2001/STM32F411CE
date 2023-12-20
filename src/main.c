#include "gpio.h"
#include "nvic.h"
const uint8_t led_pin = 13;
const uint8_t button_pin = 0;


int main()
{
    /**
     * @config: to make the clock speed 100Mhz
     */

    /**
     * TODO: need to implement the system clock at 100MHz so need to implement it later
     * TODO: need to research a bit more about it since I was unable to implement it once
    */

    // Turning off HSI
    RCC->CR &= ~(0x1U << 0U);

    // Turning on HSE
    RCC->CR |= (0x1U << 16U);
    while (!(RCC->CR >> 17 & 0x01))
        ; // Wait until HSE is ready

    // Turning PLL On
    RCC->CR |= (0x01U << 24);
    // Waiting Until Pll is Ready
    while (!(RCC->CR >> 25 & 0x01))
        ;

    // Setting HSE as PLL Source
    RCC->PLLCFGR |= (0x1U << 22);

    // Configuring PLLM
    RCC->PLLCFGR &= ~(0xFU << 0U); // Clear PLLM bits
    RCC->PLLCFGR |= (0x2U << 0U);

    // Configuring PLLN
    RCC->PLLCFGR &= ~(0x7FU << 6U); // Clear PLLN bits
    RCC->PLLCFGR |= (0x28U << 6U);

    // Configuring PLLP
    RCC->PLLCFGR &= ~(0x3U << 16U);
    RCC->PLLCFGR |= (0x1U << 16U);

    // Setting PLL as System Clock
    RCC->CFGR &= ~(0x3U << 0U); // Clear SW bits
    RCC->CFGR |= (0x2U << 0U);

    // Setting AHB1 prescaler
    RCC->CFGR &= ~(0xFU << RCC_CFGR_HPRE_Pos);

    /* Configuring the AHB1 prescaler */
    RCC->CFGR |= (0x0U << RCC_CFGR_HPRE_Pos);

    // Setting APB1 prescaler
    RCC->CFGR &= ~(0x7U << RCC_CFGR_PPRE1_Pos);
    RCC->CFGR |= (0x4U << RCC_CFGR_PPRE1_Pos);

    /*End Config*/
    GPIO_Config_TypeDef led_config;
    led_config.pin = led_pin;
    led_config.mode = GPIO_OUTPUT;
    led_config.speed = GPIO_OUT_HIGH_SPEED;
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
        delay_ms(500);
        gpio_write_pin(GPIOC, led_pin, HIGH);
        delay_ms(500);
    }
}

void EXTI0_IRQHandler()
{
    gpio_irq_handler(button_pin);
    for (int i = 0; i < 5; i++)
    {
        gpio_toggle_pin(GPIOC, led_pin, 2000);
    }
}