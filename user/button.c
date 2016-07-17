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
	enableMotorControl();
	printf("LENC %d|RENC %d\r\n", getLeftEncCount(), getRightEncCount());
	maxAccX = 1;
	maxDecX = 1;
	moveForward(10, 2.0, stopSpeed);
	printf("LENC %d|RENC %d\r\n", getLeftEncCount(), getRightEncCount());
	disableMotorControl();
	setLeftPwm(0);
	setRightPwm(0);
}
