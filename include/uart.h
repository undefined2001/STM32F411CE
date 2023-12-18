#ifndef __UART_H_
#define __UART_H_

#include "gpio.h"

/**
 * TODO: need to implement UART Funcionality 
*/


#define USART1_CLK_EN()   (RCC->APB2ENR |= RCC_APB2ENR_USART1EN)
#define USART2_CLK_EN()   (RCC->APB1ENR |= RCC_APB1ENR_USART2EN)
#define USART6_CLK_EN()   (RCC->APB2ENR |= RCC_APB2ENR_USART6EN)

#define USART1_CLK_DI()   (RCC->APB2ENR &= ~(RCC_APB2ENR_USART1EN))
#define USART2_CLK_DI()   (RCC->APB1ENR &= ~(RCC_APB1ENR_USART2EN))
#define USART6_CLK_DI()   (RCC->APB2ENR &= ~(RCC_APB2ENR_USART6EN))





typedef struct
{
    uint8_t mode;
    uint8_t parity;
    uint8_t bit_length;    
    uint8_t stop_bits;
    uint32_t baudrate;
}UART_Config_TypeDef;


void uart_clock_init(USART_TypeDef *USARTx, uint8_t state);
void uart_init(USART_TypeDef *USARTx);
void uart_write_char();
uint32_t uart_read_char();


#endif