#include "main.h"

int leftWallThreshold = 200;	// when mouse is at half a cell distance
int rightWallThreshold = 200;
int frontWallThreshold = 80;

int approachThreshold = 50;


void curveLeft90(void) {
	turn(13, 167, 13, 60, 0.5, 500, 40000, 40000);
	//turn(9, 256, 9, 53, 0.3, 345, 40000, 40000);
}

void curveRight90(void) {
	turn(13, 167, 13, 60, 0.5, -500, 40000, 40000);
	//turn(9, 250, 9, 54, 0.3, -350, 40000, 40000);
}

void pivotLeft90(void) {
	turn(9, 248, 9, 90, 0, 350, 40000, 40000);
}

void pivotRight90(void) {
	turn(9, 248, 9, 90, 0, -350, 40000, 40000);
}

void pivotLeft180(void) {
	turn(35, 235, 35, 90, 0, 700, 20000, 20000);
}

void pivotRight180(void) {
	turn(35, 235, 35, 90, 0, -700, 20000, 20000);
}

void moveN(void) {
	if (orientation == NORTH)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == EAST)
		curveLeft90();
	else if (orientation == SOUTH)
		moveBack();
	else if (orientation == WEST)
		curveRight90();
	
	curPosY++;
	orientation = NORTH;
}

void moveE(void) {
	if (orientation == EAST)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == SOUTH)
		curveLeft90();
	else if (orientation == WEST)
		moveBack();
	else if (orientation == NORTH)
		curveRight90();
	
	curPosX++;
	orientation = EAST;
}

void moveS(void) {
	if (orientation == SOUTH)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == WEST)
		curveLeft90();
	else if (orientation == NORTH)
		moveBack();
	else if (orientation == EAST)
		curveRight90();
	
	curPosY--;
	orientation = SOUTH;
}

void moveW(void) {	
	if (orientation == WEST)
		moveForward(1, searchSpeed, searchSpeed);
	else if (orientation == NORTH)
		curveLeft90();
	else if (orientation == EAST)
		moveBack();
	else if (orientation == SOUTH)
		curveRight90();
	
	curPosX--;
	orientation = WEST;
}

void moveBack(void) {
	bool hasFrontWall = (LFSensor > frontWallThreshold && RFSensor > frontWallThreshold)? 1: 0;
	bool hasLeftWall = (LDSensor > leftWallThreshold)? 1: 0;
	bool hasRightWall = (RDSensor > rightWallThreshold)? 1: 0;
	
	moveForward(0.5, turnSpeed, stopSpeed);
	if (hasFrontWall) {
		align(alignTime);
	}
	if (hasLeftWall) {
		pivotLeft90();
		align(alignTime);
		pivotLeft90();
	}
	else if (hasRightWall) {
		pivotRight90();
		align(alignTime);
		pivotRight90();
	}
	else {
		pivotLeft180();
	}
	
	moveForward(0.5, turnSpeed, turnSpeed);
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


// Pivot the mouse north
void faceN(void) {
	if (orientation == EAST)
		pivotLeft90();
	else if (orientation == SOUTH)
		pivotLeft180();
	else if (orientation == WEST)
		pivotRight90();
	
	orientation = NORTH;
}


// Pivot the mouse east
void faceE(void) {
	if (orientation == NORTH)
		pivotRight90();
	else if (orientation == SOUTH)
		pivotLeft90();
	else if (orientation == WEST)
		pivotLeft180();
	
	orientation = EAST;
}


// Pivot the mouse south
void faceS(void) {
	if (orientation == NORTH)
		pivotLeft180();
	else if (orientation == EAST)
		pivotRight90();
	else if (orientation == WEST)
		pivotLeft90();
	
	orientation = SOUTH;
}


// Pivot the mouse west
void faceW(void) {
	if (orientation == NORTH)
		pivotLeft90();
	else if (orientation == EAST)
		pivotLeft180();
	else if (orientation == SOUTH)
		pivotRight90();
	
	orientation = WEST;
}

// Detect front wall
bool approachingWall (void) {
	if ( (LFSensor > approachThreshold) && (RFSensor > approachThreshold) )
		return 1;
	else
		return 0;
}
