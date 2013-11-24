#ifndef WIRELESS_H
#define WIRELESS_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "cmsis_os.h"
#include "SMARTRF_CC2500.h"

	#define SINGLE_WRITE									0x00
	#define BURST_WRITE										0x40
	#define SINGLE_READ										0x80
	#define BURST_READ										0xC0
	
	#define FIFO_READ											0x00
	#define CONFIG_REGISTER								0
	#define STATUS_REGISTER								1
	
	// RX status reg
	#define MARCSTATE											0x35
	#define TX_FIFO												0x3F
	#define RX_FIFO												0x3F
	#define RXBYTES												0x3B
	#define FLUSH_RX_FIFO									0x3A
	#define FLUSH_TX_FIFO									0x3B
	
	// Command strobes
	#define START_TX											0x35
	#define CALIBRATE											0x33
	#define START_RX											0x34
	#define START_IDLE										0x36
	#define START_NOP											0x3D

	#define DUMMY_BYTE                 		((uint8_t)0x00)
	
	#define SPIx                           SPI2
  #define SPIx_CLK                       RCC_APB1Periph_SPI2
  #define SPIx_CLK_INIT                  RCC_APB1PeriphClockCmd
  #define SPIx_IRQn                      SPI2_IRQn
  #define SPIx_IRQHANDLER                SPI2_IRQHandler
  #define SPIx_SCK_PIN                   GPIO_Pin_13
  #define SPIx_SCK_GPIO_PORT             GPIOB
  #define SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
  #define SPIx_SCK_SOURCE                GPIO_PinSource13
  #define SPIx_SCK_AF                    GPIO_AF_SPI2
  #define SPIx_MISO_PIN                  GPIO_Pin_14
  #define SPIx_MISO_GPIO_PORT            GPIOB
  #define SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
  #define SPIx_MISO_SOURCE               GPIO_PinSource14
  #define SPIx_MISO_AF                   GPIO_AF_SPI2
  #define SPIx_MOSI_PIN                  GPIO_Pin_15
  #define SPIx_MOSI_GPIO_PORT            GPIOB
  #define SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
  #define SPIx_MOSI_SOURCE               GPIO_PinSource15
  #define SPIx_MOSI_AF                   GPIO_AF_SPI2
	#define SPIx_NSS_PIN                  GPIO_Pin_12
  #define SPIx_NSS_GPIO_PORT            GPIOB
  #define SPIx_NSS_GPIO_CLK             RCC_AHB1Periph_GPIOB
  #define SPIx_NSS_SOURCE               GPIO_PinSource12
  #define SPIx_NSS_AF                   GPIO_AF_SPI2
	
	#define wireless_CS_LOW()       			GPIO_ResetBits(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN)
	#define wireless_CS_HIGH()      			GPIO_SetBits(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN)
	
	extern osMutexId roll_mutex;
	extern osMutexId pitch_mutex;
	
	extern int roll_angle;
	extern int pitch_angle;
	
	extern osThreadId tid_wifiThread;
	
	void SPI_Config(void);
	
	void receiveAccData(uint8_t *data);
	
	int checkRXByteCount(void);

	void EXTI0_IRQHandler(void);
	
	uint32_t wireless_TIMEOUT_UserCallback(void);
	
	uint8_t wireless_SendByte(uint8_t byte);
	uint8_t wireless_CommandStrobe(uint8_t StrobeAddr);
	uint8_t wireless_WriteReg(uint8_t *byte, uint8_t WriteAddr, uint16_t NumByteToRead);
	
	void wireless_ReadReg(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead, uint8_t mode);
	void wireless_ReadConfigRegister(uint8_t *data, uint8_t StartAddr, uint8_t NumBytesToRead);
	void wireless_ReadStatusReg(uint8_t *data, uint8_t ReadAddr);
	void wireless_ReadRXFIFO(uint8_t *data);
	
	void initializeWirelessChip(void);
				
	static uint16_t TIMEOUT = 0x1000;
	
#endif
