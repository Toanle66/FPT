#include "delay.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void)
{
    msTicks++; // Tang bien dem moi khi ngat xay ra
}

/* Delay Systick */
void Delay_Systick(void) 
{
	SysTick->LOAD = (SystemCoreClock / 1000) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(uint32_t ms)
{
    msTicks = 0;
    
      while (msTicks < ms);
} 
