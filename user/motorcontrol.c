#include "main.h"

bool useMotorControl = 0;
bool useIRSensors = 0;
bool useOnlyGyroFeedback = 0;
bool useOnlyEncFeedback = 0;

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
float gyroFeedback = 0;
float errorX = 0;
float errorW = 0;
float oldErrorX = 0;
float oldErrorW = 0;
int posPwmX = 0;
int posPwmW = 0;

/* Speed settings */
int maxPwm = 999;
float stopSpeed = 0;
float searchSpeed = 0.6;	// m/s
float turnSpeed = 0.4;
float traceSpeed = 1.5;
float runSpeed = 2.0;

float maxAccX = 5;	// m/s/s
float maxDecX = 5;
float maxAccW = 25000;	// deg/s/s
float maxDecW = 25000;

/* Constant variables */
float counts_per_mm = 145.5;
float counts_per_deg = 55.8;	// higher == larger angle
int cellDistance = 26200;	// counts
int sensorScale = 200;	// sensor error divisor
float gyroScale = 3.7;

// Motor encoder PID
float kpX = 2;
float kdX = 4;
float kpW = 1;
float kdW = 20;


void setLeftPwm(int pwm) {
	if(pwm > maxPwm)
		pwm = maxPwm;
	if(pwm < -maxPwm)
		pwm = -maxPwm;
	
	
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
	if(pwm > maxPwm)
		pwm = maxPwm;
	if(pwm < -maxPwm)
		pwm = -maxPwm;	
	
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

	float rotationalFeedback;
	
	encFeedbackX = (rightEncChange + leftEncChange)/2;
	encFeedbackW = (rightEncChange - leftEncChange)/2;
	gyroFeedback = -aSpeed/gyroScale;
	
	if (useOnlyGyroFeedback)
		rotationalFeedback = gyroFeedback;
	else if (useOnlyEncFeedback)
		rotationalFeedback = encFeedbackW;
	else 
		rotationalFeedback = gyroFeedback + encFeedbackW;
	
	if (useIRSensors)
		rotationalFeedback -= getSensorError()/sensorScale;

	errorX += curSpeedX - encFeedbackX;
	errorW += curSpeedW - rotationalFeedback;
	
	posPwmX = (kpX * errorX + kdX * (errorX - oldErrorX));
	posPwmW = (kpW * errorW + kdW * (errorW - oldErrorW));
	
	oldErrorX = errorX;
	oldErrorW = errorW;
	

	
	setLeftPwm(posPwmX - posPwmW);
	setRightPwm(posPwmX + posPwmW);
}


// Get deceleration needed given distance left to travel, current speed, and final speed
float getDecNeeded(int d, float Vi, float Vf) {
	float decNeeded;
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
	useMotorControl = 1;
}

void disableMotorControl(void) {
	useMotorControl = 0;
	resetMotorParameters();
}

void resetMotorParameters(void) {
	
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
	gyroFeedback = 0;
	angle = 0;
	errorX = 0;
	errorW = 0;
	oldErrorX = 0;
	oldErrorW = 0;
	posPwmX = 0;
	posPwmW = 0;
	
	setLeftPwm(0);
	setRightPwm(0);
	
	resetLeftEncCount();
	resetRightEncCount();
}


/**
 *	Straight movement
 */
void moveForward(float cells, float maxSpeed, float endSpeed) {
	angle = 0;
	
	distanceLeft = cells*cellDistance;
	useIRSensors = 1;
	while( distanceLeft > 0 ) {
		if (distanceLeft < cellDistance/2 && endSpeed == stopSpeed)
			useIRSensors = 0;
		if (getDecNeeded(distanceLeft, curSpeedX, mm_to_counts(endSpeed)) < mm_to_counts(maxDecX)/1000) {
				targetSpeedX = mm_to_counts(maxSpeed);
		}
		else {
			targetSpeedX = mm_to_counts(endSpeed);
		}
	}
	targetSpeedX = mm_to_counts(endSpeed);
	useIRSensors = 0;
}

/**
 *	Angular movement
 *  +speedW turns left, -speedW turns right
 *	time is in ms, speedX is in m/s, speedW is in deg/s
 */
void turn(int t1, int t2, int t3, int radius, float speedX, float speedW, float accW, float decW) {
	float tempAccW = accW;
	float tempDecW = decW;
	float tempkpW = kpW;
	float tempkdW = kdW;

	moveForward(mm_to_counts(90 - radius)/cellDistance, speedX, speedX);
	
	maxAccW = accW;
	maxDecW = decW;
	
	useOnlyGyroFeedback = 1;
	angle = 0;
	int curt = millis();
	while ( (millis() - curt) <= (t1 + t2 + t3) ) {
		if ( (millis() - curt) <= t1 ) {
			kpW = 0.7;
			kdW = 10;
			targetSpeedW = deg_to_counts(speedW)/1000;
		}
		else if ( (millis() - curt) <= (t1 + t2) ) {
			kpW = 0.7;
			kdW = 10;
			targetSpeedW = deg_to_counts(speedW)/1000;
		}
		else {
			kpW = 0.7;
			kdW = 10;
			targetSpeedW = 0;
		}
	}
	
	// Crash detection
	if (speedW < 0 && angle < 3000)
		disableMotorControl();
	else if (speedW > 0 && angle > -3000)
		disableMotorControl();
		
	useOnlyGyroFeedback = 0;
	maxAccW = tempAccW;
	maxDecW = tempDecW;
	kpW = tempkpW;
	kdW = tempkdW;
	
	moveForward(mm_to_counts(90 - radius)/cellDistance, speedX, speedX);
}

void align(int duration){
	int tempPwm = maxPwm;
	maxPwm = alignPwm;
	disableMotorControl();
	int curt = millis();
	while (millis() - curt < duration) {
		setLeftPwm((LFMidVal - LFSensor)/alignScale);
		setRightPwm((RFMidVal - RFSensor)/alignScale);
	}
	maxPwm = tempPwm;
	enableMotorControl();
}

