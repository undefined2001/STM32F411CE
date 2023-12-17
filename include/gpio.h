#include "stm32f411xe.h"

#ifndef GPIO_H
#define GPIO_H

/*-----------------GPIO Values-------------*/
#define DISABLE         0x0U
#define ENABLE          0x1U
#define LOW             0x0U
#define HIGH            0x1U
/*-----------------GPIO Values-------------*/


/********************************************GPIO Configs*****************************************/

/*----------------------------- Modes -------------------------*/
#define GPIO_INPUT     0x0U  /*GPIO input Mode*/
#define GPIO_OUTPUT    0x1U  /*GPIO output Mode*/
#define GPIO_ALF       0x2U  /*GPIO Alternate Function Mode*/
#define GPIO_ALG       0x3U  /*GPIO Analog Mode*/


/*--------------------------- Output Type -------------------------*/
#define GPIO_OUT_PP    0x0U   /*Output pullup/down*/
#define GPIO_OUT_OD    0x1U   /*Output Open Drain*/

/*--------------------------- Output Speed -------------------------*/
/*
@note: output speed only works in ouput mode
*/
#define GPIO_OUT_LOW_SPEED         0x0U   //output at low speed
#define GPIO_OUT_MEDIUM_SPEED      0x1U   //output at medium speed
#define GPIO_OUT_FAST_SPEED        0x2U   //output at fast speed
#define GPIO_OUT_HIGH_SPEED        0x3U   //output at high speed

/*--------------------------- pullup/pulldown -------------------------*/
/*
@note: pull up and pull down mostly used in input mode to give 
a default value to the pin so that the pin doesn't go to 
floating (random value) mode
*/
#define GPIO_NO_PUPD       0x0U
#define GPIO_PULLUP        0x01U
#define GPIO_PULLDOWN      0x02U

/********************************************GPIO Configs*****************************************/

typedef struct
{
    uint8_t pin;
    uint8_t mode;  // Define the mood of a particular gpio pin eg. input or output
    uint8_t otype; // output type pullup/down or open drain
    uint8_t pupd;  // pull-upp and pull-down
    uint8_t speed; // GPIO pin speed
} GPIO_Config_Typedef;





/*These function is used to manipulate the gpio pins*/
void gpio_clock_init(GPIO_TypeDef *GPIOx, uint8_t state);
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_Config_Typedef config);
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state);

#endif