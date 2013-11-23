#include <stdio.h>
#include "wireless.h"

int main()
{
	
	init_wireless_chip();
	
	uint8_t pBuffer[16]; 
	
	// Read partnum
	uint8_t address = 0x30;
	wireless_ReadReg(pBuffer, address, 1, STATUS_REGISTER);
	
	// Read version
	address = 0x31;
	wireless_ReadReg(pBuffer, address, 1, STATUS_REGISTER);

	// Read all the test registers
	wireless_ReadReg(pBuffer, TEST2, 3, CONFIG_REGISTER);
	
}




