#include "cmsis_os.h"
#include "wireless.h"

extern osThreadId tid_acc, tid_wireless;
extern osMutexId pitchRollMutex;

/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void accelerometer(void const * argument);
void wireless(void const * argument);

