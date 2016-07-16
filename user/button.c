#include "main.h"

void button0(void) {
	beepn(1);
	delay_ms(500);
	
	initializeMaze();
	printMaze();
	
	enableMotorControl();
	
	moveForward(0.5, searchSpeed, searchSpeed);
	curPosY++;
	moveE();
	updateDistances((SIZE+1)/2 - 1, (SIZE+1)/2 - 1);
	
	disableMotorControl();
	printMaze();
	
	setLeftPwm(0);
	setRightPwm(0);
}


void button1(void) {
	beepn(1);
	delay_ms(500);
	
	enableMotorControl();
	randomMovement();
	disableMotorControl();
	setLeftPwm(0);
	setRightPwm(0);
}
