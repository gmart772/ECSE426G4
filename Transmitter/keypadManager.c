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

const int MAX_COLUMN = 2;
const int MAX_ROW = 3;
int column;
int row;

void initializeKeypad(void) {
	
	printf("\n[INFO] keypad initalization");
	// Those are set as input, and they must generate an interrupt.
	GPIO_InitTypeDef gpio_init_row;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_StructInit(&gpio_init_row);
  gpio_init_row.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
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
  gpio_init_column.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  gpio_init_column.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init_column.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_column.GPIO_OType = GPIO_OType_PP;
  gpio_init_column.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &gpio_init_column);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
	
	EXTI_InitTypeDef   EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

	NVIC_InitTypeDef   NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	column = 0;
	row = 0;
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	GPIO_ResetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
	scanManager();
}
void scanManager(){
	setUpColumn();
	scanRow();
	osDelay(1);
	incrementRow();
	}
void setUpColumn(){
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	GPIO_ResetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
	switch(column){
		case 0:
			GPIO_SetBits(GPIOB, GPIO_Pin_4);
		
		case 1:
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
		
		case 2:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
}
void scanRow(){
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
	switch(row){
		case 0:
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
		case 1:
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
		case 2:
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);
		case 3:
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);				
	}
}
void incrementRow(){
	if (row < MAX_ROW){
		row++;
	}
	else{
		row = 0;
		incrementColumn();
	}
}
void incrementColumn(){
	if (column < MAX_COLUMN){
		column++;
	}
	else{
		column = 0;
	}
	setUpColumn();
}
char findButton(){
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
		}	
		return 'X'; //to satisfy Keil
	}

void EXTI1_IRQHandler(void) {
        // Get current interrupt status        
        if (EXTI_GetITStatus(EXTI_Line1)){
                printf(" %c ", findButton()); 
                EXTI_ClearITPendingBit(EXTI_Line1);
        }
    EXTI_ClearFlag(EXTI_Line1);
}        


