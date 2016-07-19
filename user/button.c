#include "main.h"

void button0(void) {
	beepn(1);
	delay_ms(500);
	
	initializeMaze();
	//printMaze();

	curPosX = 0;
	curPosY = 0;
	orientation = NORTH;
	
	floodSearch(5, 5);
	
	//printMaze();
	
	setLeftPwm(0);
	setRightPwm(0);
}


void button1(void) {
	beepn(1);
	delay_ms(500);
	
	/*
	sensorScale = 200;
	speedRun(5, 5);
	*/
	
	
	enableMotorControl();
	curveRight90();
	targetSpeedX = 0;
	delay_ms(100);
	disableMotorControl();
	
	setLeftPwm(0);
	setRightPwm(0);
	
}
