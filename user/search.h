#ifndef SEARCH_H
#define SEARCH_H

void floodSearch(unsigned char targetX, unsigned char targetY);
void performNextMove(void);
void updateDistances(unsigned char xPos, unsigned char yPos);
void simulateStraight(unsigned char targetX, unsigned char targetY);

#endif
