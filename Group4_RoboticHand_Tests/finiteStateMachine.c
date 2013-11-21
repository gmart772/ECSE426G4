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
	
	/*for (int i = -90 ; i < 90 ; i = i + 10) {
		setRollAngle(i);
		goToSpecifiedAngles();
		osDelay(1000);
	}*/
	
}