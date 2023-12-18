#include "uart.h"

void uart_clock_init(USART_TypeDef *USARTx, uint8_t state)
{
    if (state == ENABLE)
    {
        if (USARTx == USART1)
        {
            USART1_CLK_EN();
        }
        else if (USARTx == USART2)
        {
            USART2_CLK_EN();
        }
        else if (USARTx == USART6)
        {
            USART6_CLK_EN();
        }
    }
    else if (state == DISABLE)
    {
        if (USARTx == USART1)
        {
            USART1_CLK_DI();
        }
        else if (USARTx == USART2)
        {
            USART2_CLK_DI();
        }
        else if (USARTx == USART6)
        {
            USART6_CLK_DI();
        }
    }
}

void uart_init(USART_TypeDef *USARTx)
{
}