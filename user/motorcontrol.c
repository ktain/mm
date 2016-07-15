#include "main.h"

bool useMotors = 0;

int leftEncCount = 0;
int rightEncCount = 0;
int encCount = 0;
int oldLeftEncCount = 0;
int oldRightEncCount = 0;
int leftEncChange = 0;
int rightEncChange = 0;
int encChange = 0;			// actual speed in counts/ms
int distanceLeft = 0;


float targetSpeedX = 0; // speed in counts/ms
float targetSpeedW = 0;	// speed in counts/ms

float curSpeedX = 0;		
float curSpeedW = 0;
float encFeedbackX = 0;
float encFeedbackW = 0;
float errorX = 0;
float errorW = 0;
float oldErrorX = 0;
float oldErrorW = 0;
int posPwmX = 0;
int posPwmW = 0;

/* Constant variables */
float counts_per_mm = 140;
float counts_per_deg = 55;	// higher == larger angle
int cellDistance = 24576;	// counts
float stopSpeed = 0;
float searchSpeed = 0.7;	// m/s
float turnSpeed = 0.7;		// m/s

float kpX = 2;
float kdX = 4;
float kpW = 1;
float kdW = 5;

float maxAccX = 5;	// m/s/s
float maxDecX = 5;
float maxAccW = 4000;	// deg/s/s
float maxDecW = 4000;

void setLeftPwm(int pwm) {
	if(pwm > MAX_PWM)
		pwm = MAX_PWM;
	if(pwm < -MAX_PWM)
		pwm = -MAX_PWM;
	
	
	if(pwm >= 0) {
			LPWMA = pwm;
			LPWMB	= 0; 
	}          
	else	{        
			LPWMA = 0;
			LPWMB	= -pwm; 
	}
}

void setRightPwm(int pwm) {
	if(pwm > MAX_PWM)
		pwm = MAX_PWM;
	if(pwm < -MAX_PWM)
		pwm = -MAX_PWM;	
	
	//swap direction
	pwm = -pwm;

	if(pwm >= 0)	{
			RPWMA = pwm;
			RPWMB	= 0; 
	}          
	else	{    
			RPWMA = 0;
			RPWMB	= -pwm; 
	}
}

/* Update motor speed to match target speed */
void updateSpeed(void) {
	
	/* Get data from encoders and update distance left to travel*/
	leftEncCount = getLeftEncCount();
	rightEncCount = getRightEncCount();
	
	leftEncChange = leftEncCount - oldLeftEncCount;
	rightEncChange = rightEncCount - oldRightEncCount;
	encChange = (leftEncChange + rightEncChange)/2;
	
	oldLeftEncCount = leftEncCount;
	oldRightEncCount = rightEncCount;
	
	leftEncCount += leftEncChange;
	rightEncCount += rightEncChange;
	encCount = (leftEncCount + rightEncCount)/2;
	
	distanceLeft -= encChange;
	
	
	/* Update current	*/
	if (curSpeedX < targetSpeedX) {
		curSpeedX += mm_to_counts(maxAccX)/1000;
		if (curSpeedX > targetSpeedX)
			curSpeedX = targetSpeedX;
	}
	else if (curSpeedX > targetSpeedX) {
		curSpeedX -= mm_to_counts(maxDecX)/1000;
		if (curSpeedX < targetSpeedX)
			curSpeedX = targetSpeedX;
	}
	
	if (curSpeedW < targetSpeedW) {
		curSpeedW +=  deg_to_counts(maxAccW)/1000/1000;
		if (curSpeedW > targetSpeedW)
			curSpeedW = targetSpeedW;
	}
	else if (curSpeedW > targetSpeedW) {
		curSpeedW -= deg_to_counts(maxDecW)/1000/1000;
		if (curSpeedX < targetSpeedW)
			curSpeedW = targetSpeedW;
	}
	
	/* PD control */
	float encFeedbackX;
	float encFeedbackW;
	
	encFeedbackX = (rightEncChange + leftEncChange)/2;
	encFeedbackW = (rightEncChange - leftEncChange)/2;
	
	errorX += curSpeedX - encFeedbackX;
	errorW += curSpeedW - encFeedbackW;
	
	posPwmX = (kpX * errorX + kdX * (errorX - oldErrorX));
	posPwmW = (kpW * errorW + kdW * (errorW - oldErrorW));
	
	oldErrorX = errorX;
	oldErrorW = errorW;
	
	setLeftPwm(posPwmX - posPwmW);
	setRightPwm(posPwmX + posPwmW);
	
}


// Get deceleration needed given distance left to travel, final speed, and current speed
float getDecNeeded(int d, float Vf, float Vi) {
	int decNeeded;
	if (d <= 0) {
		d = 1;
	}
	decNeeded = (Vf*Vf - Vi*Vi)/d/2;
	return (decNeeded < 0)? -decNeeded: decNeeded;
}

// convert counts to mm
float counts_to_mm(float counts) {
	return (counts/counts_per_mm);
}


// convert mm to counts
float mm_to_counts(float mm) {
	return (mm*counts_per_mm);
}

// convert counts to deg
float counts_to_deg(float counts) {
	return (counts/counts_per_deg);
}

// convert deg to counts
float deg_to_counts(float deg) {
	return (deg*counts_per_deg);
}

void enableMotorControl(void) {
	resetMotorParameters();
	useMotors = 1;
}

void disableMotorControl(void) {
	useMotors = 0;
	resetMotorParameters();
}

void resetMotorParameters(void) {
	setLeftPwm(0);
	setRightPwm(0);
	
	leftEncCount = 0;
	rightEncCount = 0;
	encCount = 0;
	oldLeftEncCount = 0;
	oldRightEncCount = 0;
	leftEncChange = 0;
	rightEncChange = 0;
	encChange = 0;
	distanceLeft = 0;

	targetSpeedX = 0;
	targetSpeedW = 0;

	curSpeedX = 0;		
	curSpeedW = 0;
	encFeedbackX = 0;
	encFeedbackW = 0;
	errorX = 0;
	errorW = 0;
	oldErrorX = 0;
	oldErrorW = 0;
	posPwmX = 0;
	posPwmW = 0;
	
	resetLeftEncCount();
	resetRightEncCount();
}


/**
 *	Straight movement
 */
void moveForward(float cells) {
	if (cells < 0) {
		cells = 0;
	}
	
	int startEncCount = encCount;
	distanceLeft = cells*cellDistance;
	
	while( encCount - startEncCount < cells*cellDistance ) {
		if (getDecNeeded(distanceLeft, curSpeedX, 0) < mm_to_counts(maxDecX)) {
			targetSpeedX = mm_to_counts(searchSpeed);
		}
		else {
			targetSpeedX = stopSpeed;
		}
	}
	targetSpeedX = stopSpeed;
}

/**
 *	Angular movement
 */
void turn(float degrees) {
	
	int t0 = 0;
	int t1 = 33;
	int t2 = 659;
	int t3 = 33;
	int t4 = 0;
	int curt = millis();
	targetSpeedX = mm_to_counts(0.200);
	while ( (millis() - curt) <= (t1 + t2 + t3) ) {
		if ( (millis() - curt) <= (t1 + t2) )
			targetSpeedW = deg_to_counts(130)/1000;
		else
			targetSpeedW = 0;
	}
	targetSpeedX = 0;
	
}
