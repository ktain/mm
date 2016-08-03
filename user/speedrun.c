#include "main.h"

unsigned char nextDir[100] = {0};
int length[100] = {0};

void speedRun(unsigned char targetX, unsigned char targetY){
	simulatePath(targetX, targetY);
	enableMotorControl();
	
	for (int i = 0; length[i] != 0; i++) {
		// First straight
		if (i == 0) {
			moveForward(length[i] - 0.5, runSpeed, turnSpeed);
		}
		// Last straight
		else if (length[i+1] == 0) {
			moveForward(length[i] - 0.5, runSpeed, stopSpeed);
			if (orientation == NORTH)
				curPosY++;
			else if (orientation == EAST)
				curPosX++;
			else if (orientation == SOUTH)
				curPosY--;
			else if (orientation == WEST)
				curPosX--;
		}
		// Intermediate straight
		else {
			moveForward(length[i] - 1, runSpeed, turnSpeed);
		}
		
		if (orientation == NORTH)
			curPosY += length[i] - 1;
		else if (orientation == EAST)
			curPosX += length[i] - 1;
		else if (orientation == SOUTH)
			curPosY -= length[i] - 1;
		else if (orientation == WEST)
			curPosX -= length[i] - 1;
		
		if (length[i+1] == 0)
			break;
		
		// Curve turn
		if (nextDir[i] == NORTH)
			moveN();
		else if (nextDir[i] == EAST)
			moveE();
		else if (nextDir[i] == SOUTH)
			moveS();
		else if (nextDir[i] == WEST)
			moveW();
	}
	
	delay_ms(200);
	disableMotorControl();
	
	if (orientation == NORTH)
		orientation = SOUTH;
	else if (orientation == EAST)
		orientation = WEST;
	else if (orientation == SOUTH)
		orientation = NORTH;
	else if (orientation == WEST)
		orientation = EAST;
	
	if (LFSensor > frontWallThreshold && RFSensor > frontWallThreshold)
		align(alignTime);
	
	enableMotorControl();
	pivotLeft90();
	delay_ms(100);
	disableMotorControl();
	
	if (LFSensor > frontWallThreshold && RFSensor > frontWallThreshold)
		align(alignTime);
	
	enableMotorControl();
	pivotLeft90();
	delay_ms(100);
	disableMotorControl();
	
}


void simulatePath(unsigned char targetX, unsigned char targetY) {
	int count = 0;
	
	// Store current position and orientation
	int tempPosX = curPosX;
	int tempPosY = curPosY;
	int tempOrientation = orientation;
	
	// Block off untraced routes
	closeUntracedCells();
	updateDistances(targetX, targetY);
	
	int i;
	for (i = 0; !atTarget(targetX, targetY); i++) {
		if (orientation == NORTH) {
			while (!hasNorthWall(curPosX, curPosY) && (distance[curPosX][curPosY+1] == distance[curPosX][curPosY] - 1) && hasTrace(curPosX, curPosY+1)) {
				curPosY++;
				count++;
			}
		}
		else if (orientation == EAST) {
			while (!hasEastWall(curPosX, curPosY) && (distance[curPosX+1][curPosY] == distance[curPosX][curPosY] - 1) && hasTrace(curPosX+1, curPosY)) {
				curPosX++;
				count++;
			}
		}
		else if (orientation == SOUTH) {
			while (!hasSouthWall(curPosX, curPosY) && (distance[curPosX][curPosY-1] == distance[curPosX][curPosY] - 1) && hasTrace(curPosX, curPosY-1)) {
				curPosY--;
				count++;
			}
		}
		else if (orientation == WEST) {
			while (!hasWestWall(curPosX, curPosY) && (distance[curPosX-1][curPosY] == distance[curPosX][curPosY] - 1) && hasTrace(curPosX-1, curPosY)) {
				curPosX--;
				count++;
			}
		}
		//Error check
		if (count == 0) {
			playLost();
			while(1);
		}
		length[i] = count;
		nextDir[i] = getNextDirection();
		count = 0;
	}
	
	// Encode stopping condition
	length[i] = 0;
	nextDir[i] = 0;
	
	// Restore original position and orientation
	curPosX = tempPosX;
	curPosY = tempPosY;
	orientation = tempOrientation;
}

// Returns next direction to move in
unsigned char getNextDirection(void) {
	int curDist = distance[curPosX][curPosY];
	unsigned char nextDir;
	int distN = MAX_DIST;
	int distE = MAX_DIST;
	int distS = MAX_DIST;
	int distW = MAX_DIST;
	
	if (curPosY < SIZE-1)
		distN = distance[curPosX][curPosY+1];
	if (curPosX < SIZE-1)
		distE = distance[curPosX+1][curPosY];
	if (curPosY > 0) 
		distS = distance[curPosX][curPosY-1];
	if (curPosX > 0)
		distW = distance[curPosX-1][curPosY];
	
	if (!hasNorthWall(curPosX, curPosY) && (distN == curDist-1)) {
		nextDir = NORTH;
		orientation = NORTH;
	}
	else if (!hasEastWall(curPosX, curPosY) && (distE == curDist-1)) {
		nextDir = EAST;
		orientation = EAST;
	}
	else if (!hasSouthWall(curPosX, curPosY) && (distS == curDist-1)) {
		nextDir = SOUTH;
		orientation = SOUTH;
	}
	else if (!hasWestWall(curPosX, curPosY) && (distW == curDist-1)) {
		nextDir = WEST;
		orientation = WEST;
	}
	
	return nextDir;
}

void closeUntracedCells(void) {
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			if (!hasTrace(x, y)) {
				placeWall(x, y, NORTH);
				placeWall(x, y, EAST);
				placeWall(x, y, SOUTH);
				placeWall(x, y, WEST);
			}
		}
	}
}

