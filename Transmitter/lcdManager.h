#ifndef LDCMANAGER_H
#define LDCMANAGER_H

#include "stm32f4xx.h"

typedef enum {CLEAR_DISPLAY, RESET_CURSOR, INCREMENT_CHARACTER_MODE, DISPLAY_CURSOR_ON, DISPLAY_CURSOR_OFF, DEFAULT_CONFIGS, SET_CURSOR_SECOND_ROW} lcdCommands;
typedef enum {ON, OFF} gpioState;

void initializeLCD(void);
void resetLCDScreen(void);
void resetCursor(void);
void writeString(char* dataToWrite);

#endif
