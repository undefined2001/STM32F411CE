#include "gpio.h"
#include "util.h"

/**
@blockutility: These are the utility function used in this particular source file
*/

/************
@function: __get_port_code
@params:
  - GPIO Typedef
@result: returns the code for the corresponding number acording to the port number
*************/
__STATIC_INLINE uint8_t __get_port_code(GPIO_TypeDef *GPIOx)
{
    /*Using Ternary to make the code size small*/
    return (GPIOx == GPIOA)? 0x0U:\
           (GPIOx == GPIOB)? 0x1U:\
           (GPIOx == GPIOC)? 0x2U:\
           (GPIOx == GPIOD)? 0x3U:\
           (GPIOx == GPIOE)? 0x4U:\
           (GPIOx == GPIOH)? 0x7U: 0x0U;
}


/**************
@function: __syscfg_init
@params:
  - GPIO_Typedef
  - uint8_t 
@result: turn on the clock for the syscfgr and set the exticr for the corresponding exit(external interrupt)
***************/
__STATTIC_VOID __syscfgr_init(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    /*Enabling Clock for SYSCFGR Register*/
    SYSCFGR_CLK_EN();

    /*Getting the port number which need to put inside the exticr*/
    const uint8_t port_code = __get_port_code(GPIOx);

    /*Getting the index needed to access from the array of exticr*/
    uint8_t exti_index = (uint8_t)(pin / 4);

    /*Getting the position where we need to put the port number(code)*/
    uint8_t register_pos = (uint8_t)((pin % 4) * 4);

    /*Configuring the exticr*/
    SYSCFG->EXTICR[exti_index] |= (port_code << register_pos);
}


/************
@function: __exti_init
@params:
  - uint8_t mode
  - uint8_t pin
@result: configure the exti faling/rising trigger and umask the imr(Interrupt Mask Register)
************/
__STATTIC_VOID __exti_init(uint8_t mode, uint8_t pin)
{
    if (mode == GPIO_IT_FTSR)
    {
        /*Enable Falling Edge Trigger*/
        EXTI->FTSR |= (1 << pin);

        /*Disable Rising Edge Trigger*/
        EXTI->RTSR &= ~(1 << pin);
    }
    else if (mode == GPIO_IT_RTSR)
    {
        /*Enable Rising Edge Trigger*/
        EXTI->RTSR |= (1 << pin);

        /*Disable Falling Edge Trigger*/
        EXTI->FTSR &= ~(1 << pin);
    }
    else if (mode == GPIO_IT_FRTSR)
    {
        /*Enable Falling Edge Trigger*/
        EXTI->FTSR |= (1 << pin);

        /*Enable Rising Edge Trigger*/
        EXTI->RTSR |= (1 << pin);
    }

    /*Unmasking the Interrupt Mask Register*/
    EXTI->IMR |= (1 << pin);
}

/**
@endblockutility: Here the block of the utility function ends
*/


/************
@function: gpio_clcok_init
@params:
  - GPIO_TypeDef *GPIOx (a pointer of GPIO_TypeDef)
  - uint8_t state
@result: Activate the clock for the corresponding GPIO port
************/
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


/************
@function: gpio_init
@params:
  - GPIO_TypeDef *GPIOx (a pointer of GPIO_TypeDef)
  - GPIO_Config_TypeDef config
@result: Initialize the GPIO pin for according to the configuration
************/
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_Config_TypeDef config)
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
    else
    {
        // Setting the mode to input Mode
        GPIOx->MODER &= ~(1 << (2 * config.pin) | 1 << (2 * config.pin + 1));

        /*Clearing the bits responsible for the pullup/down of the given pin*/
        GPIOx->PUPDR &= ~(1 << (2 * config.pin) | 1 << (2 * config.pin + 1));

        /*Configuring the bits responsible for the pullup/down of the given pin*/
        GPIOx->PUPDR |= (config.pupd << (2 * config.pin));

        /*Enabling Clock For SYSCFGR*/
        __syscfgr_init(GPIOx, config.pin);

        /*Configuring The Exti*/
        __exti_init(config.mode, config.pin);
    }
}


/************
@function: gpio_write_pin
@params:
  - GPIO_TypeDef *GPIOx (a pointer of GPIO_TypeDef)
  - uint8_t pin 
  - uint8_t state
@result: making the gpio state high or low
************/
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



/************
@function: gpio_read_pin
@params:
  - GPIO_TypeDef *GPIOx (a pointer of GPIO_TypeDef)
  - uint8_t pin
@result: returns the current state of a gpio pin
************/
uint8_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    return ((GPIOx->IDR >> pin) & 0x1U);
}


/************
@function: gpio_toggle_pin
@params:
  - GPIO_TypeDef *GPIOx (a pointer of GPIO_TypeDef)
  - uint8_t pin
  - uint8_t delay
@result: toggle the state of the pin after a certain amount delay
************/
void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint32_t delay)
{
    GPIOx->BSRR |= (1 << (16 + pin));
    delay_ms(delay);
    GPIOx->BSRR |= (1 << pin);
    delay_ms(delay);
}


/************
@function: gpio_irq_handler
@params:
  - uint8_t pin
@result: clear the exti pr(pending register) for the corresponding pin
************/
void gpio_irq_handler(uint8_t pin)
{
    EXTI->PR |= (1 << pin);
}