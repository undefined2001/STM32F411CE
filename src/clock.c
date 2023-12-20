#include "clock.h"

/*Prescaler's Utility Fucntion*/
__STATIC_VOID __set_ahb1_prescaler(uint32_t prescaler_value)
{
    /*Clearing the all 4 bit for the AHB1 Prescaler*/
    RCC->CFGR &= ~(0xF << RCC_CFGR_HPRE_Pos);

    /*Configuring the ahb1 prescaler*/
    RCC->CFGR |= (prescaler_value << RCC_CFGR_HPRE_Pos);
}


__STATIC_VOID __set_apb1_prescaler(uint32_t prescaler_value)
{
    /*Clearing the all 4 bit for the APB1 Prescaler*/
    RCC->CFGR &= ~(0x7 << RCC_CFGR_PPRE1_Pos);

    /*Configuring the APB1 prescaler*/
    RCC->CFGR |= (prescaler_value << RCC_CFGR_PPRE1_Pos);
}

__STATIC_VOID __set_apb2_prescaler(uint32_t prescaler_value)
{
    /*Clearing the all 4 bit for the APB1 Prescaler*/
    RCC->CFGR &= ~(0x7 << RCC_CFGR_PPRE2_Pos);

    /*Configuring the APB1 prescaler*/
    RCC->CFGR |= (prescaler_value << RCC_CFGR_PPRE2_Pos);
}


/*Prescaler's Utility Fucntion*/

__STATIC_VOID __clk_ready(Clock clk_src)
{
    if (clk_src == CLOCK_HSI)
    {
        while (!(RCC->CR & RCC_CR_HSIRDY))
            ;
    }
    else if (clk_src == CLOCK_HSE)
    {
        while (!(RCC->CR & RCC_CR_HSERDY))
            ;
    }
}

void set_clock_source(Clock clk_src, uint8_t state)
{
    if (state == ON)
    {
        if (clk_src == CLOCK_HSE)
        {
            CLOCK_SOURCE_HSE_ON();
        }
        else if (clk_src == CLOCK_HSI)
        {
            CLOCK_SOURCE_HSI_ON();
        }
        __clk_ready(clk_src);
    }
    else if (state == OFF)
    {
        if (clk_src == CLOCK_HSE)
        {
            CLOCK_SOURCE_HSE_OFF();
        }
        else if (clk_src == CLOCK_HSI)
        {
            CLOCK_SOURCE_HSI_OFF();
        }
    }
}

void set_pll_source(Clock clk_src)
{
    RCC->PLLCFGR |= (clk_src << RCC_PLLCFGR_PLLSRC_Pos);
}

void set_system_clock(Clock clk)
{
    /*Clearing the bits sw(System Clock Switch) register*/
    RCC->CFGR &= ~((1 << RCC_CFGR_SW_Pos) | (1 << (RCC_CFGR_SW_Pos + 1)));
    /*Configuring the bits sw(System Clock Switch) register*/
    RCC->CFGR |= (clk << RCC_CFGR_SW_Pos);
}