#include "util.h"

void delay_ms(uint32_t delay) {
    SysTick->LOAD = 1600000U / 1000 - 1;  // Set the SysTick reload value for a 1ms interrupt
    SysTick->VAL = 0;  // Reset the SysTick counter value
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;  // Enable SysTick

    for (uint32_t i = 0; i < delay; ++i) {
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {}  // Wait until the COUNTFLAG is set
    }

    SysTick->CTRL = 0;  // Disable SysTick
}
