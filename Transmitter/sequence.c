#include "threads.h"
#include "cmsis_os.h"
#include "accelerometer.h"
#include "sequence.h"
#include "globals.h"


#define QUEEN_MAX_ANGLE 40

#define OH_PLEASE_BACK_ANGLE -30
#define OH_PLEASE_FORWARD_ANGLE 90


void doSequences(void) {
	if (getModeOfOperation() == SEQUENCE_MODE) {
				if (getSequenceMode() == QUEEN_SEQUENCE) {
					
				//	setPitchAndRoll(0, 0);
					//		osSignalSet(tid_wireless, 1);
										
					setPitchAndRoll(-1 * QUEEN_MAX_ANGLE, 0);
					osSignalSet(getWirelessThreadId(), 1);
//					osDelay(20);
//					pitch = 0;
//					roll = 0;			
//					osSignalSet(tid_wireless, 1);
					osDelay(500);
					setPitchAndRoll(QUEEN_MAX_ANGLE, 0);
					osSignalSet(getWirelessThreadId(), 1);
					osDelay(500);
				//	setPitchAndRoll(0, 0);
			//		osSignalSet(getWirelessThreadId(), 1);
					//osDelay();

					osDelay(100);
			}
			else if (getSequenceMode() == OH_PLEASE_SEQUENCE) {
				setPitchAndRoll(0, OH_PLEASE_BACK_ANGLE);
				osSignalSet(getWirelessThreadId(), 1);
				osDelay(500);
				setPitchAndRoll(0, OH_PLEASE_FORWARD_ANGLE);
				osSignalSet(getWirelessThreadId(), 1);
				osDelay(500);
				setPitchAndRoll(0, 0);				
				osSignalSet(getWirelessThreadId(), 1);
				osDelay(1000);
			}
		}
}
