#include "cmsis_os.h"
#include "globals.h"


/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void accelerometer(void const * argument);
void wireless(void const * argument);
void keypad(void const * argument);
void sequence(void const * argument);
void keypadControl(void const * argument);
void specialKeypadControl(void const * argument);