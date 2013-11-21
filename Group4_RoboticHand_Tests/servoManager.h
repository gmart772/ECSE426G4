#ifndef SERVOMANAGER_H
#define SERVOMANAGER_H

#include "stm32f4xx.h"

void initializeServoMotors();
void goToSpecifiedAngles();
void setRollAngle(int roll);
void setPitchAngle(int pitch);

#endif