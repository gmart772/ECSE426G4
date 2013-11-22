#ifndef LDCMANAGER_H
#define LDCMANAGER_H

#include "stm32f4xx.h"

typedef enum {CLEAR_DISPLAY, RESET_CURSOR, INCREMENT_CHARACTER_MODE, DISPLAY_CURSOR_ON, DISPLAY_CURSOR_OFF} lcdCommands;
typedef enum {ON, OFF} gpioState;

void initializeLCD(void);
void executeCommand(lcdCommands commandToExecute);
void writeString(char* dataToWrite);

#endif
