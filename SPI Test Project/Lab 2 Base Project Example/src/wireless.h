#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

//#include "gpio_example.h"

#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "SMARTRF_CC2500.h"

	#define BURST_WRITE										0x40
	#define SINGLE_WRITE									0x00
	#define BURST_READ										0xC0
	#define SINGLE_READ										0x80
	
	#define CONFIG_REGISTER								0x00
	#define STATUS_REGISTER								0x01

	#define SPIx                           SPI1
  #define SPIx_CLK                       RCC_APB2Periph_SPI1
  #define SPIx_CLK_INIT                  RCC_APB1PeriphClockCmd
  #define SPIx_IRQn                      SPI1_IRQn
  #define SPIx_IRQHANDLER                SPI2_IRQHandler

  #define SPIx_SCK_PIN                   GPIO_Pin_5
  #define SPIx_SCK_GPIO_PORT             GPIOA
  #define SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOA
  #define SPIx_SCK_SOURCE                GPIO_PinSource5
  #define SPIx_SCK_AF                    GPIO_AF_SPI1

  #define SPIx_MISO_PIN                  GPIO_Pin_6
  #define SPIx_MISO_GPIO_PORT            GPIOA
  #define SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOA
  #define SPIx_MISO_SOURCE               GPIO_PinSource6
  #define SPIx_MISO_AF                   GPIO_AF_SPI1

  #define SPIx_MOSI_PIN                  GPIO_Pin_7
  #define SPIx_MOSI_GPIO_PORT            GPIOA
  #define SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOA
  #define SPIx_MOSI_SOURCE               GPIO_PinSource7
  #define SPIx_MOSI_AF                   GPIO_AF_SPI1
	
	#define SPIx_NSS_PIN                  GPIO_Pin_4
  #define SPIx_NSS_GPIO_PORT            GPIOA
  #define SPIx_NSS_GPIO_CLK             RCC_AHB1Periph_GPIOA
  #define SPIx_NSS_SOURCE               GPIO_PinSource4
  #define SPIx_NSS_AF                   GPIO_AF_SPI1
	
	
	#define wireless_CS_LOW()       GPIO_ResetBits(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN)
	#define wireless_CS_HIGH()      GPIO_SetBits(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN)
	
	#define DUMMY_BYTE                 ((uint8_t)0x00)
	
	void SPI_Config(void);
	uint8_t wireless_SendByte(uint8_t byte);
  uint32_t wireless_TIMEOUT_UserCallback(void);
	void wireless_ReadReg(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead, uint8_t mode);
	void wireless_WriteReg(uint8_t *byte, uint8_t WriteAddr, uint16_t NumByteToRead);
	void init_wireless_chip(void);
				
	static uint16_t TIMEOUT = 0x1000;