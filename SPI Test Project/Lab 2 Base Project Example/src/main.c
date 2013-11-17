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
	
	void SPI_Config(void);
        

int main()
{

	//GPIO_example_config();
	SPI_Config();
	
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPIx, &SPI_InitStructure);

  SPI_Cmd(SPIx, ENABLE);
	
  SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);

	
	uint16_t data = 0x31;
	SPI_I2S_SendData(SPIx, data);
	
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
  SPIx_CLK_INIT(SPIx_CLK, ENABLE);
  
  /* Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(SPIx_SCK_GPIO_CLK | SPIx_MISO_GPIO_CLK | SPIx_MOSI_GPIO_CLK, ENABLE);

  /* SPI GPIO Configuration --------------------------------------------------*/
  /* GPIO Deinitialisation */
  GPIO_DeInit(SPIx_SCK_GPIO_PORT);
  GPIO_DeInit(SPIx_MISO_GPIO_PORT);
  GPIO_DeInit(SPIx_MOSI_GPIO_PORT);
  
  /* Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(SPIx_SCK_GPIO_PORT, SPIx_SCK_SOURCE, SPIx_SCK_AF);
  GPIO_PinAFConfig(SPIx_MISO_GPIO_PORT, SPIx_MISO_SOURCE, SPIx_MISO_AF);    
  GPIO_PinAFConfig(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_SOURCE, SPIx_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
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





