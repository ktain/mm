#ifndef SPEEDRUN_H
#define SPEEDRUN_H

extern unsigned char nextDir[100];
extern int length[100];

void speedRun(unsigned char targetX, unsigned char targetY);
void simulatePath(unsigned char targetX, unsigned char targetY);
unsigned char getNextDirection(void);
void closeUntracedCells(void);
	
#endif

