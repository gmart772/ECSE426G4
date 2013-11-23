#include "stm32f4_discovery_lis302dl.h"
#include "math.h"
#include "conversion.h"
#include "stm32f4xx_gpio.h"
#include "led.h"
#include "accFilter.h"
#include "cmsis_os.h"

#define NO_TAP_DETECTED 0
#define TAP_DETECTED 1
#define X_OFFSET 8
#define Y_OFFSET -17
#define Z_OFFSET -18

//static float PI = 3.14159265;
static float G = 1000.0; // Earth's gravity in mg
static float correctionMatrix[4][3];

static accFilter filterX;
static accFilter filterY;
static accFilter filterZ;

extern float pitch, roll;
extern osMutexId pitchRollMutex;

extern osThreadId tid_wireless, tid_acc;

void initAccelerometer(void);
void getAcceleration(int32_t *values);
float* getTilt(int32_t *acc, float *tilts);
float getPitch(int32_t accX, int32_t accY, int32_t accZ);
float getRoll(int32_t accX, int32_t accY, int32_t accZ);
void calibrate(int32_t *values, int32_t *readings);
void resetLatch(void);
void EXTI0_IRQHandler(void);
void calculateTilts(void);
