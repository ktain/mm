#include "main.h"


int32_t getRightEncCount(void) {
	return TIM5->CNT;
}

void resetRightEncCount(void) {
	TIM5->CNT = 0;
}

int32_t getLeftEncCount(void) {
	return TIM2->CNT;
}

void resetLeftEncCount(void) {
	TIM2->CNT = 0;
}

void setRightEncCount(int count) {
	TIM5->CNT = 0;
}

void setLeftEncCount(int count) {
	TIM2->CNT = 0;
}


