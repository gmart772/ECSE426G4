#include "threads.h"

void accelerometer(void const *argument) {
	initAccelerometer();
	calculateTilts();
}

void wireless(void const *argument) {
	init_wireless_chip();
	sendAccData();
	
	/*
	wait for signal from accelerometer
	transmit
	
	*/
}

