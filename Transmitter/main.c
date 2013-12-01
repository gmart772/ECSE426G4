#include "arm_math.h"
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "led.h"
#include "threads.h"
#include "lcdManager.h"
#include "timer.h"
#include "keypadManager.h"
#include "globals.h"

short timerInterrupt;

//osThreadId tid_wireless;

//! Thread structure for above thread
osThreadDef(accelerometer, osPriorityNormal, 1, 0);
osThreadDef(wireless, osPriorityNormal, 1, 0);
osThreadDef(keypad, osPriorityNormal, 1, 0);
osThreadDef(sequence, osPriorityNormal, 1, 0);
osThreadDef(keypadControl, osPriorityNormal, 1, 0);

/*!
 @brief Program entry point
 */
int main (void) {
	// Initalize all periphs from previous labs
	initLeds();
	initTimer();
	initTimer4();
	initializeKeypad();
	initializeLCD();
	
	writeStringFirstRow("Main Mode");
	setModeOfOperation(MAIN_MODE);
	// Create mutux for the mode
	
	// Start all threads
	setThreadIds(osThreadCreate(osThread(wireless), NULL),
							osThreadCreate(osThread(accelerometer), NULL),
							osThreadCreate(osThread(sequence), NULL),
							osThreadCreate(osThread(keypad), NULL),
							osThreadCreate(osThread(keypadControl), NULL));
	
	while(1) {
		osDelay(osWaitForever);
	}
}

