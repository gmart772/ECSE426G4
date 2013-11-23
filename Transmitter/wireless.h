#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "SMARTRF_CC2500.h"
#include "cmsis_os.h"
#include "accelerometer.h"

#define BURST_WRITE										0x40
#define SINGLE_WRITE									0x00
#define BURST_READ										0xC0
#define SINGLE_READ										0x80

#define CONFIG_REGISTER								0x00
#define STATUS_REGISTER								0x01

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

#define DUMMY_BYTE                 		((uint8_t)0x00)

#define TX_FIFO												0x3F
#define RX_FIFO												0x3F

// Command strobes
#define START_TX											0x35
#define START_RX											0x34
#define START_IDLE										0x36
#define START_NOP											0x3D
	
	
void SPI_Config(void);
uint8_t wireless_SendByte(uint8_t byte);
uint32_t wireless_TIMEOUT_UserCallback(void);
void wireless_ReadReg(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead, uint8_t mode);
uint8_t wireless_WriteReg(uint8_t *byte, uint8_t WriteAddr, uint16_t NumByteToRead);
void init_wireless_chip(void);
void wireless_TransmitData(uint8_t *data, uint8_t NumByteToTransmit);
			
static uint16_t TIMEOUT = 0x1000;