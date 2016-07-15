#include "main.h"

int beepDuration; // in ms

// Non-blocking beep
void beep(int duration, int freq) {
	TIM3->CCR1 = (TIM3->ARR+1)/4;		// /8 == 12.5%, /4 == 25%, /2 == 50% loudness
	TIM3->ARR = 84000000/(freq)/140-1;
	beepDuration = duration;
}


// Multiple beep, blocking
void beepn(int count) {
	for (int i = 0; i < count; i++) {
		beep(70, 4000);
		if (i < count)
			delay_ms(140);
	}
}

void playVictory(void) {
	beep(100, 4000);
	delay_ms(150);
	beep(100, 4000);
	delay_ms(150);
	beep(100, 4000);
	delay_ms(150);
	beep(400, 4000);
	delay_ms(450);
	beep(400, 3200);
	delay_ms(450);
	beep(400, 3500);
	delay_ms(450);
	beep(100, 4000);
	delay_ms(250);
	beep(100, 3500);
	delay_ms(150);
	beep(600, 4000);
	delay_ms(600);
}

void playPrelude(void) {
	for(int j = 0; j < 2; j++) {
		for (int i = 0; i < 12; i++) {
			beep(100, 2000+300*i);
			delay_ms(150);
		}
		for (int i = 12; i > 0; i--) {
			beep(100, 2000+300*i);
			delay_ms(150);
		}
		for (int i = 0; i < 12; i++) {
			beep(100, 1000+300*i);
			delay_ms(150);
		}
		for (int i = 12; i > 0; i--) {
			beep(100, 1000+300*i);
			delay_ms(150);
		}
	}
}

 
