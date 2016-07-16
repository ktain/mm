#ifndef TEST_H
#define TEST_H


void hugFrontWall(int LSensorVal, int RSensorVal);
void randomMovement(void);
void floodSearch(unsigned char targetX, unsigned char targetY);
void performNextMove(void);
void updateDistances(unsigned char xPos, unsigned char yPos);

#endif
