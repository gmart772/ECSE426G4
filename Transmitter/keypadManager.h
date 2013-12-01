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
char getButtonPressed(void);
void doKeypadControl(void);

#endif
