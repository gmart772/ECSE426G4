/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 ***************************************************************/

#ifndef SMARTRF_CC2500_H
#define SMARTRF_CC2500_H

#define SMARTRF_RADIO_CC2500

// Value to program
#define SMARTRF_SETTING_FSCTRL1    0x0C//0x12 //Frequency offset = 457kHz
#define SMARTRF_SETTING_FSCTRL0    0x00
#define SMARTRF_SETTING_FREQ2      0x5D // Carrier Frequency is 2.433GHz + 32 MHz
#define SMARTRF_SETTING_FREQ1      0x94
#define SMARTRF_SETTING_FREQ0      0x02
#define SMARTRF_SETTING_MDMCFG4    0x0E //0x2D // BW of channel = 541.666kHz
#define SMARTRF_SETTING_MDMCFG3    0x3B // Baud Rate = 125kb
#define SMARTRF_SETTING_MDMCFG2    0x73 //0xF3 // Disable digital DC blocking filter before demodulator, MSK modulation, 16/16 sync word bits detected
#define SMARTRF_SETTING_MDMCFG1    0x42 //0x22
#define SMARTRF_SETTING_MDMCFG0    0xF8 // Default Channel Spacing of 200kHz
#define SMARTRF_SETTING_CHANNR     0x00 // Channel 0
#define SMARTRF_SETTING_DEVIATN    0x00 //0x01 // 1785kHz
#define SMARTRF_SETTING_FREND1     0xB6
#define SMARTRF_SETTING_FREND0     0x10
#define SMARTRF_SETTING_MCSM0      0x18 // Automatically calibrate When going from IDLE to RX or TX (or FSTXON) check CC2500 datasheet
#define SMARTRF_SETTING_FOCCFG     0x1D // check datasheet
#define SMARTRF_SETTING_BSCFG      0x1C
#define SMARTRF_SETTING_AGCCTRL2   0xC7
#define SMARTRF_SETTING_AGCCTRL1   0x40 //0x00
#define SMARTRF_SETTING_AGCCTRL0   0xB0
#define SMARTRF_SETTING_FSCAL3     0xEA
#define SMARTRF_SETTING_FSCAL2     0x0A
#define SMARTRF_SETTING_FSCAL1     0x00
#define SMARTRF_SETTING_FSCAL0     0x19 //0x11
#define SMARTRF_SETTING_FSTEST     0x59
#define SMARTRF_SETTING_TEST2      0x88
#define SMARTRF_SETTING_TEST1      0x31
#define SMARTRF_SETTING_TEST0      0x0B
#define SMARTRF_SETTING_FIFOTHR    0x07
#define SMARTRF_SETTING_IOCFG2     0x29
#define SMARTRF_SETTING_IOCFG0D    0x06
#define SMARTRF_SETTING_PKTCTRL1   0x04
#define SMARTRF_SETTING_PKTCTRL0   0x04 //0x05 // Fixed Packet Length (0x05)
#define SMARTRF_SETTING_ADDR       0x00 // Global Broadcast Address
#define SMARTRF_SETTING_PKTLEN     0x02 // Packet Length of 10bytes (0xFF)

// Address to program values in to
#define IOCFG2  					0x00
#define IOCFG0						0x01

#define FIFOTHR 					0x03

#define PKTLEN  					0x06
#define PKTCTRL1					0x07
#define PKTCTRL0					0x08
#define ADDR    					0x09
#define CHANNR						0x0A
#define FSCTRL1						0x0B
#define FSCTRL0						0x0C
#define FREQ2							0x0D
#define FREQ1							0x0E
#define FREQ0							0x0F
#define	MDMCFG4						0x10
#define MDMCFG3						0x11
#define MDMCFG2						0x12
#define MDMCFG1						0x13
#define MDMCFG0						0x14
#define DEVIATN 					0x15

#define MCSM0   					0x18
#define FOCCFG  					0x19
#define BSCFG   					0x1A
#define AGCCTRL2					0x1B
#define AGCCTRL1					0x1C
#define AGCCTRL0					0x1D

#define FREND1  					0x21
#define FREND0  					0x22
#define FSCAL3  					0x23
#define FSCAL2  					0x24
#define FSCAL1  					0x25
#define FSCAL0  					0x26

#define FSTEST  					0x29

#define TEST2   					0x2C
#define TEST1   					0x2D
#define TEST0   					0x2E


// #define IOCFG0D 					Should be either 0x01 for IOCFGG1 GDO1 or 0x02 for IOCFG0 GDO0



#endif

