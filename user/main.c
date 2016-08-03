#include "main.h"

void systick(void) {
	
	readVoltage();
	readIRSensors();
	readGyro();
	if (useMotorControl)
		updateSpeed();
}


int main(void) {
	setup();
	showVoltage();
	beepn(1);
	
	while(1) {
		printf("LF %4d LD %4d RD %4d RF %4d aSpeed %4d angle %7d voltage %4d lenc %7d renc %7d Outz = %4d Vref = %4d\r\n", LFSensor, LDSensor, RDSensor, RFSensor, aSpeed, angle, voltage, getLeftEncCount(), getRightEncCount(), read_Outz, read_Vref);
		
		delay_ms(100);
		
	}
}
