#ifndef SETUP_H
#define SETUP_H


#define LED1_ON    GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define LED2_ON    GPIO_SetBits(GPIOA, GPIO_Pin_11)
#define LED3_ON    GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define LED4_ON    GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define LED5_ON    GPIO_SetBits(GPIOC, GPIO_Pin_8)
#define LED6_ON    GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define LED7_ON    GPIO_SetBits(GPIOC, GPIO_Pin_6)
#define LED8_ON    GPIO_SetBits(GPIOB, GPIO_Pin_15)
#define LED9_ON		 GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define LED10_ON	 GPIO_SetBits(GPIOB, GPIO_Pin_13)

#define LED1_OFF   GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define LED2_OFF   GPIO_ResetBits(GPIOA, GPIO_Pin_11)
#define LED3_OFF   GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define LED4_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define LED5_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_8)
#define LED6_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define LED7_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_6)
#define LED8_OFF   GPIO_ResetBits(GPIOB, GPIO_Pin_15)
#define LED9_OFF   GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define LED10_OFF  GPIO_ResetBits(GPIOB, GPIO_Pin_13)

#define FRONT_EM_ON   GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define FRONT_EM_OFF  GPIO_ResetBits(GPIOD, GPIO_Pin_2)
#define DIAG_EM_ON   GPIO_SetBits(GPIOC, GPIO_Pin_12)
#define DIAG_EM_OFF  GPIO_ResetBits(GPIOC, GPIO_Pin_12)

#define ALL_LED_ON		LED1_ON; LED2_ON; LED3_ON; LED4_ON; LED5_ON; LED6_ON; LED7_ON; LED8_ON; LED9_ON; LED10_ON
#define ALL_LED_OFF		LED1_OFF; LED2_OFF; LED3_OFF; LED4_OFF; LED5_OFF; LED6_OFF; LED7_OFF; LED8_OFF; LED9_OFF; LED10_OFF

#define read_Voltage     	 (readADC(ADC1, 15, ADC_SampleTime_84Cycles)*12840/4096)
#define read_LF_Sensor     readADC(ADC1, 10,  ADC_SampleTime_480Cycles)
#define read_LD_Sensor     readADC(ADC1, 11, ADC_SampleTime_480Cycles)
#define	read_RD_Sensor     readADC(ADC1, 12,  ADC_SampleTime_480Cycles)
#define read_RF_Sensor     readADC(ADC1, 13, ADC_SampleTime_480Cycles)
#define	read_Outz	       	 readADC(ADC1, 4,  ADC_SampleTime_84Cycles)
#define	read_Vref	         readADC(ADC1, 5,  ADC_SampleTime_84Cycles)

void setup(void);
void systick_setup(void);
void led_setup(void);
void button_setup(void);
void buzzer_setup(void);
void encoder_setup(void);
void usart_setup(u32 baudrate);
void sensor_setup(void);
void motor_setup(void);
u16 readADC(ADC_TypeDef* ADCx, u8 channel, uint8_t sampleTime);



void TIM4_GPIO_Config(void);
void TIM4_Mode_Config(void);
void TIM4_PWM_Init(void);


#endif
