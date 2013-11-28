#include "threads.h"
#include "cmsis_os.h"
#include "accelerometer.h"
#include "sequence.h"


#define QUEEN_MAX_ANGLE 40

#define OH_PLEASE_BACK_ANGLE -30
#define OH_PLEASE_FORWARD_ANGLE 90

uint8_t sequenceMode;


void doSequences(void) {
	if (modeOfOperation == SEQUENCE_MODE) {
				if (sequenceMode == QUEEN_SEQUENCE) {
					osMutexWait(pitchRollMutex, osWaitForever);
					pitch = 0;
					roll = 0;
			//		osSignalSet(tid_wireless, 1);
					
					int i;
					
					pitch = -1 * QUEEN_MAX_ANGLE;
					roll = 0;
					osSignalSet(tid_wireless, 1);
//					osDelay(20);
//					pitch = 0;
//					roll = 0;			
//					osSignalSet(tid_wireless, 1);
					osDelay(500);
					pitch = QUEEN_MAX_ANGLE;
					roll = 0;			
					osSignalSet(tid_wireless, 1);
					osDelay(500);
					pitch = 0;
					roll = 0;			
					osSignalSet(tid_wireless, 1);
					//osDelay();

					osMutexRelease(pitchRollMutex);
					osDelay(100);
			}
			else if (sequenceMode == OH_PLEASE_SEQUENCE) {
				osMutexWait(pitchRollMutex, osWaitForever);
				roll = OH_PLEASE_BACK_ANGLE;
				pitch = 0;
				osSignalSet(tid_wireless, 1);
				osDelay(500);
				roll = OH_PLEASE_FORWARD_ANGLE;
				pitch = 0;
				osSignalSet(tid_wireless, 1);
				osDelay(500);
				pitch = 0;
				roll = 0;
				osSignalSet(tid_wireless, 1);
				osMutexRelease(pitchRollMutex);
				osDelay(1000);
			}
		}
}
