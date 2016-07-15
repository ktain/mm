#include "main.h"

/* Hug Front Wall */
void hugFrontWall(int LSensorVal, int RSensorVal) {
	while (1) {
		setLeftPwm(LSensorVal - LFSensor);
		setRightPwm(RSensorVal - RFSensor);
	}
}
