#include "main.h"

void button0(void) {
	beepn(1);
	delay_ms(500);
	
	initializeMaze();
	printMaze();

	curPosX = 0;
	curPosY = 0;
	orientation = NORTH;
	floodSearch(7, 7);
	
	printMaze();
	
	setLeftPwm(0);
	setRightPwm(0);
}


void button1(void) {
	beepn(1);
	delay_ms(500);
	
	speedRun(7, 7);
	
	setLeftPwm(0);
	setRightPwm(0);
}
