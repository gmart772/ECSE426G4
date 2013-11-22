/**
 * @file finiteStateMachine.c
 * @author Jean-Sebastien Dery, Matthew Johnston, Gregoire Martin, and Patrick White
 * @version 1.0
 * @date October 31th 2013
 * @brief Defines the Finite State Machine used for the continuous run, along with all its interactions with the different components.
*/

#include <stdio.h>
#include "finiteStateMachine.h"
#include "cmsis_os.h"
#include "servoManager.h"

// Mutex used to protect the currentState.
osMutexId currentState_mutex;
osMutexDef(currentState_mutex);

fsmState currentState;

/**
 * Initializes the Finite State Machine used in the continuous run.
*/
void initializeFSM() {
	printf("[INFO] initializeFSM()\n");
	currentState = WIFI_STATE;
	currentState_mutex = osMutexCreate(osMutex(currentState_mutex));
}

/**
 * Process the actions that correspond to the state at which the FSM is currently in.
*/
void processCurrentState() {
	osMutexWait(currentState_mutex, osWaitForever);
	fsmState tempState = currentState;
	osMutexRelease(currentState_mutex);
	
	switch(tempState) {
		case WIFI_STATE:
			for (int i = -90 ; i < 90 ; i = i + 30) {
				setRollAngle(i);
				goToSpecifiedAngles();
				osDelay(1000);
			}
		break;
		case PAD_STATE:
			
		break;
	}
}
