#include "main.h"

/* Hug Front Wall */
void hugFrontWall(int LSensorVal, int RSensorVal) {
	while (1) {
		setLeftPwm(LSensorVal - LFSensor);
		setRightPwm(RSensorVal - RFSensor);
	}
}

/* Move at random */
void randomMovement(void) {
	moveForward(0.5, searchSpeed, turnSpeed);
	
	while(1) {
		if (LDSensor < leftWallThreshold)	// no left wall
			turnLeft90();
		else if (RDSensor < rightWallThreshold) // no right wall
			turnRight90();
		else if (LFSensor < frontWallThreshold || RFSensor < frontWallThreshold) // no front wall
			moveForward(1, searchSpeed, turnSpeed);
		else {	// deadend
			moveBack();
		}
	}
	
}

