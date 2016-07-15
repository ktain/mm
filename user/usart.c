#include "main.h"

#pragma import(__use_no_semihosting)  

struct __FILE { int handle;};
	FILE __stdout;
	FILE __stdin;
	void _sys_exit(int x)  
{  
	x = x;  
}   

int fputc(int ch, FILE *f) 
{ 
	USART_SendData(USART1, (u8)ch); 
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 	
  return ch; 
} 

int fgetc(FILE *f)
{
  u16 temp;
  while(!(USART1->SR & USART_SR_RXNE));
  temp = (u16)(USART1->DR & (u16)0x01FF);
  return temp;
}


