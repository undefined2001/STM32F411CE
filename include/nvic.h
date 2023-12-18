
#ifndef NVIC_H
#define NVIC_H

#include "stm32f411xe.h"

void nvic_enable_irq(IRQn_Type IRQn);
void nvic_disable_irq(IRQn_Type IRQn);
void nvic_set_priority(IRQn_Type IRQn, uint8_t priority);
void nvic_get_priority(IRQn_Type IRQn);


#endif