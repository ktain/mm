#include "main.h"

int leftWallThreshold = 200;
int rightWallThreshold = 200;
int frontWallThreshold = 100;


void turnLeft90(void) {
	turn(44, 470, 44, 70, 0.2, 175, 4000, 4000);
}

void turnRight90(void){
	turn(44, 470, 44, 70, 0.2, -175, 4000, 4000);
}

void turnLeft180(void) {
	turn(33, 1352, 33, 90, 0, 130, 4000, 4000);
}

void turnRight180(void) {
	turn(33, 1352, 33, 90, 0, -130, 4000, 4000);
}

void moveN(void) {
	if (orientation == NORTH)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == EAST)
		turnLeft90();
	else if (orientation == SOUTH)
		moveBack();
	else if (orientation == WEST)
		turnRight90();
	
	curPosY++;
	orientation = NORTH;
}

void moveE(void) {
	if (orientation == EAST)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == SOUTH)
		turnLeft90();
	else if (orientation == WEST)
		moveBack();
	else if (orientation == NORTH)
		turnRight90();
	
	curPosX++;
	orientation = EAST;
}

void moveS(void) {
	if (orientation == SOUTH)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == WEST)
		turnLeft90();
	else if (orientation == NORTH)
		moveBack();
	else if (orientation == EAST)
		turnRight90();
	
	curPosY--;
	orientation = SOUTH;
}

void moveW(void) {	
	if (orientation == WEST)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == NORTH)
		turnLeft90();
	else if (orientation == EAST)
		moveBack();
	else if (orientation == SOUTH)
		turnRight90();
	
	curPosX--;
	orientation = WEST;
}

void moveBack(void) {
	moveForward(0.5, searchSpeed, stopSpeed);
	delay_ms(100);
	turnLeft180();
	delay_ms(100);
	moveForward(0.5, searchSpeed, searchSpeed);
}

void detectWalls() {
	
	// Detect front wall
	if ( (LFSensor > frontWallThreshold) && (RFSensor > frontWallThreshold) ) {
		placeWall(curPosX, curPosY, orientation);
	}
		
	// Detect left wall
	if (LDSensor > leftWallThreshold) {
		if (orientation == NORTH)
			placeWall(curPosX, curPosY, WEST);
		else if (orientation == EAST)
			placeWall(curPosX, curPosY, NORTH);
		else if (orientation == SOUTH)
			placeWall(curPosX, curPosY, EAST);
		else if (orientation == WEST)
			placeWall(curPosX, curPosY, SOUTH);
	}
	
	// Detect right wall
	if (RDSensor > rightWallThreshold) {
		if (orientation == NORTH)
			placeWall(curPosX, curPosY, EAST);
		else if (orientation == EAST)
			placeWall(curPosX, curPosY, SOUTH);
		else if (orientation == SOUTH)
			placeWall(curPosX, curPosY, WEST);
		else if (orientation == WEST)
			placeWall(curPosX, curPosY, NORTH);
	}

}


