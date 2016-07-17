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

extern int LDMidVal;
extern int RDMidVal;
extern int LFMidVal;
extern int RFMidVal;
extern int alignTime;
extern int alignScale;

void readVoltage(void);
void readIRSensors(void);
int getSensorError(void);
void readGyro(void);
void showVoltage(void);

#endif
