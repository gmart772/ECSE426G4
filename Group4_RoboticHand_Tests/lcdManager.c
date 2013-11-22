/**
 * @file lcdManager.c
 * @author Jean-Sebastien Dery, Matthew Johnston, Gregoire Martin, and Patrick White
 * @version 1.0
 * @date November 21th 2013
 * @brief Manages all the interactions with the LCD screen.
*/

#include <stdio.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx.h"
#include "lcdManager.h"
#include "cmsis_os.h"

/**
 * Initializes the LCD display.
*/
void initializeLCD(void) {
	
}

void executeCommand(lcdCommands commandToExecute) {
	switch(commandToExecute) {
		case CLEAR_DISPLAY:
		
		break;
		case RESET_CURSOR:
			
		break;
		case INCREMENT_CHARACTER_MODE:
			
		break;
	}
}

void writeString(char* dataToWrite) {
	
}