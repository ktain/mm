#include "main.h"


void SysTick_Handler(void)
{
	Millis++;
	
	systick();	
	
	beepDuration--;
	if(beepDuration < 0)
		beep_off;
}



void EXTI9_5_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) {
		delay_ms(20);
		if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
			EXTI_DeInit();
			button0();
			button_setup();
		}
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}


void EXTI15_10_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line12) != RESET) {
		delay_ms(20);
		if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
			EXTI_DeInit();
			button1();
			button_setup();
		}
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}


