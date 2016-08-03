#include "main.h"

void button0(void) {
	beepn(1);
	delay_ms(2000);
	
	initializeMaze();
	//printMaze();

	curPosX = 0;
	curPosY = 0;
	orientation = NORTH;
	
		floodSearch(5, 5);
		floodSearch(0, 0);
	
	//printMaze();
	
	setLeftPwm(0);
	setRightPwm(0);
}


void button1(void) {
	beepn(1);
	delay_ms(1000);

	angle = 0;
	speedRun(5,5);
	speedRun(0,0);
	
	/*
	enableMotorControl();
	while (1){
		moveForward(1, 0.4, 0.4);
		curveLeft90();
	}
	disableMotorControl();
	*/

}
