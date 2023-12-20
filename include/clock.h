#ifndef _CLOCK_H_
#define _CLOCK_H_
#include "stm32f411xe.h"
#define __STATIC static
#define __STATIC_VOID static void

#define ON    1
#define OFF   0


/*
1000: system clock divided by 2
1001: system clock divided by 4
1010: system clock divided by 8
1011: system clock divided by 16
1100: system clock divided by 64
1101: system clock divided by 128
1110: system clock divided by 256
1111: system clock divided by 512
*/

/*AHB(Advance High-Performance Bus) Prescaler*/
#define AHB_DIV_1        0x0U
#define AHB_DIV_2        0x8U
#define AHB_DIV_4        0x9U
#define AHB_DIV_8        0xAU
#define AHB_DIV_16       0xBU
#define AHB_DIV_64       0xCU
#define AHB_DIV_128      0xDU
#define AHB_DIV_256      0xEU
#define AHB_DIV_512      0xFU
/*END of AHB Prescaler*/

/*APB Prescalers for both (APB1 and APB2)*/
#define APB_DIV_0   0x0U
#define APB_DIV_2   0x4U
#define APB_DIV_4   0x5U
#define APB_DIV_8   0x6U
#define APB_DIV_16  0x7U
/*APB Prescalers*/


#define CLOCK_SOURCE_HSI_ON() (RCC->CR |=  RCC_CR_HSION)  /*Activating the High Speed Internal Clock(HSI)*/
#define CLOCK_SOURCE_HSI_OFF() (RCC->CR &= ~RCC_CR_HSION) /*Deactivating the High Speed Internal Clock(HSI)*/

#define CLOCK_SOURCE_HSE_ON() (RCC->CR |= RCC_CR_HSEON)  /*Activating the High Speed Internal Clock(HSI)*/
#define CLOCK_SOURCE_HSE_OFF() (RCC->CR &= ~RCC_CR_HSEON) /*Deactivating the High Speed Internal Clock(HSI)*/

typedef enum
{
    CLOCK_HSI = 0x0U,
    CLOCK_HSE = 0x1U,
    CLOCK_PLL = 0x2U
} Clock;

void set_clock_source(Clock clk_src, uint8_t state);
void pll_enable(void);
void set_pll_source(Clock clk_src);
void set_system_clock(Clock clk);

#endif