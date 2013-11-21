/**
 * @file finiteStateMachine.c
 * @author Jean-Sebastien Dery (260430688) and Matthew Johnston (260349319)
 * @version 1.0
 * @date October 31th 2013
 * @brief Defines the Finite State Machine used for the continuous run, along with all its interactions with the different components.
*/

#include <stdio.h>
#include "finiteStateMachine.h"
#include "ledManager.h"
#include "cmsis_os.h"
#include "servoManager.h"

// Mutex used to protect the currentState.
osMutexId currentState_mutex;
osMutexDef(currentState_mutex);

void processAccelerometerNormalState();
void processAccelerometerPWMState();
void processTemperatureNORMALState();
void processTemperaturePWMState();
void cwLeds();
void ccwLeds();
fsmState getCurrentState();

fsmState currentState;
activeLED currentLED;

// Defines the constants used for the boundaries in the NORMAL operation mode.
const int UPPER_BOUND = 90;
const int LOWER_BOUND = -UPPER_BOUND;
const int MIDDLE_UPPER_BOUND = 45;
const int MIDDLE_LOWER_BOUND = -MIDDLE_UPPER_BOUND;
const int UPPER_DEAD = 5;
const int LOWER_DEAD = -UPPER_DEAD;
const int MAX_PWM_DUTY_CYCLE = 1000;

// Defines the boundaries of the counters used to flash the LEDs.
const uint32_t UPPER_COUNTER_BOUND = 10;
const uint32_t MIDDLE_COUNTER_BOUND = 20;

// Counters used for the NORMAL operation state.
int pitchCounter = 0;
int rollCounter = 0;

// Variable used for the PWM mode on the LED.
int ledBrightness = MAX_PWM_DUTY_CYCLE;
uint32_t prevFilterAvg = 0;
int deviation = 0;

/**
 * Returns the currentState.
*/
fsmState getCurrentState() {
	return (currentState);	
}

/**
 * Initializes the Finite State Machine used in the continuous run.
*/
void initializeFSM() {
	//printf("[INFO] initializeFSM()\n");
	currentState = ACCELEROMETER_NORMAL_STATE;
	currentLED = TOP;
	currentState_mutex = osMutexCreate(osMutex(currentState_mutex));
}

/**
 * Process the actions that correspond to the state at which the FSM is currently in.
*/
void processCurrentState() {
	
	for (int i = -90 ; i < 90 ; i = i + 10) {
		setRollAngle(i);
		goToSpecifiedAngles();
		osDelay(1000);
	}
	
	/*TIM4->CCR1 = 600;
	TIM4->CCR2 = 600;
	osDelay(1000);
	
	TIM4->CCR1 = 1050;
	TIM4->CCR2 = 1050;
	osDelay(1000);
	
	TIM4->CCR1 = 1500;
	TIM4->CCR2 = 1500;
	osDelay(1000);
	
	TIM4->CCR1 = 1950;
	TIM4->CCR2 = 1950;
	osDelay(1000);
	
	TIM4->CCR1 = 2400;
	TIM4->CCR2 = 2400;
	osDelay(1000);
	
	TIM4->CCR1 = 1950;
	TIM4->CCR2 = 1950;
	osDelay(1000);
	
	TIM4->CCR1 = 1500;
	TIM4->CCR2 = 1500;
	osDelay(1000);
	
	TIM4->CCR1 = 1050;
	TIM4->CCR2 = 1050;
	osDelay(1000);*/
	
	
	/*ledBrightness = 2400;
	// Start with a full duty cycle (100%) and decrement it until the duty cycle is equal to 0.
	while (ledBrightness > 600) {
		// The LEDs have been configured with TIM4 so this is why we do this.
		// Check for this function to have more info: TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		// CCR1 is the TIM capture/compare register 1, same for CCR2, CCR3 and CCR4.
		TIM4->CCR1 = ledBrightness;
		TIM4->CCR2 = ledBrightness;
		ledBrightness -= 10;
		
		printf("[INFO] Current pulse width in is %i microseconds.\n", ledBrightness);
		
		// Adds some delay so that the humans can see what's going on.
		osDelay(10);
	}
	
	// Start with a duty cycle equal to 0 and increment it until it reaches 100%.
	while (ledBrightness < 2400) {
		// The LEDs have been configured with TIM4 so this is why we do this.
		// Check for this function to have more info: TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		// CCR1 is the TIM capture/compare register 1, same for CCR2, CCR3 and CCR4.
		TIM4->CCR1 = ledBrightness;
		TIM4->CCR2 = ledBrightness;
		ledBrightness += 10;
		
		printf("[INFO] Current pulse width in is %i microseconds.\n", ledBrightness);
		
		// Adds some delay so that the humans can see what's going on.
		osDelay(10);
	}*/
}