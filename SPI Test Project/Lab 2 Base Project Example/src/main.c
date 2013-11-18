#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

//#include "gpio_example.h"

#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
SPI_InitTypeDef  SPI_InitStructure;

	#define SPIx                           SPI1
  #define SPIx_CLK                       RCC_APB2Periph_SPI1
  #define SPIx_CLK_INIT                  RCC_APB1PeriphClockCmd
  #define SPIx_IRQn                      SPI1_IRQn
  #define SPIx_IRQHANDLER                SPI2_IRQHandler

  #define SPIx_SCK_PIN                   GPIO_Pin_5
  #define SPIx_SCK_GPIO_PORT             GPIOA
  #define SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOA
  #define SPIx_SCK_SOURCE                GPIO_PinSource1
  #define SPIx_SCK_AF                    GPIO_AF_SPI1

  #define SPIx_MISO_PIN                  GPIO_Pin_6
  #define SPIx_MISO_GPIO_PORT            GPIOA
  #define SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOA
  #define SPIx_MISO_SOURCE               GPIO_PinSource2
  #define SPIx_MISO_AF                   GPIO_AF_SPI1

  #define SPIx_MOSI_PIN                  GPIO_Pin_7
  #define SPIx_MOSI_GPIO_PORT            GPIOA
  #define SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOA
  #define SPIx_MOSI_SOURCE               GPIO_PinSource3
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
	uint8_t wireless_SendByte(uint8_t byte);
	void wireless_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
				
	uint16_t TIMEOUT = 0x1000;		

int main()
{

	//GPIO_example_config();
	SPI_Config();
	

	
  //SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);

	
	//uint8_t command = 0x0C40;
//	uint8_t command = 0xF0;
	
	uint8_t pBuffer[1]; 
	
	//wireless_Read(pBuffer, command, 2);
	
	uint8_t command = 0x30;
	wireless_Read(pBuffer, command, 1);

	
	//wireless_Read(&pBuffer, command, 1);
	
	
	
	
	//SPI_I2S_SendData(SPIx, data);
	
	//while(1) {

		//GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		//printf("This is a TEST?");
		
	//}
}
	 
void SPI_Config(void)
{
	
	
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable the SPI clock */
  //SPIx_CLK_INIT(SPIx_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(SPIx_CLK, ENABLE);

  
  /* Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(SPIx_SCK_GPIO_CLK | SPIx_MISO_GPIO_CLK | SPIx_MOSI_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(SPIx_NSS_GPIO_CLK, ENABLE);

  /* SPI GPIO Configuration --------------------------------------------------*/

  
  /* Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(SPIx_SCK_GPIO_PORT, SPIx_SCK_SOURCE, SPIx_SCK_AF);
  GPIO_PinAFConfig(SPIx_MISO_GPIO_PORT, SPIx_MISO_SOURCE, SPIx_MISO_AF);    
  GPIO_PinAFConfig(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_SOURCE, SPIx_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = SPIx_SCK_PIN;
  GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);
  
  /* SPI  MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPIx_MISO_PIN;
  GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStructure);  

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPIx_MOSI_PIN;
  GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
		  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPIx);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPIx, &SPI_InitStructure);

  SPI_Cmd(SPIx, ENABLE);
	
	/* SPI  NSS pin configuration */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 // GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin = SPIx_NSS_PIN;
  //GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

  GPIO_Init(SPIx_NSS_GPIO_PORT, &GPIO_InitStructure);
	
	wireless_CS_HIGH();

 

  /* Configure the Priority Group to 1 bit */                
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Configure the SPI interrupt priority */
  NVIC_InitStructure.NVIC_IRQChannel = SPIx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
}

void SPIx_IRQHandler(void) {
	printf("Interrupt received!\n");
	uint16_t data;
	data = SPI_I2S_ReceiveData(SPIx);
		printf("Version data: %d\n", data);

}

uint8_t wireless_SendByte(uint8_t byte)
{
  /* Loop while DR register in not emplty */
	uint32_t wirelessTimeout = TIMEOUT;
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
  {
    if((wirelessTimeout--) == 0) return wireless_TIMEOUT_UserCallback();
  }
  
  /* Send a Byte through the SPI peripheral */
  SPI_I2S_SendData(SPI1, byte);
  
  /* Wait to receive a Byte */
  wirelessTimeout = TIMEOUT;
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
  {
    if((wirelessTimeout--) == 0) return wireless_TIMEOUT_UserCallback();
  }
  
  /* Return the Byte read from the SPI bus */
  return (uint8_t)SPI_I2S_ReceiveData(SPI1);
}

uint32_t wireless_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  while (1)
  {  
		//	int x  = 0;
  }
}

void wireless_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{  
 // if(NumByteToRead > 0x01)
 // {
 //   ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
 // }
 // else
 // {
  ReadAddr |= (uint8_t)0x80;
 // }
  /* Set chip select Low at the start of the transmission */
  wireless_CS_LOW();
  
  /* Send the Address of the indexed register */
  wireless_SendByte(ReadAddr);
  
  /* Receive the data that will be read from the device (MSB First) */
  while(NumByteToRead > 0x00)
  {
    /* Send dummy byte (0x00) to generate the SPI clock to LIS302DL (Slave device) */
    *pBuffer = wireless_SendByte(DUMMY_BYTE);
    NumByteToRead--;
    pBuffer++;
  }
  
  /* Set chip select High at the end of the transmission */ 
  wireless_CS_HIGH();
}





