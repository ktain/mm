#ifndef PWM_H
#define PWM_H   

extern bool useMotorControl;

extern int encCountLeft;
extern int encCountRight;
extern int encCount;
extern int oldEncCountLeft;
extern int oldEncCountRight;
extern int encChangeLeft;
extern int encChangeRight;
extern int encChange;
extern int distanceLeft;


extern float targetSpeedX; // speed in counts/ms
extern float targetSpeedW;

extern float curSpeedX;			
extern float curSpeedW;
extern float encFeedbackX;
extern float encFeedbackW;
extern float errorX;
extern float errorW;
extern float oldErrorX;
extern float oldErrorW;

extern float kpX;
extern float kdX;
extern float kpW;
extern float kdW;

extern float stopSpeed;
extern float searchSpeed;
extern float turnSpeed;

extern float maxAccX;
extern float maxDecX;
extern float maxAccW;
extern float maxDecW;


void updateSpeed(void);
float getDecNeeded(int d, float Vf, float Vi);
void setLeftPwm(int pwm);
void setRightPwm(int pwm);
void enableMotorControl(void);
void disableMotorControl(void);
void resetMotorParameters(void);

void moveForward(float cells, float maxSpeed, float endSpeed);
void turn(int t1, int t2, int t3, int radius, float speedX, float speedW, float accX, float accW);

float counts_to_mm(float counts);
float mm_to_counts(float speed);
float counts_to_deg(float counts);
float deg_to_counts(float deg);

#define MAX_PWM 900
#define LPWMA TIM4->CCR1
#define LPWMB TIM4->CCR2
#define RPWMA TIM4->CCR3
#define RPWMB TIM4->CCR4

#endif
