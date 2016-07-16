#include "main.h"

unsigned char cell[SIZE][SIZE];	// cell[x][y]
int distance[SIZE][SIZE];	// distance of cell[x][y]
unsigned char curPosX = 0;	 // 0 bottom left, horizontal
unsigned char curPosY = 0;  // 0 bottom left, vertical
unsigned char orientation = NORTH;

// Place known wall information
void initializeMaze(void) {

	placeWall(0, 0, EAST);	// east wall at starting cell
	
	// Place outer walls
	for (int i = 0; i < SIZE; i++) {
		placeWall(i, SIZE-1, NORTH);	// north wall
		placeWall(SIZE-1, i, EAST);		// east wall
		placeWall(i, 0, SOUTH);				// south wall
		placeWall(0, i, WEST);				// west wall
	}
	
}

// Place a wall, direction can be bitwise or'ed
void placeWall(unsigned char x, unsigned char y, unsigned char direction) {
	cell[x][y] |= direction;
	if ( (x > 0) && (direction == WEST) )
		cell[x-1][y] |= EAST;
	if ( (x < SIZE-1) && (direction == EAST) )
		cell[x+1][y] |= WEST;
	if ( (y > 0) && (direction == SOUTH) )
		cell[x][y-1] |= NORTH;
	if ( (y < SIZE - 1) && (direction == NORTH) )
		cell[x][y+1] |= SOUTH;
}

// Place a trace
void placeTrace(unsigned char x, unsigned char y) {
	cell[x][y] |= TRACEBIT;
}

// Check for trace
bool hasTrace(unsigned char x, unsigned char y) {
	return (cell[x][y] & TRACEBIT);
}

// Check for north wall
bool hasNorthWall(unsigned char x, unsigned char y) {
	return (cell[x][y] & NORTH);
}

// Check for east wall
bool hasEastWall(unsigned char x, unsigned char y) {
	return (cell[x][y] & EAST);
}

// Check for south wall
bool hasSouthWall(unsigned char x, unsigned char y) {
	return (cell[x][y] & SOUTH);
}

// Check for west wall
bool hasWestWall(unsigned char x, unsigned char y) {
	return (cell[x][y] & WEST);
}

// Check if current position is at target
bool atTarget(unsigned char targetX, unsigned char targetY) {
	if (curPosX == targetX && curPosY == targetY)
		return 1;
	else
		return 0;
}

// Get smallest distance of surrounding cells
int getMinDistance(unsigned char xPos, unsigned char yPos) {
   int min;
   int distN;
   int distE;
   int distS;
   int distW;
   
   distN = hasNorthWall(xPos, yPos)? MAX_DIST : distance[xPos][yPos+1];
   distE = hasEastWall(xPos, yPos)? MAX_DIST : distance[xPos+1][yPos];
   distS = hasSouthWall(xPos, yPos)? MAX_DIST : distance[xPos][yPos-1];
   distW = hasWestWall(xPos, yPos)? MAX_DIST : distance[xPos-1][yPos];
   
   min = distN;
   min = (distE < min)? distE : min;
   min = (distS < min)? distS : min;
   min = (distW < min)? distW : min;
   
   return min;
}

