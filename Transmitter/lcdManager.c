/**
 * @file lcdManager.c
 * @author Jean-Sebastien Dery, Matthew Johnston, Gregoire Martin, and Patrick White
 * @version 1.0
 * @date November 21th 2013
 * @brief Manages all the interactions with the LCD screen.
*/

// Table representing the mapping from the GPIO pins on the board and the pin
// number on the LCD display:
// +------------------+----------+-------------------+
// |       Name       | GPIO Pin | Pin number on LCD |
// +------------------+----------+-------------------+
// |       Data0      |   PE0    |         7         |
// |       Data1      |   PE1    |         8         |
// |       Data2      |   PE2    |         9         |
// |       Data3      |   PE3    |        10         |
// |       Data4      |   PE4    |        11         |
// |       Data5      |   PE5    |        12         |
// |       Data6      |   PE6    |        13         |
// |       Data7      |   PE7    |        14         |
// | Register Select  |   PD0    |         4         |
// |    Read/Write    |   PD1    |         5         |
// |      Enable      |   PD2    |         6         |
// |       Vcc        |  ground  |         1         |
// |       Vdd        |   +5v    |         2         |
// |       Vee        |  ground  |         3         |
// +------------------+----------+-------------------+

#include <stdio.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx.h"
#include "lcdManager.h"
#include "cmsis_os.h"

const uint8_t COMMAND_DELAY = 1;
const uint8_t MAX_CHARACTERS_ON_SINGLE_ROW = 24;
uint8_t internalCursor = 0;

void initializeDataGPIO(void);
void initializeControlGPIO(void);
void setCommandOnDataLine(lcdCommands commandToExecute);
void sendCommand(void);
void setData0(gpioState state);
void setData1(gpioState state);
void setData2(gpioState state);
void setData3(gpioState state);
void setData4(gpioState state);
void setData5(gpioState state);
void setData6(gpioState state);
void setData7(gpioState state);
void setRegisterSelect(gpioState state);
void setReadWrite(gpioState state);
void setEnable(gpioState state);

/**
 * Initializes the LCD display.
*/
void initializeLCD(void) {
	printf("[INFO] Initializing the LCD.\n");	
	
	initializeControlGPIO();
	initializeDataGPIO();
	
	// Sets the Read/Write pin to 0 since we only write to the LCD.
	setReadWrite(OFF);
	// The default value for enable is 0 if there is no incoming data.
	setEnable(OFF);
	
	setCommandOnDataLine(DEFAULT_CONFIGS);
	sendCommand();
	
	setCommandOnDataLine(CLEAR_DISPLAY);
	sendCommand();
	
	setCommandOnDataLine(RESET_CURSOR);
	sendCommand();
	
	setCommandOnDataLine(INCREMENT_CHARACTER_MODE);
	sendCommand();
	
	setCommandOnDataLine(DISPLAY_CURSOR_OFF);
	sendCommand();
	
	char* testString = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";
	writeString(testString);
}

/**
 * Initializes the GPIO pins that will be used for the LCD data.
*/
void initializeDataGPIO(void) {
	GPIO_InitTypeDef gpio_init_s;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_StructInit(&gpio_init_s);
  gpio_init_s.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  gpio_init_s.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init_s.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_s.GPIO_OType = GPIO_OType_PP;
  gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &gpio_init_s);
}

/**
 * Initializes the GPIO pins that will be used for the LCD control.
*/
void initializeControlGPIO(void) {
	GPIO_InitTypeDef gpio_init_s;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_StructInit(&gpio_init_s);
  gpio_init_s.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  gpio_init_s.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init_s.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_s.GPIO_OType = GPIO_OType_PP;
  gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &gpio_init_s);
}

/**
 * Sets the state of the lcd data pin 0.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData0(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_0);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_0);
		break;
	}
}

/**
 * Sets the state of the lcd data pin 1.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData1(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_1);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_1);
		break;
	}
}

/**
 * Sets the state of the lcd data pin 2.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData2(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_2);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_2);
		break;
	}
}

/**
 * Sets the state of the lcd data pin 3.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData3(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_3);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_3);
		break;
	}
}

/**
 * Sets the state of the lcd data pin 4.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData4(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_4);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_4);
		break;
	}
}

/**
 * Sets the state of the lcd data pin 5.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData5(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_5);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		break;
	}
}

/**
 * Sets the state of the lcd data pin 6.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData6(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_6);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_6);
		break;
	}
}

/**
 * Sets the state of the lcd data pin 7.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setData7(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOE, GPIO_Pin_7);
		break;
		case OFF:
			GPIO_ResetBits(GPIOE, GPIO_Pin_7);
		break;
	}
}

/**
 * Sets the state of the lcd Register Select pin.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setRegisterSelect(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOD, GPIO_Pin_0);
		break;
		case OFF:
			GPIO_ResetBits(GPIOD, GPIO_Pin_0);
		break;
	}
}

/**
 * Sets the state of the lcd Read/Write pin.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setReadWrite(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOD, GPIO_Pin_1);
		break;
		case OFF:
			GPIO_ResetBits(GPIOD, GPIO_Pin_1);
		break;
	}
}

/**
 * Sets the state of the lcd Enable pin.
 *
 * @param state The next state of the GPIO pin, can be either ON or OFF.
*/
void setEnable(gpioState state) {
	switch(state) {
		case ON:
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
		break;
		case OFF:
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
		break;
	}
}

/**
 * Sends a command that was set on the data pin to the LCD screen.
*/
void sendCommand(void) {
	setEnable(ON);
	setEnable(OFF);
	osDelay(COMMAND_DELAY);
}

/**
 * Sets a specific command on the data pins.
 *
 * @param commandToExecute The command that will be set on the data pins.
*/
void setCommandOnDataLine(lcdCommands commandToExecute) {	
	switch(commandToExecute) {
		case CLEAR_DISPLAY:
			internalCursor = 0;
			setData0(ON);
			setData1(OFF);
			setData2(OFF);
			setData3(OFF);
			setData4(OFF);
			setData5(OFF);
			setData6(OFF);
			setData7(OFF);
		break;
		case RESET_CURSOR:
			internalCursor = 0;
			setData0(OFF);
			setData1(ON);
			setData2(OFF);
			setData3(OFF);
			setData4(OFF);
			setData5(OFF);
			setData6(OFF);
			setData7(OFF);
		break;
		case INCREMENT_CHARACTER_MODE:
			setData0(OFF);
			setData1(ON);
			setData2(ON);
			setData3(OFF);
			setData4(OFF);
			setData5(OFF);
			setData6(OFF);
			setData7(OFF);
		break;
		case DISPLAY_CURSOR_ON:
			setData0(ON);
			setData1(ON);
			setData2(ON);
			setData3(ON);
			setData4(OFF);
			setData5(OFF);
			setData6(OFF);
			setData7(OFF);
		break;
		case DISPLAY_CURSOR_OFF:
			setData0(OFF);
			setData1(OFF);
			setData2(ON);
			setData3(ON);
			setData4(OFF);
			setData5(OFF);
			setData6(OFF);
			setData7(OFF);
		break;
		case DEFAULT_CONFIGS:
			setData0(OFF);
			setData1(OFF);
			setData2(ON);
			setData3(ON);
			setData4(ON);
			setData5(ON);
			setData6(OFF);
			setData7(OFF);
		break;
		case SET_CURSOR_SECOND_ROW:
			setData0(OFF);
			setData1(OFF);
			setData2(OFF);
			setData3(OFF);
			setData4(OFF);
			setData5(OFF);
			setData6(ON);
			setData7(ON);
		break;
	}
	
	// Sets the Register Select to 0 so that the LCD expects a command.
	setRegisterSelect(OFF);
}

/**
 * Writes and send a string to the LCD.
 *
 * @param dataToWrite The string to be sent to the LCD.
*/
void writeString(char* dataToWrite) {
	
	while (*dataToWrite) {
		int asciiValue = (int) (*dataToWrite);
		
		// Verifies if the cursor went overbound.
		if (internalCursor == MAX_CHARACTERS_ON_SINGLE_ROW) {
			setCommandOnDataLine(SET_CURSOR_SECOND_ROW);
			sendCommand();
		} else if (internalCursor == 2*MAX_CHARACTERS_ON_SINGLE_ROW) {
			return;
		}
		
		//printf("ASCII Char=%c Value=%i\n", (*dataToWrite), asciiValue);
		
		if ((0x1&asciiValue) == 0) {
			setData0(OFF);
		} else {
			setData0(ON);
		}
		
		if ((0x2&asciiValue) == 0) {
			setData1(OFF);
		} else {
			setData1(ON);
		}
		
		if ((0x4&asciiValue) == 0) {
			setData2(OFF);
		} else {
			setData2(ON);
		}
		
		if ((0x8&asciiValue) == 0) {
			setData3(OFF);
		} else {
			setData3(ON);
		}
		
		if ((0x10&asciiValue) == 0) {
			setData4(OFF);
		} else {
			setData4(ON);
		}
		
		if ((0x20&asciiValue) == 0) {
			setData5(OFF);
		} else {
			setData5(ON);
		}
		
		if ((0x40&asciiValue) == 0) {
			setData6(OFF);
		} else {
			setData6(ON);
		}
		
		if ((0x80&asciiValue) == 0) {
			setData7(OFF);
		} else {
			setData7(ON);
		}
		
		// Sets the Register Select to 1 so that the LCD expects a character.
		setRegisterSelect(ON);
		sendCommand();
		
		dataToWrite++;
		internalCursor++;
	}
}
