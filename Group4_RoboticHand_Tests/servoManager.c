/**
 * @file servoManager.c
 * @author Jean-Sebastien Dery, Matthew Johnston, Gregoire Martin, and Patrick White
 * @version 1.0
 * @date November 21th 2013
 * @brief Manages all the interactions with the servo motors.
*/

#include <stdio.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx.h"
#include "servoManager.h"
#include "cmsis_os.h"

const uint32_t ANGLE_MIN_90 = 600;
const uint32_t ANGLE_MIN_45 = 1050;
const uint32_t ANGLE_0 = 1500;
const uint32_t ANGLE_PLUS_45 = 1950;
const uint32_t ANGLE_PLUS_90 = 2400;

int roll_angle = 0;
int pitch_angle = 0;

void setupGPIOForTIM4(void);
void initializeTIM4Timer(void);
uint32_t angleToPulseWidth(int angle);

osMutexId roll_mutex;
osMutexDef(roll_mutex);
osMutexId pitch_mutex;
osMutexDef(pitch_mutex);

/**
 * Initializes the servo motors.
*/
void initializeServoMotors(void) {
	roll_mutex = osMutexCreate(osMutex(roll_mutex));
	pitch_mutex = osMutexCreate(osMutex(pitch_mutex));
	initializeTIM4Timer();
}

/**
 * Sets the roll angle for the robotic hand.
*/
void setRollAngle(int roll) {
	osMutexWait(roll_mutex, osWaitForever);
	roll_angle = roll;
	osMutexRelease(roll_mutex);
}

/**
 * Sets the pitch angle for the robotic hand.
*/
void setPitchAngle(int pitch) {
	osMutexWait(pitch_mutex, osWaitForever);
	pitch_angle = pitch;
	osMutexRelease(pitch_mutex);
}

/*
 * Goes to the Roll and pitch that is stored in the roll_angle and pitch_angle variables respectively.
*/
void goToSpecifiedAngles(void) {
	// Fetches the roll value.
	osMutexWait(roll_mutex, osWaitForever);
	int tempRoll = roll_angle;
	osMutexRelease(roll_mutex);
	
	// Fetches the pitch value.
	osMutexWait(pitch_mutex, osWaitForever);
	int tempPitch = pitch_angle;
	osMutexRelease(pitch_mutex);
	
	printf("[INFO] Roll=%i and Pitch=%i (degrees)\n", tempRoll, tempPitch);
	
	// Converts the angle to actual pulse width.
	uint32_t rollPulseWidth = angleToPulseWidth(tempRoll);
	uint32_t pitchPulseWidth = angleToPulseWidth(tempPitch);
	
	printf("[INFO] Roll=%i and Pitch=%i (microseconds)\n", rollPulseWidth, pitchPulseWidth);
	
	// Sets the new duty cycle to the two GPIO pins used for the servo motors.
	TIM4->CCR1 = rollPulseWidth;
	TIM4->CCR2 = pitchPulseWidth;
}

/**
 * Converts an angle to the appropriate pulse width that will be used to control the servo motors.
 *
 * @param angle The angle to be converted, it needs to range from -90° to +90°.
 * @return The pulse width corresponding to the angle passed in the signature. If the angle is not in the specified range, its value will be of ANGLE_0.
*/
uint32_t angleToPulseWidth(int angle) {
	// If the angle is out of the possible range, the default value will be the 0° position.
	if (angle < -90 || angle > 90) {
		return (ANGLE_0);
	}
	
	int pulseWidth = 10*angle + 1500;
	
	return ((uint32_t)pulseWidth);
}

/**
 * Setup the GPIO to work with the TIM4.
*/
void setupGPIOForTIM4(void) {
	// Setup the GPIO pins of the LEDs to work witht the TIM4 timer.
	GPIO_InitTypeDef GPIO_InitStructure;
	// Enables the clock for GPIOD and TIM4.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	// Setup the pin source of the LEDs.
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	// The GPIO mode is set to Alternating Function so we can play with the Duty Cycle.
	// If it was to GPIO_Mode_OUT, then we would not be able to set a Duty Cycle using the TIM4 timer.
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure); 
	// GPIOD, because this is the one used for the LEDs.
	// Sets all the Pin numbers that will be connected to TIM4.
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4); 
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
}

/**
 * Setup the TIM4 timer that will be used to generate PWM signals that will control the servo motors.
*/
void initializeTIM4Timer(void) {
	// Code example on how to setup TIM4:
	// https://my.st.com/public/STe2ecommunities/mcu/Lists/STM32Discovery/DispForm.aspx?ID=1816&Source=/public/STe2ecommunities/Tags.aspx?tags=stm32f4
	
	// Some explanation about PWM signals:
	// http://umassamherstm5.org/tech-tutorials/pic32-tutorials/pic32mx220-tutorials/pwm
	
	// Documentation about the HS-322 servo motor from Hitec that has similar properties:
	// http://www.servocity.com/html/hs-322hd_standard_deluxe.html
	
	// The servo motor are controller with PWM signals, the overal period of the signal must be 20 ms (which leads to a frequency of 50 Hz).
	// Within this period, a pulse with a known duration will determine the actual position of the servo motor. The position ranges from
	// -90° to +90°. 
	
	// Under is a table that maps the servo angle to its pulse duration:
	// +-------------------------------------------+
	// | Angle (°) | Pulse Duration (microseconds) |
	// +-----------+-------------------------------+
	// |    -90    |             600               |
	// |    -45    |            1050               |
	// |      0    |            1500               |
	// |    +45    |            1950               |
	// |    +90    |            2400               |
	// +-----------+-------------------------------+
	
	// Under is a table mapping the channel registers to actual GPIO pin:
	// +---------------------+
	// | Register | GPIO Pin |
	// +----------+----------+
	// |   CCR1   |   PD12   | ROLL
	// |   CCR2   |   PD13   | PITCH
	// |   CCR3   |   PD14   |
	// |   CCR4   |   PD15   |
	// +----------+----------+
	
	// The clock frequency is being fetched from the system's variable.
	RCC_ClocksTypeDef clockType;
	RCC_GetClocksFreq(&clockType);
	uint32_t clockFrequency = clockType.PCLK1_Frequency*2;
	printf("[INFO] The frequency of AHB1 (PCLK1) is %i Hz\n", clockFrequency);
	// The period represents the maximum value that the hardware counter can reach.
	// It is set to 20,000 since this represents 20,000 microseconds, and it's an easy mapping
	// to adjust the duty cycle to time duration afterwards.
	uint32_t period = 20000;
	// The period is 20 ms, which leads to a frequency of 50 Hz.
	uint32_t desiredInterruptFrequency = 50;
	uint32_t prescaler = (clockFrequency) / (desiredInterruptFrequency * period);
	double actualPeriod = (double)period*(double)prescaler*(1/(double)clockFrequency);
	printf("[INFO] The period is %i, the desiredInterruptFrequency is %i, and the prescaler is %i.\n", period, desiredInterruptFrequency, prescaler);
	printf("[INFO] The period of the PWM signal is %f seconds.\n", actualPeriod);
	
	setupGPIOForTIM4();
	
	// Setup the PWM functionality with the TIM4 timer.
	// This is the same kind of configuration as with the TIM3 timer used for the accelerometer.
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Period = period-1;
  TIM_TimeBaseStructure.TIM_Prescaler = (prescaler)-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	// So once we have inicialized the TIM4 time-based configuration, we need to configure the different channels.
	// So the way this is working is that the register CCRx will be loaded at everytime the counter will overflow.
	// Then, the PIN will on ON during the Duty Cycle set in the register, then it will be turned off the rest of the time.
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// Sets up PWM for Channel 1.
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ANGLE_0;
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	// Sets up PWM for Channel 2.
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = ANGLE_0;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	// Sets up PWM for Channel 3.
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	// Sets up PWM for Channel 4.
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	// Enabling the TIM4 counter, and starting the machine.
	TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}
