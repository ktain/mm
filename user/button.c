#include "main.h"

void button0(void) {
	beepn(1);
	delay_ms(500);
	
	initializeMaze();
	printMaze();
	
	enableMotorControl();
	
	curPosX = 0;
	curPosY = 0;
	orientation = NORTH;
	floodSearch(5, 5);
	
	disableMotorControl();
	printMaze();
	
	setLeftPwm(0);
	setRightPwm(0);
}


void button1(void) {
	beepn(1);
	delay_ms(500);
	align(670, 690, 1000);
	setLeftPwm(0);
	setRightPwm(0);
}
