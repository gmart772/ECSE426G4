#include "globals.h"

static float pitch = 0, roll = 0;
static osMutexId pitchRollMutex = NULL;
static osMutexId modeMutex = NULL;
static osMutexId sequenceMutex = NULL;
static osThreadId tid_wireless = NULL, tid_acc = NULL, tid_sequence = NULL, tid_keypad = NULL, tid_keypad_control = NULL;
static uint8_t modeOfOperation = 0, sequenceMode = 0;


void setPitchAndRoll(float newPitch, float newRoll) {
	if (newPitch > 90) {
		newPitch = 90;
	}
	else if (newPitch < -90) {
		newPitch = -90;
	}
	
	if (newRoll > 90) {
		newRoll = 90;
	}
	else if (newRoll < -90) {
		newRoll = -90;
	}
	osMutexWait(pitchRollMutex, osWaitForever);
	pitch = newPitch;
	roll = newRoll;
	osMutexRelease(pitchRollMutex);
}

float getPitch() {
	float temp;
	osMutexWait(pitchRollMutex, osWaitForever);
	temp = pitch;
	osMutexRelease(pitchRollMutex);
	return temp;
}

float getRoll() {
	float temp;
	osMutexWait(pitchRollMutex, osWaitForever);
	temp = roll;
	osMutexRelease(pitchRollMutex);
	return temp;
}

uint8_t getModeOfOperation() {
	uint8_t temp;
	osMutexWait(modeMutex, osWaitForever);
	temp = modeOfOperation;
	osMutexRelease(modeMutex);
	return temp;
}

void setModeOfOperation(uint8_t newModeOfOperation) {
	osMutexWait(modeMutex, osWaitForever);
	modeOfOperation = newModeOfOperation;
	osMutexRelease(modeMutex);
}

void setThreadIds(osThreadId wireless, osThreadId acc, osThreadId sequence, osThreadId keypad, osThreadId keypadControl) {
	tid_wireless = wireless;
	tid_acc = acc;
	tid_sequence = sequence;
	tid_keypad = keypad;
}


uint8_t getSequenceMode() {
	uint8_t temp;
	osMutexWait(sequenceMutex, osWaitForever);
	temp = sequenceMode;
	osMutexRelease(sequenceMutex);
	return temp;
}

void setSequenceMode(uint8_t newSequenceMode) {
	osMutexWait(sequenceMutex, osWaitForever);
	sequenceMode = newSequenceMode;
	osMutexRelease(sequenceMutex);
}

osThreadId getWirelessThreadId(void) {
		return tid_wireless;
}

osThreadId getAccThreadId(void) {
		return tid_acc;
}

osThreadId getSequenceThreadId(void) {
		return tid_sequence;
}

osThreadId getKeypadThreadId(void) {
		return tid_keypad;
}

osThreadId getKeypadControlThreadId(void) {
		return tid_keypad_control;
}
