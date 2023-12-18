#include "nvic.h"

/********
@notes:
IRQ = Interrupt Request
ISER = Interrupt set enable register 
ICER = Interrupt Clear enable Register
IP = Interrupt Priority
*/



/************
@function: nvic_enable_irq
@params:
  - IRQn_Type IRQn
@result: enable the given interrupt request
************/
void nvic_enable_irq(IRQn_Type IRQn)
{
    NVIC->ISER[((int)IRQn / 32)] |= (1 << (IRQn % 32));
}


/************
@function: nvic_disable_irq
@params:
  - IRQn_Type IRQn
@result: disable the given interrupt request
************/
void nvic_disable_irq(IRQn_Type IRQn)
{
    NVIC->ICER[((int)IRQn >> 0x5U)] |= (0x1U << (IRQn & 0x1F));
}

/************
@function: nvic_set_priority
@params:
  - IRQn_Type IRQn
  - uint8_t priority
@result: set the priority of the corresponding interrupt request
************/
void nvic_set_priority(IRQn_Type IRQn, uint8_t priority)
{
    if (IRQn >= 0U)
    {
        NVIC->IP[((uint32_t)IRQn)] |= (uint8_t)(priority << (0x08 - __NVIC_PRIO_BITS));
    }
}

/*
TODO: implements the following function
*/
void nvic_get_priority(IRQn_Type IRQn);
