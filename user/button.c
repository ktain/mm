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
	
	enableMotorControl();
	moveForward(4.5, 1, 0.4);
	turn(14, 320, 170, 90, 0.4, -400, 25000, 25000);
	moveForward(7*1.414/2, 1, 0.4);
	moveForward(.07, 1, 0.4);
	turn(14, 320, 14, 90, 0.4, 400, 25000, 25000);
	moveForward(3.5, 1, 0.4);
	disableMotorControl();
	delay_ms(300);
	setLeftPwm(0);
	setRightPwm(0);
	
	//speedRun(5,5);
	//speedRun(0,0);
	
	/*
	enableMotorControl();
	while (1){
		moveForward(1, 0.4, 0.4);
		curveLeft90();
	}
	disableMotorControl();
	*/

}
