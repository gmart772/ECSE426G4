/**
 * @file timerManager.c
 * @author Jean-Sebastien Dery (260430688), Matthew Johnston (260349319)
 * @version 1.0
 * @date November 21th 2013
 * @brief Manages all the interactions with the on-board timers peripheral.
*/

#include <stdio.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx.h"
#include "timerManager.h"

void activateTIM3Interrupt(void);
void activateTIM2Interrupt(void);

void initializeTIM2Timer(void) {
	// To have information about the Nested Vectored Interrupt Controller go to Reference Manual page 195.
	// TIM2 to TIM5 main features explained in Reference Manual at page 361.
	// To have information about how the hardware interrupts work on the STM32f4 go to http://visualgdb.com/tutorials/arm/stm32/timers/
	// Another example available here http://amarkham.com/?p=29
	
	activateTIM2Interrupt();
	
	// Enables the clock for the TIM3 timer so we can use it.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// Creates the Structure that will contain all the desired parameters.
	TIM_TimeBaseInitTypeDef timer2InitParameters;
	// The TIM_Prescaler multiplied with the Clock Period will be the time between each incrementation of the counter used to generate interrupts.
	// The total time between interrupts will be given by (TIM_Prescaler*TIM_Period*(Clock Period)) which leads to a frequency at which the 
	// interrupts will happen to be equal to: Clock Frequency/(TIM_Prescaler*TIM_Period) that is given in the Lab Experiment requirements.
	// This value has been taken arbitrarily, and TIM_Period was adjusted according to it.
	// When defining the prescaler remember that the speed is 42 Mhz (as presented on the STM32F40x Block Diagram schematic).
	timer2InitParameters.TIM_Prescaler = 40000;
	// Sets to up because we want it to count from 0 to the specified value (and generate an interrupt when the desired value is reached).
	timer2InitParameters.TIM_CounterMode = TIM_CounterMode_Up;
	// This is the upper bound of the counter. When it reaches this value it will generate an interrupt and reset itself to 0.
	timer2InitParameters.TIM_Period = 20;
	timer2InitParameters.TIM_ClockDivision = 0;
	// Initializes the TIM2 timer with the specified parameters.
	TIM_TimeBaseInit(TIM2, &timer2InitParameters);
	// Enable the interrupt generation for the TIM2 timer.
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// Activates the TIM2 timer.
	TIM_Cmd(TIM2, ENABLE);
}

/**
 * Setup the interrupt on the Nested Vectored Interrupt Controller for the TIM2 timer.
*/
void activateTIM2Interrupt(void) {
	NVIC_InitTypeDef nvicStructure;
	// The IRQ channel is going to be TIM2 since this is the timer that we are using.
  nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
	// The NVIC provides a Group Priority and a Sub Priority within this Group.
	// Link to this information: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/BABHGEAJ.html
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
	// Enables the IRQ channel.
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	// Actually enable the IRQ channel with NVIC.
  NVIC_Init(&nvicStructure);
}

/**
 * Initializes the on-board TIM3 timer at a frequency of 25 Hz, as per lab requirement.
*/
void initializeTIM3Timer(void) {
	// To have information about the Nested Vectored Interrupt Controller go to Reference Manual page 195.
	// TIM2 to TIM5 main features explained in Reference Manual at page 361.
	// To have information about how the hardware interrupts work on the STM32f4 go to http://visualgdb.com/tutorials/arm/stm32/timers/
	// Another example available here http://amarkham.com/?p=29
	
	activateTIM3Interrupt();
	
	// Enables the clock for the TIM3 timer so we can use it.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	// Creates the Structure that will contain all the desired parameters.
	TIM_TimeBaseInitTypeDef timer3InitParameters; 
	// The TIM_Prescaler multiplied with the Clock Period will be the time between each incrementation of the counter used to generate interrupts.
	// The total time between interrupts will be given by (TIM_Prescaler*TIM_Period*(Clock Period)) which leads to a frequency at which the 
	// interrupts will happen to be equal to: Clock Frequency/(TIM_Prescaler*TIM_Period) that is given in the Lab Experiment requirements.
	// This value has been taken arbitrarily, and TIM_Period was adjusted according to it.
	// When defining the prescaler remember that the speed is 42 Mhz (as presented on the STM32F40x Block Diagram schematic).
	timer3InitParameters.TIM_Prescaler = 40000;
	// Sets to up because we want it to count from 0 to the specified value (and generate an interrupt when the desired value is reached).
	timer3InitParameters.TIM_CounterMode = TIM_CounterMode_Up;
	// This is the upper bound of the counter. When it reaches this value it will generate an interrupt and reset itself to 0.
	timer3InitParameters.TIM_Period = 42;
	timer3InitParameters.TIM_ClockDivision = 0;
	// Initializes the TIM3 timer with the specified parameters.
	TIM_TimeBaseInit(TIM3, &timer3InitParameters);
	// Enable the interrupt generation for the TIM3 timer.
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	// Activates the TIM3 timer.
	TIM_Cmd(TIM3, ENABLE);
}

/**
 * Setup the interrupt on the Nested Vectored Interrupt Controller for the TIM3 timer.
*/
void activateTIM3Interrupt(void) {
	NVIC_InitTypeDef nvicStructure;
	// The IRQ channel is going to be TIM3 since this is the timer that we are using.
  nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	// The NVIC provides a Group Priority and a Sub Priority within this Group.
	// Link to this information: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/BABHGEAJ.html
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
	// Enables the IRQ channel.
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	// Actually enable the IRQ channel with NVIC.
  NVIC_Init(&nvicStructure);
}
