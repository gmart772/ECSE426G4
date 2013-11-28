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

osThreadId tid_keypad;
extern osThreadId tid_wireless;
extern float pitch, roll;
extern osMutexId pitchRollMutex;
extern uint8_t modeOfOperation;

extern uint8_t sequenceMode;

const int MAX_COLUMN = 2;
const int MAX_ROW = 3;
int column;
int row;
int sequenceNumber = -1;
int updated = 0;
char display;

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
	//GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

void scanManager(void){
		setUpColumn();
		printf("\nScan: col %i, row %i", column, row);
		scan();
		incrementColumn();

		if (sequenceNumber == 3) {
			if ((display == '*') && updated) {
				updated = 0;
				if (modeOfOperation == SEQUENCE_MODE) {
					modeOfOperation = MAIN_MODE;
				}
				else {
					modeOfOperation = SEQUENCE_MODE;
					sequenceMode = OH_PLEASE_SEQUENCE;
				}
			}
		}
		else if (sequenceNumber == 0) {
			if ((display == '1') && updated) {
				updated = 0;
				sequenceMode = OH_PLEASE_SEQUENCE;
			}
			else if ((display == '2') && updated) {
				updated = 0;
				sequenceMode = QUEEN_SEQUENCE;
			}
			
		}
		
	//	writeString("%d");
		
		if (modeOfOperation == SEQUENCE_MODE) {

		}
		
	//	display = '!';
}

void setUpColumn(void){
	//GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
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
	}
	else{
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
