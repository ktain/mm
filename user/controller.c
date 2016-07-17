#include "main.h"

int leftWallThreshold = 110;	// when mouse is at half a cell distance
int rightWallThreshold = 110;
int frontWallThreshold = 20;


void curveLeft90(void) {
	turn(23, 170, 23, 80, 0.6, 450, 20000, 20000);
	//turn(35, 222, 35, 70, 0.4, 350, 10000, 10000);
	//turn(43, 487, 43, 60, 0.2, 170, 4000, 4000);
}

void curveRight90(void){
	turn(23, 170, 23, 80, 0.6, -450, 20000, 20000);
	//turn(35, 222, 35, 70, 0.4, -350, 10000, 10000);
	//turn(43, 485, 43, 60, 0.2, -170, 4000, 4000);
}

void pivotLeft90(void) {
	turn(43, 487, 43, 90, 0, 170, 4000, 4000);
}

void pivotRight90(void) {
	turn(43, 485, 43, 90, 0, -170, 4000, 4000);
}

void pivotLeft180(void) {
	turn(33, 1352, 33, 90, 0, 130, 4000, 4000);
}

void pivotRight180(void) {
	turn(33, 1352, 33, 90, 0, -130, 4000, 4000);
}

void moveN(void) {
	if (orientation == NORTH) {
		if (approachingWall())
			moveForward(1, searchSpeed, turnSpeed);
		moveForward(1, searchSpeed, searchSpeed);
	}
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
	if (orientation == EAST) {
		if (approachingWall())
			moveForward(1, searchSpeed, turnSpeed);
		else
			moveForward(1, searchSpeed, searchSpeed);
	}
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
	if (orientation == SOUTH) {
		if (approachingWall())
			moveForward(1, searchSpeed, turnSpeed);
		else 
			moveForward(1, searchSpeed, searchSpeed);
	}
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
	if (orientation == WEST) {
		if (approachingWall())
			moveForward(1, searchSpeed, turnSpeed);
		else
			moveForward(1, searchSpeed, searchSpeed);
	}
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
	bool hasFrontWall = (LFSensor > frontWallThreshold || RFSensor > frontWallThreshold)? 1: 0;
	bool hasLeftWall = (LDSensor > leftWallThreshold)? 1: 0;
	bool hasRightWall = (RDSensor > rightWallThreshold)? 1: 0;
	
	moveForward(0.5, searchSpeed, stopSpeed);
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


// Pivot the mouse north
void faceN(void) {
	
	
}


// Pivot the mouse east
void faceE(void) {
	
	
}


// Pivot the mouse south
void faceS(void) {
	
}


// Pivot the mouse west
void faceW(void) {
	
	
}

// Detect front wall
bool approachingWall (void) {
	if ( (LFSensor > 20) && (RFSensor > 20) )
		return 1;
	else
		return 0;
}
