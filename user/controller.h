#ifndef CONTROLLER_H
#define CONTROLLER_H

void curveLeft90(void);
void curveRight90(void);
void pivotLeft90(void);
void pivotRight90(void);
void pivotLeft180(void);
void pivotRight180(void);
void moveN(void);
void moveE(void);
void moveS(void);
void moveW(void);
void moveBack(void);
void alignFrontWall(void);
void detectWalls(void);
void faceN(void);
void faceE(void);
void faceS(void);
void faceW(void);
bool approachingWall(void);

extern int leftWallThreshold;
extern int rightWallThreshold;
extern int frontWallThreshold;


#endif

