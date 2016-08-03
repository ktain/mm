#ifndef BUZZER_H
#define BUZZER_H


void beep(int duration, int freq);
void beepn(int count);
void playVictory(void);
void playPrelude(void);
void playLost(void);

extern int beepDuration;

#define beep_on   TIM3->CCR1 = (TIM3->ARR+1)/32 //set the duty cycle as of the loudness for each frequency. /8 is 12.5% loudness, /4 is 25%, however /1 buzzer is not 100% loudness, why?
#define beep_off  TIM3->CCR1 = 0               //set the duty cycle

#endif
