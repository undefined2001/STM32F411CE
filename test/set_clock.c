void maximum_clk_speed()
{
    //Turning HSE On
    RCC->CR &= ~RCC_CR_HSEBYP;
    RCC->CR |= RCC_CR_HSEON;
    
    //Cheking if HSE is Ready
    while(RCC->CR & RCC_CR_HSERDY);
    
    //Enabling Prefetch instrction from flash
    FLASH->ACR |= FLASH_ACR_PRFTEN;
    
    //Setting the Flash Latency
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2WS;

    //Clearing the ahb1 prescaler not divided
    RCC->CFGR &= ~RCC_CFGR_HPRE;

    //Setting apb1 prescaler value to div 2
    /*100: AHB clock divided by 2*/
    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR |= RCC_CFGR_PPRE1_2;

    //setting apb2 prescaler to not divided
    RCC->CFGR &= ~RCC_CFGR_PPRE2;

    //Setting PLL Source
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;

    //Setting PLLM value to 16
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
    RCC->PLLCFGR |= (16U << 0U);

    //Setting PLLN to 128
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR |= (128U << 6U);

    //Setting PLLP to 2
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
    RCC->PLLCFGR |= (2U << 16U);

    //Turning PLL on
    RCC->CR |= RCC_CR_PLLON;

    //Waiting untill the pll is ready
    while(RCC->CR & RCC_CR_PLLRDY);

    //Setting pll as system clock
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= (2U << 0U);

    //Waiting untill pll is used as system clock
    while((RCC->CFGR & RCC_CFGR_SWS) == 8);

}