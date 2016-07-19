#include "main.h"

void button0(void) {
	beepn(1);
	delay_ms(2000);
	
	initializeMaze();
	//printMaze();

	curPosX = 0;
	curPosY = 0;
	orientation = NORTH;
	
	while(1) {
		floodSearch(5, 5);
		floodSearch(0, 0);
	}
	//printMaze();
	
	setLeftPwm(0);
	setRightPwm(0);
}


void button1(void) {
	beepn(1);
	delay_ms(500);

	//maxAccX = 1000;
	//maxDecX = 1000;
	enableMotorControl();
	curveLeft90();
	targetSpeedX = 0;
	delay_ms(500);
	disableMotorControl();
	
	setLeftPwm(0);
	setRightPwm(0);
	
}
