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

const uint8_t COMMAND_DELAY = 5;
const uint8_t ENABLE_DELAY = 1;

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
	printf("[INFO] Initializing the LCD.");	
	
	initializeControlGPIO();
	initializeDataGPIO();
	
	// Sets the Read/Write pin to 0 since we only write to the LCD.
	setReadWrite(OFF);
	
	setCommandOnDataLine(CLEAR_DISPLAY);
	sendCommand();
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

void sendCommand(void) {
	setEnable(ON);
	osDelay(ENABLE_DELAY);
	setEnable(OFF);
	osDelay(COMMAND_DELAY);
}

void setCommandOnDataLine(lcdCommands commandToExecute) {	
	switch(commandToExecute) {
		case CLEAR_DISPLAY:
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
			
		break;
		case INCREMENT_CHARACTER_MODE:
			
		break;
	}
	
	// Sets the Register Select to 0 so that the LCD expects a command.
	setRegisterSelect(OFF);
}

void writeString(char* dataToWrite) {
	
}