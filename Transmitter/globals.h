#include "cmsis_os.h"

#define MAIN_MODE 0 
#define SEQUENCE_MODE 1
#define KEYPAD_CONTROL_MODE 2

#define QUEEN_SEQUENCE 0
#define OH_PLEASE_SEQUENCE 1	

void setPitchAndRoll(float newPitch, float newRoll);
float getPitch(void);
float getRoll(void);
uint8_t getModeOfOperation(void);
void setModeOfOperation(uint8_t newModeOfOperation);
uint8_t getSequenceMode(void);
void setSequenceMode(uint8_t newSequenceMode);
void setThreadIds(osThreadId wireless, osThreadId acc, osThreadId sequence, osThreadId keypad, osThreadId keypadControl);
osThreadId getWirelessThreadId(void);
osThreadId getAccThreadId(void);
osThreadId getSequenceThreadId(void);
osThreadId getKeypadThreadId(void);
