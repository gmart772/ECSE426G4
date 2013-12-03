#include "globals.h"

static float pitch = 0, roll = 0;
static osMutexId pitchRollMutex = NULL;
static osMutexId modeMutex = NULL;
static osMutexId sequenceMutex = NULL;
static osThreadId tid_wireless = NULL, tid_acc = NULL, tid_sequence = NULL, tid_keypad = NULL, tid_keypad_control = NULL, tid_special_keypad_control = NULL;
static uint8_t modeOfOperation = 0, sequenceMode = 0;


/**
 * @brief Sets the pitch and roll angles.
 * @param newPitch: New pitch angle.
 * @param newRoll: New roll angle.
 */
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

/**
 * @brief Get the pitch angle.
 * @return The pitch angle.
 */
float getPitch() {
	float temp;
	osMutexWait(pitchRollMutex, osWaitForever);
	temp = pitch;
	osMutexRelease(pitchRollMutex);
	return temp;
}

/**
 * @brief Get the roll angle.
 * @return The roll angle.
 */
float getRoll() {
	float temp;
	osMutexWait(pitchRollMutex, osWaitForever);
	temp = roll;
	osMutexRelease(pitchRollMutex);
	return temp;
}

/**
 * @brief Get the current mode of operation.
 * @return The mode of operation.
 */
uint8_t getModeOfOperation() {
	uint8_t temp;
	osMutexWait(modeMutex, osWaitForever);
	temp = modeOfOperation;
	osMutexRelease(modeMutex);
	return temp;
}

/**
 * @brief Set the mode of operation.
 * @param newModeOfOperation: The new mode of operation.
 */
void setModeOfOperation(uint8_t newModeOfOperation) {
	osMutexWait(modeMutex, osWaitForever);
	modeOfOperation = newModeOfOperation;
	osMutexRelease(modeMutex);
}

/**
 * @brief Set the thread IDs. 
 * @params The thread IDs. 
 */
void setThreadIds(osThreadId wireless, osThreadId acc, osThreadId sequence, osThreadId keypad, osThreadId keypadControl, osThreadId specialKeypadControl) {
	tid_wireless = wireless;
	tid_acc = acc;
	tid_sequence = sequence;
	tid_keypad = keypad;
	tid_keypad_control = keypadControl;
	tid_special_keypad_control = specialKeypadControl;
}


/**
 * @brief Get the sequence mode.
 * @return The current sequence mode.
 */
uint8_t getSequenceMode() {
	uint8_t temp;
	osMutexWait(sequenceMutex, osWaitForever);
	temp = sequenceMode;
	osMutexRelease(sequenceMutex);
	return temp;
}

/**
 * @brief Sets the sequence mode.
 * @param newSequenceMode: The new sequence mode.
 */
void setSequenceMode(uint8_t newSequenceMode) {
	osMutexWait(sequenceMutex, osWaitForever);
	sequenceMode = newSequenceMode;
	osMutexRelease(sequenceMutex);
}

/**
 * @brief Get the Wireless Thread ID.
 * @return The Wireless thread ID.
 */
osThreadId getWirelessThreadId(void) {
		return tid_wireless;
}

/**
 * @brief Get the Accelerometer wireless Thread ID.
 * @return The Accelerometer thread ID.
 */
osThreadId getAccThreadId(void) {
		return tid_acc;
}

/**
 * @brief Get the Sequence Thread ID.
 * @return The Sequence thread ID.
 */
osThreadId getSequenceThreadId(void) {
		return tid_sequence;
}

/**
 * @brief Get the Keypad Thread ID.
 * @return The Keypad thread ID.
 */
osThreadId getKeypadThreadId(void) {
		return tid_keypad;
}

/**
 * @brief Get the Keypad Control Thread ID.
 * @return The Keypad Control thread ID.
 */
osThreadId getKeypadControlThreadId(void) {
		return tid_keypad_control;
}

/**
 * @brief Get the Special Keypad Thread ID.
 * @return The Special Keypad thread ID.
 */
osThreadId getSpecialKeypadControlThreadId(void) {
		return tid_special_keypad_control;
}