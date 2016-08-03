#include "main.h"

/* Sensor constants */
int LDMidVal = 400; // 60-1800
int RDMidVal = 400;	// 80-1600
int LFMidVal = 1140;
int RFMidVal = 1240;
int alignTime = 300;
int alignPwm = 150;
float alignScale = 1;

/* Sensor values updated every ms */
int voltage = 0;
int LFSensor = 0;
int RFSensor = 0;
int LDSensor = 0;
int RDSensor = 0;
int Outz = 0;
int aSpeed = 0;
int angle = 0; 


/* Read IR Sensors */
void readIRSensors(void)
{
	
	//Read DC value		
	LFSensor = read_LF_Sensor;	
	RFSensor = read_RF_Sensor;	
	LDSensor = read_LD_Sensor;
	RDSensor = read_RD_Sensor;	
	
	//Read front sensors
	FRONT_EM_ON;
	delay_us(30);
	LFSensor = read_LF_Sensor - LFSensor;
	RFSensor = read_RF_Sensor - RFSensor;
	FRONT_EM_OFF;
	if(LFSensor < 0) //error check
		LFSensor = 0;
	if(RFSensor < 0)
		RFSensor = 0;
 	delay_us(30);
	
	//Read diagonal sensors
	DIAG_EM_ON;
	delay_us(30);
	LDSensor = read_LD_Sensor - LDSensor;
	RDSensor = read_RD_Sensor - RDSensor;
  DIAG_EM_OFF;
	if(LDSensor < 0)
		LDSensor = 0;
	if(RDSensor < 0)
		RDSensor = 0;
	delay_us(30);
}

// Returns sensor error 
int getSensorError(void) {
	int sensorError = 0;

	if (LDSensor > LDMidVal)
		sensorError = LDMidVal - LDSensor;
	else if (RDSensor > RDMidVal)
		sensorError = RDSensor - RDMidVal;
	
	return sensorError;
}

/* Read gyro */
void readGyro(void)
{	                      //k=19791(sum for sample in 1 second)    101376287 for 50 seconds with 5000 samples
	int i;
	int sampleNum = 20;
	aSpeed = 0;
	for(i = 0; i < sampleNum; i++)
		aSpeed += read_Outz;
	
  aSpeed *= 50000/sampleNum;
	aSpeed -= 96350000;	// Outz * 50000, if angle goes up, increase
	aSpeed /= 50000;
	aSpeed /= 4;
	angle += aSpeed; 
}

/* Read voltage */
void readVoltage(void) {
	voltage = read_Voltage;
	if (voltage < 7000)
		beep(1000, 4000);
}

/* 
 * Show voltage using LED10 to LED1
 * Range is from 7V to 8V 
 */
void showVoltage(void){
	readVoltage();
	LED10_ON;
	if (voltage > 7200)
		LED9_ON;
	if (voltage > 7300)
		LED8_ON;
	if (voltage > 7400)
		LED7_ON;
	if (voltage > 7500)
		LED6_ON;
	if (voltage > 7600)
		LED5_ON;
	if (voltage > 7700)
		LED4_ON;
	if (voltage > 7800)
		LED3_ON;
	if (voltage > 7900)
		LED2_ON;
	if (voltage > 8000)
		LED1_ON;
	
	delay_ms(2000);
	ALL_LED_OFF;
}

