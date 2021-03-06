#include "threads.h"
#include "wireless.h"
#include "keypadManager.h"
#include "sequence.h"

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
	//setSequenceMode(OH_PLEASE_SEQUENCE);
	while (1) {
		doSequences();
	}
}

void keypadControl(void const *argument) {
	while (1) {
		doKeypadControl();
	}
}

void specialKeypadControl(void const *argument) {
	while (1) {
		doSpecialKeypadControl();
	}
}