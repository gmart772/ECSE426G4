#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "cmsis_os.h"
#include "threads.h"

#define NO_TIMEOUT 0
#define TIMEOUT_OCCURRED 1

#define ACCELEROMETER 0
#define PWM 1

//#define TIM4_PERIOD 665

extern short timerInterrupt;

void initTimer(void);
void initializeTimerPin(void);

void initTimer4(void);
void initTimer2(void);

void TIM3_IRQHandler(void);

void configureLEDS(int LED1, int LED2, int LED3, int LED4);
