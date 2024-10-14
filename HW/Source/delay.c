#include "delay.h"
void delay_init()
{
	systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);
}
void delay_us(uint16_t us)
{
	SysTick->LOAD = us * 72;
	SysTick->VAL  = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
		
}
void delay_ms(uint16_t ms)
{
	delay_us(ms*1000);
}