#ifndef SENSOR
#define SENSOR

extern int voltage;
extern int LFSensor;
extern int RFSensor;
extern int LDSensor;
extern int RDSensor;
extern int Outz;
extern int aSpeed;
extern int angle;

void readVoltage(void);
void readIRSensors(void);
void readGyro(void);
void showVoltage(void);

#endif
