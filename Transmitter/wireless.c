#include "wireless.h"
#include "lcdManager.h"


void init_wireless_chip(void)
{
	SPI_Config();

	
	uint8_t init_data[16];
	
	init_data[0] = SMARTRF_SETTING_IOCFG2;
	wireless_WriteReg(init_data, IOCFG2, 1);
	
	init_data[0] = SMARTRF_SETTING_IOCFG0D;
	wireless_WriteReg(init_data, IOCFG0, 1);
	
	init_data[0] = SMARTRF_SETTING_FIFOTHR;
	wireless_WriteReg(init_data, FIFOTHR, 1);
	
	init_data[0] = SMARTRF_SETTING_PKTLEN;
	init_data[1] = SMARTRF_SETTING_PKTCTRL1;
	init_data[2] = SMARTRF_SETTING_PKTCTRL0;
	init_data[3] = SMARTRF_SETTING_ADDR;
	init_data[4] = SMARTRF_SETTING_CHANNR;
	init_data[5] = SMARTRF_SETTING_FSCTRL1;
	init_data[6] = SMARTRF_SETTING_FSCTRL0;
	init_data[7] = SMARTRF_SETTING_FREQ2;
	init_data[8] = SMARTRF_SETTING_FREQ1;
	init_data[9] = SMARTRF_SETTING_FREQ0;
	init_data[10] = SMARTRF_SETTING_MDMCFG4;
	init_data[11] = SMARTRF_SETTING_MDMCFG3;
	init_data[12] = SMARTRF_SETTING_MDMCFG2;
	init_data[13] = SMARTRF_SETTING_MDMCFG1;
	init_data[14] = SMARTRF_SETTING_MDMCFG0;
	init_data[15] = SMARTRF_SETTING_DEVIATN;
	wireless_WriteReg(init_data, PKTLEN, 16);
	
	init_data[0] = SMARTRF_SETTING_MCSM1;
	wireless_WriteReg(init_data, MCSM1, 1);
	
	init_data[0] = SMARTRF_SETTING_MCSM0;
	init_data[1] = SMARTRF_SETTING_FOCCFG;
	init_data[2] = SMARTRF_SETTING_BSCFG;
	init_data[3] = SMARTRF_SETTING_AGCCTRL2;
	init_data[4] = SMARTRF_SETTING_AGCCTRL1;
	init_data[5] = SMARTRF_SETTING_AGCCTRL0;
	wireless_WriteReg(init_data, MCSM0, 6);

	init_data[0] = SMARTRF_SETTING_FREND1;
	init_data[1] = SMARTRF_SETTING_FREND0;
	init_data[2] = SMARTRF_SETTING_FSCAL3;
	init_data[3] = SMARTRF_SETTING_FSCAL2;
	init_data[4] = SMARTRF_SETTING_FSCAL1;
	init_data[5] = SMARTRF_SETTING_FSCAL0;
	wireless_WriteReg(init_data, FREND1, 6);
	
	init_data[0] = SMARTRF_SETTING_FSTEST;
	wireless_WriteReg(init_data, FSTEST, 1);
	
	init_data[0] = SMARTRF_SETTING_TEST2;
	init_data[1] = SMARTRF_SETTING_TEST1;
	init_data[2] = SMARTRF_SETTING_TEST0;
	wireless_WriteReg(init_data, TEST2, 3);
	
	wireless_WriteReg(NULL, FLUSH_TX_FIFO, 0);
	wireless_WriteReg(NULL, FLUSH_RX_FIFO, 0);
	wireless_WriteReg(NULL, START_IDLE, 0);

	
}
	 
void SPI_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	SPI_InitTypeDef  SPI_InitStructure;


  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable the SPI clock */
  //SPIx_CLK_INIT(SPIx_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(SPIx_CLK, ENABLE);

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
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPIx, &SPI_InitStructure);
  SPI_Cmd(SPIx, ENABLE);
	
	/* SPI  NSS pin configuration */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = SPIx_NSS_PIN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

  GPIO_Init(SPIx_NSS_GPIO_PORT, &GPIO_InitStructure);
	
	wireless_CS_HIGH();


	wireless_WriteReg(NULL, FLUSH_RX_FIFO, 0);
	wireless_WriteReg(NULL, FLUSH_TX_FIFO, 0);
  /* Configure the Priority Group to 1 bit */                
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* Configure the SPI interrupt priority */
  //NVIC_InitStructure.NVIC_IRQChannel = SPIx_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //NVIC_Init(&NVIC_InitStructure); 
}

uint8_t wireless_SendByte(uint8_t byte)
{
  /* Loop while DR register in not emplty */
	uint32_t wirelessTimeout = TIMEOUT;
	
  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
  {
    if((wirelessTimeout--) == 0) return wireless_TIMEOUT_UserCallback();
  }
  
  /* Send a Byte through the SPI peripheral */
  SPI_I2S_SendData(SPIx, byte);
  
  /* Wait to receive a Byte */
  wirelessTimeout = TIMEOUT;
  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
  {
    if((wirelessTimeout--) == 0) return wireless_TIMEOUT_UserCallback();
  }
  
  /* Return the Byte read from the SPI bus */
  return (uint8_t)SPI_I2S_ReceiveData(SPIx);
}

uint32_t wireless_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  while (1)
  {  
		//	int x  = 0;
  }
}

void wireless_ReadReg(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead, uint8_t mode)
{  
	uint8_t read_type;
	
	if (mode == CONFIG_REGISTER)
	{
		if(NumByteToRead > 1)
		{
			read_type = BURST_READ;
		}
		else
		{
			read_type = SINGLE_READ;
		}
	}
	else if (mode == STATUS_REGISTER)
	{
		read_type = BURST_READ;
	}
	
  /* Set chip select Low at the start of the transmission */
  wireless_CS_LOW();
  
  /* Send the Address of the indexed register */
  wireless_SendByte(ReadAddr | read_type);
  
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

uint8_t wireless_WriteReg(uint8_t *byte, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  /* Loop while DR register in not empty */
//	uint32_t wirelessTimeout = TIMEOUT;
	//address |= (uint8_t) 0x80;
	uint8_t write_type;
	uint8_t chipStatusByte;
	
	if (NumByteToWrite > 1)
	{
		write_type = BURST_WRITE;
	}
	else
	{
		write_type = SINGLE_WRITE;
	}
	
	wireless_CS_LOW();
	int i;
	chipStatusByte = wireless_SendByte(WriteAddr | write_type);
	for (i = 0; i < NumByteToWrite; i++) {
		chipStatusByte = wireless_SendByte(byte[i]);
	}
	wireless_CS_HIGH();
	
	return chipStatusByte;
}

void wireless_TransmitData(uint8_t *data, uint8_t NumByteToTransmit) 
{
	if (NumByteToTransmit > 64) {
	  //flag some sort of error
	}
	
	uint8_t write_type;
	uint8_t chipStatusByte;
			
	chipStatusByte = wireless_WriteReg(data, TX_FIFO, 2);

	chipStatusByte = wireless_WriteReg(data, START_TX, 0);
	
	uint8_t state[1];
	wireless_ReadReg(state, 0x35, 1, STATUS_REGISTER);

}

void sendData() {
	uint8_t data[2];
	while (1) {
		// wait for signal
		osSignalWait(1, osWaitForever);
		
		// mutex
		
		data[0] = (uint8_t) (getPitch() + 90);
		data[1] = (uint8_t) (getRoll() + 90);
		
		char str[24];
		sprintf(str, "Pitch: %d Roll: %d   ", data[0], data[1]);
		writeStringSecondRow(str);
		
		/*char c = (char) ( ((int) '0') + 5 );
		
		data[0] = 180;
		
		char* info = "(Pitch:Roll)=(";
		int roll1 = data[0]*(100/100);
		++info;
		(*info) = (char) (((int) '0') + roll1);
		int roll2 = data[0]*(010/010);
		++info;
		(*info) = (char) (((int) '0') + roll2);
		int roll3 = data[0]*(001/001);
		++info;
		(*info) = (char) (((int) '0') + roll3);
		
		// Displays the angle on the LCD.
		writeStringSecondRow(info);*/
		

		// maybe pad with dummy bytes?
		// mutex
		//Write to LCD
		
		wireless_TransmitData(data, 2);
	}
}
