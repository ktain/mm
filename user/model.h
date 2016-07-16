#ifndef MODEL_H
#define MODEL_H

#define SIZE 16      // size of maze
#define MAX_DIST 252  // max distance for flood search

#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8
#define TRACEBIT 16

extern unsigned char cell[SIZE][SIZE];	// cell[x][y]
extern int distance[SIZE][SIZE];	// distance of cell[x][y]
extern unsigned char curPosX;	 // 0 bottom left, horizontal
extern unsigned char curPosY;  // 0 bottom left, vertical
extern unsigned char orientation;

void initializeMaze(void);
void placeWall(unsigned char x, unsigned char y, unsigned char direction);
void placeTrace(unsigned char x, unsigned char y);
	
bool hasTrace(unsigned char x, unsigned char y);
bool hasNorthWall(unsigned char x, unsigned char y);
bool hasEastWall(unsigned char x, unsigned char y);
bool hasSouthWall(unsigned char x, unsigned char y);
bool hasWestWall(unsigned char x, unsigned char y);

bool atTarget(unsigned char targetX, unsigned char targetY);
int getMinDistance(unsigned char xPos, unsigned char yPos);

#endif

