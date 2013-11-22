#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include "stm32f4xx.h"

typedef enum {WIFI_STATE, PAD_STATE} fsmState;

void initializeFSM(void);
void switchCurrentState(void);
void switchInternalState(void);
void processCurrentState(void);

#endif
