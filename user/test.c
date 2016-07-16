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

void floodSearch(unsigned char targetX, unsigned char targetY) {
	moveForward(0.5, searchSpeed, searchSpeed);
	curPosY++;
	
	detectWalls();
	updateDistances(targetX, targetY);
	
	performNextMove();
	
}

void performNextMove() {
	
	unsigned char nextMove;
	int distN;
	int distE;
	int distS;
	int distW;
	
	// Get distances around current block
	distN = hasNorthWall(curPosX, curPosY)? MAX_DIST : distance[curPosX][curPosY+1];
	distE = hasEastWall(curPosX, curPosY)? MAX_DIST : distance[curPosX+1][curPosY];
	distS = hasSouthWall(curPosX, curPosY)? MAX_DIST : distance[curPosX][curPosY-1];
	distW = hasWestWall(curPosX, curPosY)? MAX_DIST : distance[curPosX-1][curPosY];
	
	// Decide next movement
	// 1. Pick the shortest route
	if ( (distN < distE) && (distN < distS) && (distN < distW) )
		nextMove = NORTH;
	else if ( (distE < distN) && (distE < distS) && (distE < distW) )
		nextMove = EAST;
	else if ( (distS < distE) && (distS < distN) && (distS < distW) )
		nextMove = SOUTH;
	else if ( (distW < distE) && (distW < distS) && (distW < distN) )
		nextMove = WEST;
	
	// 2. If multiple equally short routes, go straight if untraced
	else if ( !hasNorthWall(curPosX, curPosY) && !hasTrace(curPosX, curPosY+1) && orientation == NORTH)
		nextMove = NORTH;
	else if ( !hasEastWall(curPosX, curPosY) && !hasTrace(curPosX+1, curPosY) && orientation == EAST)
		nextMove = EAST;
	else if ( !hasSouthWall(curPosX, curPosY) && !hasTrace(curPosX, curPosY-1) && orientation == SOUTH)
		nextMove = SOUTH;
	else if ( !hasWestWall(curPosX, curPosY) && !hasTrace(curPosX-1,curPosY) && orientation == WEST)
		nextMove = WEST;
	 
	// 3. Else, choose untraced route prioritizing N > E > S > W
	else if ( !hasNorthWall(curPosX, curPosY) && !hasTrace(curPosX, curPosY+1) )
		nextMove = NORTH;
	else if ( !hasEastWall(curPosX, curPosY) && !hasTrace(curPosX+1, curPosY) )
		nextMove = EAST;
	else if ( !hasSouthWall(curPosX, curPosY) && !hasTrace(curPosX, curPosY-1) )
		nextMove = SOUTH;
	else if ( !hasWestWall(curPosX, curPosY) && !hasTrace(curPosX-1,curPosY) )
		nextMove = WEST;
	
	// 4. Else, go straight if possible
	else if ( orientation == NORTH && !hasNorthWall(curPosX, curPosY) )
		nextMove = NORTH;
	else if ( orientation == EAST && !hasEastWall(curPosX, curPosY) )
		nextMove = EAST;
	else if ( orientation == SOUTH && !hasSouthWall(curPosX, curPosY) )
		nextMove = SOUTH;
	else if ( orientation == WEST && !hasWestWall(curPosX, curPosY) )
		nextMove = WEST;
	
	// 5. Otherwise prioritize N > E > S > W
	else if (!hasNorthWall(curPosX, curPosY))
		nextMove = NORTH;
	else if (!hasEastWall(curPosX, curPosY))
		nextMove = EAST;
		else if (!hasSouthWall(curPosX, curPosY))
		nextMove = SOUTH;
	else if (!hasWestWall(curPosX, curPosY))
		nextMove = WEST;
}

void updateDistances(unsigned char targetX, unsigned char targetY) {
	for (int i = 0; i < SIZE*SIZE; i++) {
		for (int x = 0; x < SIZE; x++) {
			for (int y = 0; y < SIZE; y++) {
				if ( !((x == targetX) && (y == targetY)) ){
					distance[x][y] = getMinDistance(x, y) + 1;
				}
			}
		}
	}
}
