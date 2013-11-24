#include "wireless.h"

void initializeWirelessChip(void)
{
	SPI_Config();

	uint8_t init_data[16];
	
	init_data[0] = SMARTRF_SETTING_IOCFG2;
	wireless_WriteReg(init_data, IOCFG2, 1);
	
	init_data[0] = SMARTRF_SETTING_IOCFG0;
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
	init_data[1] = SMARTRF_SETTING_MCSM0;
	init_data[2] = SMARTRF_SETTING_FOCCFG;
	init_data[3] = SMARTRF_SETTING_BSCFG;
	init_data[4] = SMARTRF_SETTING_AGCCTRL2;
	init_data[5] = SMARTRF_SETTING_AGCCTRL1;
	init_data[6] = SMARTRF_SETTING_AGCCTRL0;
	wireless_WriteReg(init_data, MCSM1, 7);

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
}


uint32_t wireless_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  while (1)
  {  
		//	int x  = 0;
  }
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

void wireless_ReadStatusReg(uint8_t *data, uint8_t ReadAddr)
{
	wireless_ReadReg(data, ReadAddr, 1, STATUS_REGISTER);
}

void wireless_ReadConfigRegister(uint8_t *data, uint8_t StartAddr, uint8_t NumBytesToRead)
{
	wireless_ReadReg(data, StartAddr, NumBytesToRead, CONFIG_REGISTER);
}

void wireless_ReadRXFIFO(uint8_t *data)
{
	wireless_CS_LOW();
	
	wireless_SendByte(RX_FIFO | 0x80);
	*data = wireless_SendByte(DUMMY_BYTE);
   data++;
	
	wireless_SendByte(RX_FIFO | 0x80);
	*data = wireless_SendByte(DUMMY_BYTE);
  
	/* Set chip select High at the end of the transmission */ 
  wireless_CS_HIGH();
}

uint8_t wireless_WriteReg(uint8_t *byte, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  /* Loop while DR register in not emplty */
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

uint8_t wireless_CommandStrobe(uint8_t StrobeAddr)
{
	uint8_t chipStatusByte;
	
	wireless_CS_LOW();
	
	chipStatusByte = wireless_SendByte(StrobeAddr);
	
	wireless_CS_HIGH();
	
	return chipStatusByte;
}


void receiveAccData(uint8_t *data)
{
	wireless_ReadRXFIFO(data);
	
	uint8_t receivedData[4];
	
	receivedData[0] = data[0];
	receivedData[1] = data[1];
	
	osMutexWait(pitch_mutex, osWaitForever);
	pitch_angle = (int)(data[0]) - 90;
	osMutexRelease(pitch_mutex);
	
	osMutexWait(roll_mutex, osWaitForever);
	roll_angle = (int)(data[1]) - 90;
	osMutexRelease(roll_mutex);
}

int checkRXByteCount()
{
	int status;
	uint8_t data[2];
	uint8_t chipStatusByte;
	
	//chipStatusByte = wireless_CommandStrobe(START_RX);
	
	// Read the RX bytes available register
	wireless_ReadStatusReg(data, RXBYTES);
	
	// Make sure there is data in the FIFO but it is not overfilled
	if (data[0] >= 2 && data[0] < 255)
	{
		status = 1;
	}
	else if (data[0] >= 255)
	{
		// RX buffer is overflowed!! DO SOMETHING ABOUT IT, NOT SURE WHAT
	}
	else
	{
		status = 0;
	}
	
	return status;
}
