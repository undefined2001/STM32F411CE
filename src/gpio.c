#include "gpio.h"
#include "util.h"
void gpio_clock_init(GPIO_TypeDef *GPIOx, uint8_t state)
{
    if (state == ENABLE)
    {
        if (GPIOx == GPIOA)
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        }
        else if (GPIOx == GPIOB)
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        }
        else if (GPIOx == GPIOC)
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        }
        else if (GPIOx == GPIOD)
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
        }
    }
    else if (state == DISABLE)
    {
        if (GPIOx == GPIOA)
        {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
        }
        else if (GPIOx == GPIOB)
        {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
        }
        else if (GPIOx == GPIOC)
        {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
        }
        else if (GPIOx == GPIOD)
        {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
        }
    }
}

void gpio_init(GPIO_TypeDef *GPIOx, GPIO_Config_Typedef config)
{
    /*Clearing the bits responsible for the mode of the given pin*/
    GPIOx->MODER &= ~(1 << (2 * config.pin) | 1 << (2 * config.pin + 1));

    /*Configuring the bits responsible for the mode of the given pin*/
    GPIOx->MODER |= (config.mode << (2 * config.pin));

    if (config.mode == GPIO_OUTPUT)
    {
        /*Clearing the bits responsible for the speed of the given pin*/
        GPIOx->OSPEEDR &= ~(1 << (2 * config.pin) | 1 << (2 * config.pin + 1));

        /*Configuring the bits responsible for the speed of the given pin*/
        GPIOx->OSPEEDR |= (config.speed << (2 * config.pin));

        /*Configuring the Output Type*/
        GPIOx->OTYPER |= (config.otype << config.pin);
    }
    else if (config.mode == GPIO_INPUT)
    {
        /*Clearing the bits responsible for the pullup/down of the given pin*/
        GPIOx->PUPDR &= ~(1 << (2 * config.pin) | 1 << (2 * config.pin + 1));

        /*Configuring the bits responsible for the pullup/down of the given pin*/
        GPIOx->PUPDR |= (config.pupd << (2 * config.pin));
    }
}

void gpio_write_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state)
{
    if (state == HIGH)
    {
        GPIOx->BSRR |= (1 << pin);
    }
    else if (state == LOW)
    {
        GPIOx->BSRR |= (1 << (16 + pin));
    }
}

uint8_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    return ((GPIOx->IDR >> pin) & 0x1U);
}

void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint32_t delay)
{
    GPIOx->BSRR |= (1 << pin);
    delay_ms(delay);
    GPIOx->BSRR |= (1 << (16 + pin));
    delay_ms(delay);
}