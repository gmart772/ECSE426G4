#ifndef KEYPADMANAGER_H
#define KEYPADMANAGER_H

#include "stm32f4xx.h"
#include "lcdManager.h"
#include "threads.h"

void initializeKeypad(void);
void scanManager(void);
void setUpColumn(void);
void scan(void);
void incrementColumn(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHanlder(void);
void EXTI3_IRQHandler(void);

#endif
