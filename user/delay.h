#ifndef DELAY_H
#define DELAY_H   


void delay_ms(u32 nTime);
void delay_us(u32 nTime);
u32 micros(void);
u32 millis(void);
void elapseMicros(u32 targetTime, u32 oldt);
void elapseMillis(u32 targetTime, u32 oldt);

extern volatile u32 Millis;
extern volatile u32 Micros;

#endif
