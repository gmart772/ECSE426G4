#include "cmsis_os.h"

extern osThreadId tid_acc, tid_wireless, tid_keypad;
extern osMutexId pitchRollMutex;
extern osMutexId modeMutex;
extern uint8_t modeOfOperation, sequenceMode;

#define MAIN_MODE 0 
#define SEQUENCE_MODE 1


/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void accelerometer(void const * argument);
void wireless(void const * argument);
void keypad(void const * argument);
void sequence(void const * argument);
