#include "main.h"

void button0(void) {
	beepn(1);
	delay_ms(500);
	
	//1W == .025rev/s == 9 deg/s
	enableMotorControl();
	turn(00);
	delay_ms(1000);
	disableMotorControl();
}


void button1(void) {
	beepn(1);
	delay_ms(500);
	
	enableMotorControl();
	targetSpeedX = mm_to_counts(0.04);
	delay_ms(2500);
	disableMotorControl();
}
