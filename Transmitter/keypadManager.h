#ifndef KEYPADMANAGER_H
#define KEYPADMANAGER_H

#include "stm32f4xx.h"

void initializeKeypad(void);
void scanManager(void);
void setUpColumn(void);
void scanRow(void);
void incrementRow(void);
void incrementColumn(void);
void EXTI0_IRQHandler(void);

#endif
