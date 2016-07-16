#ifndef CONTROLLER_H
#define CONTROLLER_H

void turnLeft90(void);
void turnRight90(void);
void turnLeft180(void);
void turnRight180(void);
void moveN(void);
void moveE(void);
void moveS(void);
void moveW(void);
void moveBack(void);
void alignFrontWall(void);
void detectWalls(void);

extern int leftWallThreshold;
extern int rightWallThreshold;
extern int frontWallThreshold;


#endif

