#include "arm_math.h"
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "led.h"
#include "threads.h"
#include "lcdManager.h"
#include "timer.h"
#include "keypadManager.h"

short timerInterrupt;

osThreadId tid_wireless;
osThreadId tid_sequence;

//! Thread structure for above thread
osThreadDef(accelerometer, osPriorityNormal, 1, 0);
osThreadDef(wireless, osPriorityNormal, 1, 0);
osThreadDef(keypad, osPriorityNormal, 1, 0);
osThreadDef(sequence, osPriorityNormal, 1, 0);

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
	
	// Create mutux for the mode
	
	// Start thread all threads
	tid_acc = osThreadCreate(osThread(accelerometer), NULL);
	tid_wireless = osThreadCreate(osThread(wireless), NULL);
	tid_keypad = osThreadCreate(osThread(keypad), NULL);
	tid_sequence = osThreadCreate(osThread(sequence), NULL);
	
	while(1) {
		osDelay(osWaitForever);
	}
}

