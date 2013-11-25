#include "cmsis_os.h"
#include "wireless.h"
#include "keypadManager.h"

extern osThreadId tid_acc, tid_wireless, tid_keypad;
extern osMutexId pitchRollMutex;

/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void accelerometer(void const * argument);
void wireless(void const * argument);
void keypad(void const * argument);

