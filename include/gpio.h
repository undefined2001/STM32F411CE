#include "stm32f411xe.h"
#include "util.h"

#ifndef GPIO_H
#define GPIO_H

#define __STATTIC_VOID static void

#define SYSCFGR_CLK_EN() (RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN)

/*-----------------GPIO Values-------------*/
#define DISABLE 0x0U
#define ENABLE 0x1U
#define LOW 0x0U
#define HIGH 0x1U
/*-----------------GPIO Values-------------*/

/********************************************GPIO Configs*****************************************/

/*----------------------------- Modes -------------------------*/
#define GPIO_INPUT 0x0U     /*GPIO input Mode*/
#define GPIO_OUTPUT 0x1U    /*GPIO output Mode*/
#define GPIO_ALF 0x2U       /*GPIO Alternate Function Mode*/
#define GPIO_ALG 0x3U       /*GPIO Analog Mode*/
#define GPIO_IT_FTSR 0x04U  /*GPIO Interrupt at falling edge(Falling Trigger Selection Register)*/
#define GPIO_IT_RTSR 0x05U  /*GPIO Interrupt at Rising edge(Rising Trigger Selection Register)*/
#define GPIO_IT_FRTSR 0x06U /*GPIO Interrupt at Rising and Falling Trigger*/

/*--------------------------- Output Type -------------------------*/
#define GPIO_OUT_PP 0x0U /*Output pullup/down*/
#define GPIO_OUT_OD 0x1U /*Output Open Drain*/

/*--------------------------- Output Speed -------------------------*/
/*
@note: output speed only works in ouput mode
*/
#define GPIO_OUT_LOW_SPEED 0x0U    // output at low speed
#define GPIO_OUT_MEDIUM_SPEED 0x1U // output at medium speed
#define GPIO_OUT_FAST_SPEED 0x2U   // output at fast speed
#define GPIO_OUT_HIGH_SPEED 0x3U   // output at high speed

/*--------------------------- pullup/pulldown -------------------------*/
/*
@note: pull up and pull down mostly used in input mode to give
a default value to the pin so that the pin doesn't go to
floating (random value) mode
*/
#define GPIO_NO_PUPD 0x0U
#define GPIO_PULLUP 0x01U
#define GPIO_PULLDOWN 0x02U

/********************************************GPIO Configs*****************************************/

typedef struct
{
    uint8_t pin;
    uint8_t mode;  // Define the mood of a particular gpio pin eg. input or output
    uint8_t otype; // output type pullup/down or open drain
    uint8_t pupd;  // pull-upp and pull-down
    uint8_t speed; // GPIO pin speed
} GPIO_Config_TypeDef;

/*These Are the utility Function*/
__STATIC_INLINE uint8_t __get_port_code(GPIO_TypeDef *GPIOx);
__STATTIC_VOID __syscfgr_init(GPIO_TypeDef *GPIOx, uint8_t pin);
__STATTIC_VOID __exti_init(uint8_t mode, uint8_t pin);

/*These function is used to manipulate the gpio pins*/
void gpio_clock_init(GPIO_TypeDef *GPIOx, uint8_t state);
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_Config_TypeDef config);
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state);
uint8_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint8_t pin);
void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint32_t delay);
void gpio_irq_handler(uint8_t pin);

#endif