/**
 * @file keypadManager.c
 * @author Jean-Sebastien Dery, Matthew Johnston, Gregoire Martin, and Patrick White
 * @version 1.0
 * @date November 22th 2013
 * @brief Manages all the interactions with the keypad.
*/

#include <stdio.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx.h"
#include "keypadManager.h"
#include "cmsis_os.h"
#include "sequence.h"
#include "lcdManager.h"
#include "globals.h"

#define DELTA 5

const int MAX_COLUMN = 2;
const int MAX_ROW = 3;
int column;
int row;
int sequenceNumber = -1;
int updated = 0;
char display;
uint8_t firstIteration = 0;
static int keypadControlPitch, keypadControlRoll;

int updatedRoll1 = 0;
int updatedPitch1 = 0;

int updatedRoll2 = 0;
int updatedPitch2 = 0;

int confirmRoll1 = 0;
int confirmPitch1 = 0;

int confirmRoll2 = 0;
int confirmPitch2 = 0;

int updatedRollSign = 0;
int updatedPitchSign = 0;

int confirmRollSign = 0;
int confirmPitchSign = 0;

char str[24];

void initializeKeypad(void) {
	printf("\n[INFO] keypad initalization");
	// Those are set as input, and they must generate an interrupt.
	GPIO_InitTypeDef gpio_init_row;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_StructInit(&gpio_init_row);
  gpio_init_row.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
  gpio_init_row.GPIO_Mode = GPIO_Mode_IN;
  gpio_init_row.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_row.GPIO_OType = GPIO_OType_PP; 
  gpio_init_row.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &gpio_init_row);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	// Those are set as output.
	GPIO_InitTypeDef gpio_init_column;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_StructInit(&gpio_init_column);
  gpio_init_column.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  gpio_init_column.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init_column.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_column.GPIO_OType = GPIO_OType_PP;
  gpio_init_column.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &gpio_init_column);
	
	//Setup input for B4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource4);
	
	EXTI_InitTypeDef   EXTI_InitStructure4;
  EXTI_InitStructure4.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure4.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure4.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure4.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure4);

	NVIC_InitTypeDef   NVIC_InitStructure4;
  NVIC_InitStructure4.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure4.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure4.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure4.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure4);
	
	//Setup input for B1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
	
	EXTI_InitTypeDef   EXTI_InitStructure1;
  EXTI_InitStructure1.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure1.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure1.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure1.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure1);

	NVIC_InitTypeDef   NVIC_InitStructure1;
  NVIC_InitStructure1.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure1);
	
		//Setup input for B2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);
	
	EXTI_InitTypeDef   EXTI_InitStructure2;
  EXTI_InitStructure2.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure2.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure2.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure2.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure2);

	NVIC_InitTypeDef   NVIC_InitStructure2;
  NVIC_InitStructure2.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure2);
	
	//Setup input for B3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);
	
	EXTI_InitTypeDef   EXTI_InitStructure3;
  EXTI_InitStructure3.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure3.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure3.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure3.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure3);

	NVIC_InitTypeDef   NVIC_InitStructure3;
  NVIC_InitStructure3.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure3);
	
	column = 0;
	row = 0;
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

//
void scanManager(void){
		setUpColumn();
		printf("\nScan: col %i, row %i", column, row);
		scan();
		incrementColumn();

		if (sequenceNumber == 3) {
			if ((display == '*') && updated) {
				updated = 0;
				if (getModeOfOperation() == SEQUENCE_MODE) {
					setModeOfOperation(KEYPAD_CONTROL_MODE);
					writeStringFirstRow("Keypad Control Mode    ");
					
					firstIteration = 1;
				}
				else if (getModeOfOperation() == MAIN_MODE) {
					setModeOfOperation(SEQUENCE_MODE);
					setSequenceMode(OH_PLEASE_SEQUENCE);
					writeStringFirstRow("Seq Mode: Oh, Please...");
				}
				else if (getModeOfOperation() == KEYPAD_CONTROL_MODE)
				{
					setModeOfOperation(SPECIAL_KEYPAD_CONTROL_MODE);
					//writeStringFirstRow("Keypad Control Mode    ");			
					firstIteration = 1;
				}
				else {
					setModeOfOperation(MAIN_MODE);
					writeStringFirstRow("Main Mode              ");
				}
			}
		}
		else if (sequenceNumber == 0) {
			if (getModeOfOperation() == SEQUENCE_MODE) {
				if ((display == '1') && updated) {
					updated = 0;
					setSequenceMode(OH_PLEASE_SEQUENCE);
					writeStringFirstRow("Seq Mode: Oh, Please...");
				}
				else if ((display == '2') && updated) {
					updated = 0;
					setSequenceMode(QUEEN_SEQUENCE);
					writeStringFirstRow("Seq Mode: Queen        ");
				}
			}
		}
		
	//	writeString("%d");
		
		if (getModeOfOperation() == SEQUENCE_MODE) {

		}
		
	//	display = '!';
}

void setUpColumn(void){
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	switch(column){
		case 0:
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			break;
		case 1:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			break;
		case 2:
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			break;
		}
}


void scan(void){
	osDelay(20);
}


void incrementColumn(void){
	if (column < MAX_COLUMN){
		column++;
	} else {
		column = 0;
	}
}


char findButton(void) {
	switch(column){
		case 0:
			switch(row){
				case 0:
					return '1';
				case 1:
					return '4';
				case 2:
					return '7';
				case 3:
					return '*';
			}
		break;	
		case 1:
			switch(row){
				case 0:
					return '2';
				case 1:
					return '5';
				case 2:
					return '8';
				case 3:
					return '0';
			}
		break;
		case 2:
			switch(row){
				case 0:
					return '3';
				case 1:
					return '6';
				case 2:
					return '9';
				case 3:
					return '#';
			}
		break;
		}	
		return 'X'; //to satisfy Keil
	}
	
	void doKeypadControl(void) {
	while (1) {
		//control from keypad
		if (getModeOfOperation() == KEYPAD_CONTROL_MODE) {
			if (firstIteration) {
				keypadControlPitch = 0;
				keypadControlRoll = 0;
				setPitchAndRoll(0, 0);
				firstIteration = 0;
				osSignalSet(getWirelessThreadId(), 1);

			}
			else {
				if (display == '2' && updated) {
					updated = 0;
					keypadControlRoll += DELTA;
				}
				else if (display == '8' && updated) {
					updated = 0;
					keypadControlRoll -= DELTA;
				}
				else if (display == '4' && updated) {
					updated = 0;
					keypadControlPitch -= DELTA;				
				}
				else if (display == '6' && updated) {
					updated = 0;
					keypadControlPitch += DELTA;								
					
				}
				
				if (keypadControlPitch > 90) {
					keypadControlPitch = 90;
				}
				else if (keypadControlPitch < -90) {
					keypadControlPitch = -90;
				}
				
				if (keypadControlRoll > 90) {
					keypadControlRoll = 90;
				}
				else if (keypadControlRoll < -90) {
					keypadControlRoll = -90;
				}
				
				
				setPitchAndRoll(keypadControlPitch, keypadControlRoll);
				osSignalSet(getWirelessThreadId(), 1);
				osDelay(50);
		}

			
		}
	}
}


void doSpecialKeypadControl(void) {
	while (1) {
		//control from keypad
		if (getModeOfOperation() == SPECIAL_KEYPAD_CONTROL_MODE) {
			if (firstIteration) {
				keypadControlPitch = 0;
				keypadControlRoll = 0;
				
				updatedRoll1 = 0;
				updatedRoll2 = 0;
				updatedPitch1 = 0;
				updatedPitch2 = 0;
				updatedRollSign = 0;
				updatedPitchSign = 0;
				confirmRoll1 = 0;
				confirmPitch1 = 0;
				confirmRoll2 = 0;
				confirmPitch2 = 0;
				confirmRollSign = 0;
				confirmPitchSign = 0;
				
				setPitchAndRoll(0, 0);
				firstIteration = 0;
				osSignalSet(getWirelessThreadId(), 1);
			}
			else {
				
				if (updatedRoll1 == 0)
				{
					writeStringFirstRow("Enter digit 1 of pitch  ");
					if (display != '#' && display != '*')
					{
						keypadControlRoll = (display - '0')*10;
						updatedRoll1 = 1;
					}
				}
				else if (confirmRoll1 == 0)
				{
					if (display == '#')
					{
						confirmRoll1 = 1;
					}
					else if (display != '*')
					{
						keypadControlRoll = (display - '0')*10;
					}
				}
				else if (updatedRoll2 == 0)
				{
					writeStringFirstRow("Enter digit 2 of pitch  ");
					if (display != '#' && display != '*')
					{
						keypadControlRoll += (display - '0');
						updatedRoll2 = 1;
					}
				}
				else if (confirmRoll2 == 0)
				{
					if (display == '#')
					{
						confirmRoll2 = 1;
					}
					else if (display != '*')
					{
						keypadControlRoll = keypadControlRoll - (keypadControlRoll % 10) + (display - '0');
					}
				}
				else if (updatedRollSign == 0)
				{
					writeStringFirstRow("1 = +ve     2 = -ve     ");
					if (display != '#' && display != '*')
					{
						if (display == '1')
						{
							// Do nothing to update value
							updatedRollSign = 1;
						}
						else if (display == '2')
						{
							keypadControlRoll = -1*keypadControlRoll;
							updatedRollSign = 1;
						}
					}
				}
				else if (confirmRollSign == 0)
				{
					if (display == '#')
					{
						confirmRollSign = 1;
					}
					else if (display != '*')
					{
						if (keypadControlRoll > 0)
						{
							if (display == '1')
							{
								// Do nothing to update value
							}
							else if (display == '2')
							{
								keypadControlRoll = -1*keypadControlRoll;
							}
						}
						else
						{
							if (display == '1')
							{
								
								keypadControlRoll = -1*keypadControlRoll;
							}
							else if (display == '2')
							{
								// Do nothing to update value
							}
						}
					}
				}
				else if (updatedPitch1 == 0)
				{
					writeStringFirstRow("Enter digit 1 of roll   ");
					if (display != '#' && display != '*')
					{
						keypadControlPitch = (display - '0')*10;
						updatedPitch1 = 1;
					}
				}
				else if (confirmPitch1 == 0)
				{
					if (display == '#')
					{
						confirmPitch1 = 1;
					}
					else if (display != '*')
					{
						keypadControlPitch = (display - '0')*10;
					}
				}
				else if (updatedPitch2 == 0)
				{
					writeStringFirstRow("Enter digit 2 of roll   ");
					if (display != '#' && display != '*')
					{
						keypadControlPitch += (display - '0');
						updatedPitch2 = 1;
					}
				}
				else if (confirmPitch2 == 0)
				{
					//writeStringFirstRow("Press # to confirm digit");
					if (display == '#')
					{
						confirmPitch2 = 1;
					}
					else if (display != '*')
					{
						keypadControlPitch = keypadControlPitch - (keypadControlPitch % 10) + (display - '0');
					}
				}
				else if (updatedPitchSign == 0)
				{
					writeStringFirstRow("1 = +ve     2 = -ve     ");
					if (display != '#' && display != '*')
					{
						if (display == '1')
						{
							// Do nothing to update value
							updatedPitchSign = 1;
						}
						else if (display == '2')
						{
							keypadControlPitch = -1*keypadControlPitch;
							updatedPitchSign = 1;
						}
					}
				}
				else if (confirmPitchSign == 0)
				{
					//writeStringFirstRow("Press # to confirm sign ");
					if (display == '#')
					{
						confirmPitchSign = 1;
					}
					else if (display != '*')
					{
						if (keypadControlPitch > 0)
						{
							if (display == '1')
							{
								// Do nothing to update value
							}
							else if (display == '2')
							{
								keypadControlPitch = -1*keypadControlPitch;
							}
						}
						else
						{
							if (display == '1')
							{
								
								keypadControlPitch = -1*keypadControlPitch;
							}
							else if (display == '2')
							{
								// Do nothing to update value
							}
						}
					}
				}
				
				
				if (keypadControlPitch > 90) {
					keypadControlPitch = 90;
				}
				else if (keypadControlPitch < -90) {
					keypadControlPitch = -90;
				}
				
				if (keypadControlRoll > 90) {
					keypadControlRoll = 90;
				}
				else if (keypadControlRoll < -90) {
					keypadControlRoll = -90;
				}
				
				// Yes I am aware that i messed up pitch and roll here
				sprintf(str, "Roll: %d Pitch: %d   ", keypadControlPitch, keypadControlRoll);
				writeStringSecondRow(str);
				
				if (confirmPitchSign == 1 && confirmRollSign == 1)
				{
					updatedRoll1 = 0;
					updatedRoll2 = 0;
					updatedPitch1 = 0;
					updatedPitch2 = 0;
					updatedRollSign = 0;
					updatedPitchSign = 0;
					confirmRoll1 = 0;
					confirmPitch1 = 0;
					confirmRoll2 = 0;
					confirmPitch2 = 0;
					confirmRollSign = 0;
					confirmPitchSign = 0;
					
					updated = 0;
					
					setPitchAndRoll(keypadControlPitch, keypadControlRoll);
					osSignalSet(getWirelessThreadId(), 1);
					osDelay(500);
				}
			}	
		}
	}
}


void EXTI4_IRQHandler(void) {
        // Get current interrupt status   
				row = 0;
        if (EXTI_GetITStatus(EXTI_Line4) != RESET){ 
					EXTI_ClearITPendingBit(EXTI_Line4);
					display = findButton();  
					sequenceNumber = 0;
					updated = 1;
        }
    EXTI_ClearFlag(EXTI_Line4);
}

void EXTI1_IRQHandler(void) {
        // Get current interrupt status   
				row = 1;
        if (EXTI_GetITStatus(EXTI_Line1) != RESET){ 
					EXTI_ClearITPendingBit(EXTI_Line1);
					display = findButton(); 
					sequenceNumber = 1;
					updated = 1;
        }
    EXTI_ClearFlag(EXTI_Line1);
}

void EXTI2_IRQHandler(void) {
        // Get current interrupt status   
				row = 2;
        if (EXTI_GetITStatus(EXTI_Line2) != RESET){ 
					EXTI_ClearITPendingBit(EXTI_Line2);
					display = findButton();   
					sequenceNumber = 2;
					updated = 1;
        }
    EXTI_ClearFlag(EXTI_Line2);
}

void EXTI3_IRQHandler(void) {
        // Get current interrupt status    
				row = 3;
        if (EXTI_GetITStatus(EXTI_Line3) != RESET){ 
					EXTI_ClearITPendingBit(EXTI_Line3);
					display = findButton();
					sequenceNumber = 3;
					if (updated == 0) {
						updated = 1;
					}
        }
    EXTI_ClearFlag(EXTI_Line3);
}


