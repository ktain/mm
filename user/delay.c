#include <stm32f4xx.h>
#include "stm32f4xx.h"
#include "delay.h"


u32 micros(void)
{
	return (Millis*1000 + 1000 - SysTick->VAL/168);
}

u32 millis(void)
{
	return Millis;
}

void delay_ms(u32 nTime)
{
	u32 curTime = Millis;
	while((Millis - curTime) < nTime);
}

void delay_us(u32 nTime)
{
	u32 curTime = micros();
	while((micros() - curTime) < nTime);
}  
