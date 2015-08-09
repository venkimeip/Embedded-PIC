#ifndef _RF_MODULE
#define _RF_MODULE

#define TRUE 1
#define FALSE 0
#define RFDEVICE_SLAVE_ID 2
#define RFDEVICE_PACKETLEN 5
#define RDDEVICE_CRC_MASK 0x80

#define RFDEVICE_PACKETLEN_POS 0
#define RFDEVICE_PACKETNUM_POS 1
#define RFDEVICE_SLAVE_ID_POS 2
#define RFDEVICE_COMMMAND_POS 3
#define RFDEVICE_DATA_POS 4
#define RDDEVICE_CRC_POS 6

#define PACKET_LEN	64


#define READ_TXBYTES 0xFA
#define READ_RXBYTES 0xFB
//assign values to the registers
//assign	registers	Val from rf studio
#define	CC_IOCFG2_value	0x29
#define	CC_IOCFG1_value	0x2E
#define	CC_IOCFG0D_value	0x06
#define	CC_FIFOTHR_value	0x07
#define	CC_SYNC1_value	0xD3
#define	CC_SYNC0_value	0x91
#define	CC_PKTLEN_value	0xFF
#define	CC_PKTCTRL1_value	0x04
#define	CC_PKTCTRL0_value	0x05
#define	CC_ADDR_value	0x00
#define	CC_CHANNR_value	0x03
#define	CC_FSCTRL1_value	0x08
#define	CC_FSCTRL0_value	0x00
#define	CC_FREQ2_value	0x5D
#define	CC_FREQ1_value	0x44
#define	CC_FREQ0_value	0xEC
#define	CC_MDMCFG4_value	0x86
#define	CC_MDMCFG3_value	0x83
#define	CC_MDMCFG2_value	0x03
#define	CC_MDMCFG1_value	0x23
#define	CC_MDMCFG0_value	0x3B
#define	CC_DEVIATN_value	0x44
#define	CC_MCSM2_value	0x07
#define	CC_MCSM1_value	0x33
#define	CC_MCSM0_value	0x18
#define	CC_FOCCFG_value	0x16
#define	CC_BSCFG_value	0x6C
#define	CC_AGCCTRL2_value	0x03
#define	CC_AGCCTRL1_value	0x40
#define	CC_AGCCTRL0_value	0x91
#define	CC_WOREVT1_value	0x87
#define	CC_WOREVT0_value	0x6B
#define	CC_WORCTRL_value	 0xF8
#define	CC_FREND1_value	0x56
#define	CC_FREND0_value	0x10
#define	CC_FSCAL3_value	0xA9
#define	CC_FSCAL2_value	0x0A
#define	CC_FSCAL1_value	0x00
#define	CC_FSCAL0_value	0x11
#define	CC_RCCTRL1_value	0x41
#define	CC_RCCTRL0_value	0x00
#define	CC_FSTEST_value	0x59
#define	CC_PTEST_value	0x7F
#define	CC_AGCTEST_value	 0x3F
#define	CC_TEST2_value	0x88
#define	CC_TEST1_value	0x31
#define	CC_TEST0_value	0x0B

//-------------------------------

#define SRES     0x30
#define SFSTXON  0x31
#define SXOFF    0x32
#define SCAL     0x33
#define SRX      0x34
#define STX      0x35
#define SIDLE    0x36
#define SAFC     0x37
#define SWOR     0x38
#define SPWD     0x39
#define SFRX     0x3A
#define SFTX     0x3B
#define SWORRST  0x3C
#define SNOP     0x3D

//


typedef enum{
	CRA_ALL=0,
	CRA_FIXED,
	CRA_FIXED_00,
	CRA_FIXED_00_FF,
}CC2500_RECV_ADDR;//
unsigned char CC2500_ReadReg(unsigned char addr);
void RF_Module_init(void);
void RF_Module_Txchar(unsigned char *Txdata,unsigned char Len);
unsigned char RF_Module_Rxchar(void);
unsigned char command(unsigned char a);
void CC2500_SetRecvAddr(CC2500_RECV_ADDR AddrMode,unsigned char SpecAddr);
void CC2500_Init(void);
unsigned char CC2500_WriteReg(unsigned char, unsigned char);
#define CC2500_SendSpiData command
#define CC2500_Select SPI_SS_Enable
#define CC2500_NoSelect SPI_SS_Disable
#define CC2500_WriteByte spi_TxByte
#define CC2500_ReadByte spi_TxByte

//----------------------------------------

//CC2500 Reg
#define CCxxx0_IOCFG2					0x00								// GDO2 output pin configuration
#define CCxxx0_IOCFG1       			0x01        						// GDO1 output pin configuration
#define CCxxx0_IOCFG0      				0x02        						// GDO0 output pin configuration
#define CCxxx0_FIFOTHR      			0x03        						// RX FIFO and TX FIFO thresholds
#define CCxxx0_SYNC1        			0x04        						// Sync word, high u8
#define CCxxx0_SYNC0        			0x05        						// Sync word, low u8
#define CCxxx0_PKTLEN       			0x06        						// Packet length
#define CCxxx0_PKTCTRL1     			0x07        						// Packet automation control
#define CCxxx0_PKTCTRL0     			0x08        						// Packet automation control
#define CCxxx0_ADDR         			0x09        						// Device address
#define CCxxx0_CHANNR       			0x0A        						// Channel number
#define CCxxx0_FSCTRL1      			0x0B        						// Frequency synthesizer control
#define CCxxx0_FSCTRL0      			0x0C        						// Frequency synthesizer control
#define CCxxx0_FREQ2        			0x0D        						// Frequency control word, high u8
#define CCxxx0_FREQ1        			0x0E        						// Frequency control word, middle u8
#define CCxxx0_FREQ0        			0x0F        						// Frequency control word, low u8
#define CCxxx0_MDMCFG4      			0x10        						// Modem configuration
#define CCxxx0_MDMCFG3      			0x11        						// Modem configuration
#define CCxxx0_MDMCFG2      			0x12        						// Modem configuration
#define CCxxx0_MDMCFG1      			0x13        						// Modem configuration
#define CCxxx0_MDMCFG0      			0x14        						// Modem configuration
#define CCxxx0_DEVIATN      			0x15        						// Modem deviation setting
#define CCxxx0_MCSM2        			0x16        						// Main Radio Control State Machine configuration
#define CCxxx0_MCSM1        			0x17        						// Main Radio Control State Machine configuration
#define CCxxx0_MCSM0        			0x18        						// Main Radio Control State Machine configuration
#define CCxxx0_FOCCFG       			0x19        						// Frequency Offset Compensation configuration
#define CCxxx0_BSCFG        			0x1A        						// Bit Synchronization configuration
#define CCxxx0_AGCCTRL2     			0x1B        						// AGC control
#define CCxxx0_AGCCTRL1     			0x1C        						// AGC control
#define CCxxx0_AGCCTRL0     			0x1D        						// AGC control
#define CCxxx0_WOREVT1      			0x1E        						// High u8 Event 0 timeout
#define CCxxx0_WOREVT0      			0x1F        						// Low u8 Event 0 timeout
#define CCxxx0_WORCTRL      			0x20        						// Wake On Radio control
#define CCxxx0_FREND1       			0x21        						// Front end RX configuration
#define CCxxx0_FREND0       			0x22        						// Front end TX configuration
#define CCxxx0_FSCAL3       			0x23        						// Frequency synthesizer calibration
#define CCxxx0_FSCAL2       			0x24        						// Frequency synthesizer calibration
#define CCxxx0_FSCAL1       			0x25        						// Frequency synthesizer calibration
#define CCxxx0_FSCAL0       			0x26        						// Frequency synthesizer calibration
#define CCxxx0_RCCTRL1      			0x27        						// RC oscillator configuration
#define CCxxx0_RCCTRL0      			0x28        						// RC oscillator configuration

//control reg
#define CCxxx0_FSTEST       			0x29        						// Frequency synthesizer calibration control
#define CCxxx0_PTEST        			0x2A        						// Production test
#define CCxxx0_AGCTEST      			0x2B        						// AGC test
#define CCxxx0_TEST2        			0x2C        						// Various test settings
#define CCxxx0_TEST1        			0x2D        						// Various test settings
#define CCxxx0_TEST0        			0x2E        						// Various test settings

// register setting
#define CCxxx0_SRES         			0x30        						// Reset chip.
#define CCxxx0_SFSTXON      			0x31        						// Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        									// If in RX/TX: Go to a wait state where only the synthesizer is
                                        									// running (for quick RX / TX turnaround).
#define CCxxx0_SXOFF        			0x32        						// Turn off crystal oscillator.
#define CCxxx0_SCAL         			0x33        						// Calibrate frequency synthesizer and turn it off
                                        									// (enables quick start).
#define CCxxx0_SRX          			0x34        						// Enable RX. Perform calibration first if coming from IDLE and
                                        									// MCSM0.FS_AUTOCAL=1.
#define CCxxx0_STX          			0x35        						// In IDLE state: Enable TX. Perform calibration first if
                                        									// MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        									// Only go to TX if channel is clear.
#define CCxxx0_SIDLE        			0x36        						// Exit RX / TX, turn off frequency synthesizer and exit
                                        									// Wake-On-Radio mode if applicable.
#define CCxxx0_SAFC         			0x37        						// Perform AFC adjustment of the frequency synthesizer
#define CCxxx0_SWOR         			0x38        						// Start automatic RX polling sequence (Wake-on-Radio)
#define CCxxx0_SPWD         			0x39        						// Enter power down mode when CSn goes high.
#define CCxxx0_SFRX         			0x3A        						// Flush the RX FIFO buffer.
#define CCxxx0_SFTX         			0x3B        						// Flush the TX FIFO buffer.
#define CCxxx0_SWORRST      			0x3C        						// Reset real time clock.
#define CCxxx0_SNOP         			0x3D        						// No operation. May be used to pad strobe commands to two
                                        									// bytes for simpler software.
//information reg
#define CCxxx0_PARTNUM      			0x30
#define CCxxx0_VERSION      			0x31
#define CCxxx0_FREQEST      			0x32
#define CCxxx0_LQI          			0x33
#define CCxxx0_RSSI         			0x34
#define CCxxx0_MARCSTATE    			0x35
#define CCxxx0_WORTIME1     			0x36
#define CCxxx0_WORTIME0     			0x37
#define CCxxx0_PKTSTATUS    			0x38
#define CCxxx0_VCO_VC_DAC   			0x39
#define CCxxx0_TXBYTES      			0x3A
#define CCxxx0_RXBYTES      			0x3B


//function reg
#define CCxxx0_PATABLE      			    0x3E         //set PA value
#define CCxxx0_TXFIFO_One       			0x3F
#define CCxxx0_TXFIFO_Muti                  0x7f
#define CCxxx0_RXFIFO_Muti                  0xff
#define CCxxx0_RXFIFO_one       			0xbF

#define WRITE_BURST     				0x40
#define READ_SINGLE     				0x80
#define READ_BURST      				0xC0

#define RFRXDBUFFSIZE				64									// 24
#define RFTXDBUFFSIZE					64									// 35

#endif
