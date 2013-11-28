#include "threads.h"
#include "wireless.h"
#include "keypadManager.h"
#include "sequence.h"

void accelerometer(void const * argument);
void wireless(void const * argument);
void keypad(void const * argument);


void accelerometer(void const *argument) {
	initAccelerometer();
	calculateTilts();
}

void wireless(void const *argument) {
	init_wireless_chip();
	sendData();
	
	/*
	wait for signal from accelerometer
	transmit
	
	*/
}

void keypad(void const *argument){
	while(1){
		scanManager();
	}
}

void sequence(void const *argument) {
	while (1) {
		doSequences();
	}
}

