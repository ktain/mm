#include "main.h"

// Flood search to target position
void floodSearch(unsigned char targetX, unsigned char targetY) {
	enableMotorControl();
	placeTrace(curPosX, curPosY);
	moveForward(0.5, searchSpeed, searchSpeed);
	if (orientation == NORTH)
		curPosY++;
	else if (orientation == EAST)
		curPosX++;
	else if (orientation == SOUTH)
		curPosY--;
	else if (orientation == WEST)
		curPosX--;
	
	placeTrace(curPosX, curPosY);
	
	while( !atTarget(targetX, targetY) ) {
		detectWalls();
		updateDistances(targetX, targetY);
		if (distance[curPosX][curPosY] >= MAX_DIST) {
			moveForward(0.5, searchSpeed, stopSpeed);
			delay_ms(100);
			disableMotorControl();
			playLost();
			return;
		}
		performNextMove();
		placeTrace(curPosX, curPosY);
		simulateStraight(targetX, targetY);
	}
	moveForward(0.5, searchSpeed, stopSpeed);
	if (orientation == NORTH)
		orientation = SOUTH;
	else if (orientation == EAST)
		orientation = WEST;
	else if (orientation == SOUTH)
		orientation = NORTH;
	else if (orientation == WEST)
		orientation = EAST;
	
	delay_ms(100);
	disableMotorControl();
	playVictory();
	enableMotorControl();
	turnLeft180();
	delay_ms(100);
	disableMotorControl();
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
	
	// 5. Else, prioritize N > E > S > W
	else if (!hasNorthWall(curPosX, curPosY))
		nextMove = NORTH;
	else if (!hasEastWall(curPosX, curPosY))
		nextMove = EAST;
	else if (!hasSouthWall(curPosX, curPosY))
		nextMove = SOUTH;
	else if (!hasWestWall(curPosX, curPosY))
		nextMove = WEST;
		
	
	// Perform next move
	if (nextMove == NORTH)
		moveN();
	else if (nextMove == EAST)
		moveE();
	else if (nextMove == SOUTH)
		moveS();
	else if (nextMove == WEST)
		moveW();
	
}

void updateDistances(unsigned char targetX, unsigned char targetY) {
	distance[targetX][targetY] = 0;
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


void simulateStraight(unsigned char targetX, unsigned char targetY) {
	unsigned char xPos = curPosX;
	unsigned char yPos = curPosY;
	unsigned char count = 0;
	
	if (orientation == NORTH) {
		while (!hasNorthWall(xPos, yPos) && hasTrace(xPos, yPos+1) && (distance[xPos][yPos+1] ==  distance[xPos][yPos] - 1)
			 && !(xPos == targetX && yPos == targetY) ) {
		count++;
		yPos++;
		}
	}
	
	else if (orientation == EAST) {
		while (!hasEastWall(xPos, yPos) && hasTrace(xPos+1, yPos) && (distance[xPos+1][yPos] == distance[xPos][yPos] - 1)
			 && !(xPos == targetX && yPos == targetY) ) {
		count++;
		xPos++;
		}
	}
	
	else if (orientation == SOUTH) {
		while (!hasSouthWall(xPos, yPos) && hasTrace(xPos, yPos-1) && (distance[xPos][yPos-1] == distance[xPos][yPos-1] - 1)
			 && !(xPos == targetX && yPos == targetY) ) {
			count++;
			yPos--;
		}
	}
	
	else if (orientation == WEST) {
		while(!hasWestWall(xPos, yPos) && hasTrace(xPos-1, yPos) && (distance[xPos-1][yPos] == distance[xPos][yPos] - 1 )
			 && !(xPos == targetX && yPos == targetY) ) {
			count++;
			xPos--;
		}
	}
	
	moveForward(count, traceSpeed, searchSpeed);
	curPosX = xPos;
	curPosY = yPos;
	
}

