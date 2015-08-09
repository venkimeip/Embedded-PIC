//#include <avr/io.h>
#include <htc.h>
#include "RF_Module.h"
#include "Spi.h" 
#include "DigIO.h"
unsigned char bTempRxBuf[10];
unsigned char bTxBuf[10];
const unsigned char paTable_CC2500[8]={0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe};  //PA value
/**
// PA value
**/



unsigned char CC_rfSettings[0x2F]=
{
CC_IOCFG2_value,
CC_IOCFG1_value,
CC_IOCFG0D_value,
CC_FIFOTHR_value,
CC_SYNC1_value,
CC_SYNC0_value,
CC_PKTLEN_value,
CC_PKTCTRL1_value,
CC_PKTCTRL0_value,
CC_ADDR_value,
CC_CHANNR_value,
CC_FSCTRL1_value,
CC_FSCTRL0_value,
CC_FREQ2_value,
CC_FREQ1_value,
CC_FREQ0_value,
CC_MDMCFG4_value,
CC_MDMCFG3_value,
CC_MDMCFG2_value,
CC_MDMCFG1_value,
CC_MDMCFG0_value,
CC_DEVIATN_value,
CC_MCSM2_value,
CC_MCSM1_value,
CC_MCSM0_value,
CC_FOCCFG_value,
CC_BSCFG_value,
CC_AGCCTRL2_value,
CC_AGCCTRL1_value,
CC_AGCCTRL0_value,
CC_WOREVT1_value,
CC_WOREVT0_value,
CC_WORCTRL_value,
CC_FREND1_value,
CC_FREND0_value,
CC_FSCAL3_value,
CC_FSCAL2_value,
CC_FSCAL1_value,
CC_FSCAL0_value,
CC_RCCTRL1_value,
CC_RCCTRL0_value,
CC_FSTEST_value,
CC_PTEST_value,
CC_AGCTEST_value,
CC_TEST2_value,
CC_TEST1_value,
CC_TEST0_value
};


void RF_Module_Txchar(unsigned char *Txdata,unsigned char Len)
{
unsigned char i,status;
     //flush tx FIFO
    command(SIDLE);    //turn CC2500 into idle mode
	command(SFTX); 
	command(SFRX); 
//	Delay_ms(20);   
	
				status = command(SNOP); // command to receive data wirelessly
				//Uart_TxChar(status);
        if((status & 0x20) != 0x20)// If not receiving then tx
		{ 

	SPI_SS_Enable();

	//Delay_ms(20);
	while(SPI_MISO_READ()== TRUE);
	spi_TxByte(CCxxx0_TXFIFO_Muti);
	spi_TxByte(Len);
	//Uart_TxChar(Len);
	for(i=0;i<Len;i++) // 
	{
	spi_TxByte((unsigned char)*(Txdata+i));
//	Uart_TxChar((unsigned char)*(Txdata+i));
	}
	SPI_SS_Disable();
	command(STX);  //command to send data in tx FIFO wirelessly

	}
}

unsigned char RF_Module_Rxchar(void)
{
unsigned char i,rxbytes;
unsigned char NewPacketReceived=0,ValidPacketReceived=0;
static unsigned char OldPacketNum=0,Packetcounter=0;
unsigned char status;	
				status = command(SNOP); // command to receive data wirelessly
				//Uart_TxChar(status);
        if((status & 0x20) != 0x20)// If not transmitting then receive
		{ 
		         command(SRX); 
	    		 //while((PINB & (1<<DD_GDO0)) == FALSE);// Wait for GDO0

				rxbytes=CC2500_ReadReg(READ_RXBYTES);
				SPI_SS_Enable();
				while(SPI_MISO_READ()== TRUE);
				spi_TxByte(0xFF); // rx FIFO address burst mode
				for(i=0;i<rxbytes;i++)	   
				{
			
				 bTempRxBuf[i]=spi_TxByte(0x00); // data byte1
				 //Uart_TxChar(bTempRxBuf[i]);
				}			
				SPI_SS_Disable();



				//---------Packet Process-------------
			// If new packet is received and packetlength is as expected
				//if((bTempRxBuf[RDDEVICE_CRC_POS] & RDDEVICE_CRC_MASK)  == RDDEVICE_CRC_MASK)// CRC OK

					if( (bTempRxBuf[RFDEVICE_PACKETNUM_POS] != OldPacketNum) && (bTempRxBuf[RFDEVICE_PACKETLEN_POS] == RFDEVICE_PACKETLEN))
					{
					NewPacketReceived = TRUE;
					OldPacketNum =bTempRxBuf[RFDEVICE_PACKETNUM_POS];
					}

				
					if(NewPacketReceived == TRUE)
					{	
					
						NewPacketReceived= FALSE;
				
						if(bTempRxBuf[RFDEVICE_SLAVE_ID_POS] == RFDEVICE_SLAVE_ID) 
						{
						ValidPacketReceived = TRUE;
					
						}
				
					}
					
					if(ValidPacketReceived == TRUE)
					{
					ValidPacketReceived = FALSE;
					bTxBuf[RFDEVICE_PACKETLEN_POS] =RFDEVICE_PACKETLEN;
					bTxBuf[RFDEVICE_PACKETNUM_POS] = bTempRxBuf[RFDEVICE_PACKETNUM_POS];
					bTxBuf[RFDEVICE_SLAVE_ID_POS] = RFDEVICE_SLAVE_ID;
					bTxBuf[RFDEVICE_COMMMAND_POS] =bTempRxBuf[RFDEVICE_COMMMAND_POS];
					
							switch(bTempRxBuf[RFDEVICE_COMMMAND_POS])
							{
							case 0x01 :	bTxBuf[RFDEVICE_DATA_POS] =read_switchs(); break;
					
							case 0x02 :	bTxBuf[RFDEVICE_DATA_POS] =0; break;

							case 0x03 :	bTxBuf[RFDEVICE_DATA_POS] =0; break;
						
							case 0x04 :	bTxBuf[RFDEVICE_DATA_POS] =0; break;

							default: 	bTxBuf[RFDEVICE_DATA_POS] =0; break;	
			
							}	
					
				//_delay_ms(50);
					TX_LED_Toggle();
					RF_Module_Txchar(bTxBuf+1,RFDEVICE_PACKETLEN); // Send Response

					//_delay_ms(250);
					
					//RF_Module_Txchar(bTxBuf+1,RFDEVICE_PACKETLEN); // Send Response

					}
					
					



		
		}


}//End of function



unsigned char command(unsigned char a) // give commands to CC
{
unsigned char val;
SPI_SS_Enable();
	while(SPI_MISO_READ()== TRUE); // Check miso is high
val =spi_TxByte(a);
SPI_SS_Disable();
return val;
}


void Delay_us(unsigned int nCount) // Not calibrated
{
	unsigned int i;

  	for(; nCount != 0; nCount--)
  		for(i=12; i != 0; i--);
}

void Delay_ms1(unsigned int nCount)// Not calibrated
{
	unsigned int i;

	for(; nCount != 0; nCount--)
  		for(i=120; i != 0; i--);
}


//reset cc2500
void CC2500_Reset(void) //Verified By venki
{
	CC2500_SendSpiData(CCxxx0_SIDLE);

	Delay_ms(20);

	CC2500_Select();

	Delay_ms(20);

	CC2500_NoSelect();

	Delay_ms(40);

	CC2500_SendSpiData(CCxxx0_SRES);
}
// read cc2500 register
unsigned char CC2500_ReadReg(unsigned char addr)
{
	unsigned char value;

	CC2500_Select();
		while(SPI_MISO_READ()== TRUE);
	Delay_ms(20);
	CC2500_WriteByte(addr|0x80);
	Delay_ms(20);
	value = CC2500_ReadByte(0x00);
    CC2500_NoSelect();
	Delay_ms(20);
	return value;
}
//wirte cc2500 register
unsigned char CC2500_WriteReg(unsigned char addr, unsigned char value)
{
unsigned char i=0;
repeat:	Delay_ms(20);
	CC2500_Select();
		while(SPI_MISO_READ()== TRUE);
	addr &= 0x7F;
	Delay_ms(20);
	CC2500_WriteByte(addr);
	Delay_ms(20);
	CC2500_WriteByte(value);
	Delay_ms(20);
	CC2500_NoSelect();

	if (CC2500_ReadReg(addr) == value )
	{
	return 0;
	}
	else
	{
			if(i++ < 5)
			goto repeat;
			else
			return 1;//
	}


}


void CC2500_SetRxd(void) // Verified by venki
{
	CC2500_SendSpiData(CCxxx0_SIDLE);
	CC2500_SendSpiData(CCxxx0_SIDLE);
	Delay_ms(20);
	CC2500_SendSpiData(CCxxx0_SFRX);
	CC2500_SendSpiData(CCxxx0_SFRX);
	Delay_ms(20);
	CC2500_SendSpiData(CCxxx0_SRX);
	CC2500_SendSpiData(CCxxx0_SRX);
	Delay_ms(20);

}

unsigned char CC2500_SendPacket(unsigned char *txBuffer, unsigned char size) // Verified by venki
{
	unsigned char i =0;

	CC2500_SendSpiData(CCxxx0_SIDLE);
	CC2500_SendSpiData(CCxxx0_SFTX);//SFRX SFTX

	CC2500_Select();
	CC2500_WriteByte(CCxxx0_TXFIFO_Muti);
    for(i=0;i<size;i++)
    {
    	CC2500_WriteByte(txBuffer[i]);
	}
	CC2500_NoSelect();

	CC2500_SendSpiData(CCxxx0_STX);
	//while(!GDO0_IN());   //wait high
	//while(GDO0_IN());    //wait low ,end send

	//Delay_ms(10);
    return 0;
}

unsigned char CC2500_ReadStatus(unsigned char addr)
{
	unsigned char  value;
/*
	CC2500_Select();
	addr  |= READ_BURST;

	CC2500_WriteByte(addr);
	value = CC2500_ReadByte();

	CC2500_NoSelect();

	return value;
	*/
}

// receive a paket data form cc2500
unsigned char CC2500_ReceivePacket(unsigned char *rxBuffer)
{
	unsigned char status;
	unsigned char LEN=0,i=0;

    status =CC2500_ReadStatus(CCxxx0_RXBYTES);          //RX FIFO
    if((status & 0x7F)==0x00)
    {
        status = CC2500_ReadStatus(CCxxx0_MARCSTATE);
        if((status!=0x0D)&&(status!=0x08))
        {
        	CC2500_SetRxd();
        }
        return 0;
    }


}

void CC2500_RfSettings(void)
{
	unsigned char Error_Counter=0;

#if 1
		if (CC2500_WriteReg(CCxxx0_FSCTRL1,	0x09)) Error_Counter++;	// 0x0c
		if (CC2500_WriteReg(CCxxx0_FSCTRL0,	0x00)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_FREQ2,	0x5D)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_FREQ1,	0x93)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_FREQ0,	0xB1)) Error_Counter++;
//#define _10k
#ifdef _10k
		if (CC2500_WriteReg(CCxxx0_MDMCFG4,	0x78)) Error_Counter++; //0x78-10k   0x86
		if (CC2500_WriteReg(CCxxx0_MDMCFG3,	0x93)) Error_Counter++; //0x93-10k   0x83
//		CC2500_WriteReg(CCxxx0_MDMCFG2,	0x70);
		if (CC2500_WriteReg(CCxxx0_MDMCFG2,	0x03)) Error_Counter++; //0x03-10k  0x03
		if (CC2500_WriteReg(CCxxx0_MDMCFG1,	0x22)) Error_Counter++; //0x22-10k	 0x22							// 0x22????
		if (CC2500_WriteReg(CCxxx0_MDMCFG0,	0xF8)) Error_Counter++; //0xf8        0xf8

#else
		if (CC2500_WriteReg(CCxxx0_MDMCFG4,	0x2D)) Error_Counter++; //0x78-10k   0x86
		if (CC2500_WriteReg(CCxxx0_MDMCFG3,	0x3B)) Error_Counter++; //0x93-10k   0x83
//		CC2500_WriteReg(CCxxx0_MDMCFG2,	0x70);
		if (CC2500_WriteReg(CCxxx0_MDMCFG2,	0x73)) Error_Counter++; //0x03-10k  0x03
		if (CC2500_WriteReg(CCxxx0_MDMCFG1,	0xA2)) Error_Counter++; //0x22-10k	 0x22							// 0x22????
		if (CC2500_WriteReg(CCxxx0_MDMCFG0,	0xF8)) Error_Counter++; //0xf8        0xf8
#endif

		if (CC2500_WriteReg(CCxxx0_CHANNR,	0x00)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_DEVIATN,	0x01)) Error_Counter++;	//0x44							// 00
		if (CC2500_WriteReg(CCxxx0_FREND1,	0x56)) Error_Counter++;								// 0xB6   56
		if (CC2500_WriteReg(CCxxx0_FREND0,	0x10)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_MCSM1,	0x00)) Error_Counter++;								// 0X00>NO CCA; 0X30>CCA   ?????
		if (CC2500_WriteReg(CCxxx0_MCSM0,	0x18)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_FOCCFG,	0x15)) Error_Counter++;								// 0x1D
		if (CC2500_WriteReg(CCxxx0_BSCFG,	0x6C)) Error_Counter++;								// 0x1c
		if (CC2500_WriteReg(CCxxx0_AGCCTRL2,	0x07)) Error_Counter++;								// 0xc3
		if (CC2500_WriteReg(CCxxx0_AGCCTRL1,	0x00)) Error_Counter++;								// cca=0x10
		if (CC2500_WriteReg(CCxxx0_AGCCTRL0,	0x91)) Error_Counter++;								// 0xb2
		if (CC2500_WriteReg(CCxxx0_FSCAL3,	0xEA)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_FSCAL2,	0x0A)) Error_Counter++;  //0x0a - 250k  0x06 --10k,0x08-2.4k
		if (CC2500_WriteReg(CCxxx0_FSCAL1,	0x00)) Error_Counter++;

		if (CC2500_WriteReg(CCxxx0_FSCAL0,	0x11)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_FSTEST,	0x59)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_TEST2,	0x8F)) Error_Counter++;								// 0x88
		if (CC2500_WriteReg(CCxxx0_TEST1,	0x21)) Error_Counter++;								// 0x31
		if (CC2500_WriteReg(CCxxx0_TEST0,	0x0B)) Error_Counter++;
		if (CC2500_WriteReg(CCxxx0_IOCFG2,	0x06)) Error_Counter++;	//29							// CCA=0x09:1=free   ??????
		if (CC2500_WriteReg(CCxxx0_IOCFG0,	0x06)) Error_Counter++;								//                  ?????
		if (CC2500_WriteReg(CCxxx0_PKTCTRL1,	0x00)) Error_Counter++;		//                      ??????
		if (CC2500_WriteReg(CCxxx0_PKTCTRL0,	0x04)) Error_Counter++;	//0x41 whiter+val	 //crc on 05						//                          ????
		if (CC2500_WriteReg(CCxxx0_ADDR,		0x00)) Error_Counter++;								//                     ?????
		if (CC2500_WriteReg(CCxxx0_PKTLEN,	PACKET_LEN)) Error_Counter++;//                      ??????
      // CC2500_ReadReg(CCxxx0_MDMCFG1);
#else
	if (CC2500_WriteReg(CCxxx0_IOCFG2,0x0B)) Error_Counter++;//0x0B,   // IOCFG2    GDO2 output pin configuration.
	if (CC2500_WriteReg(CCxxx0_IOCFG1,0x06)) Error_Counter++;   //IOCFG1
	if (CC2500_WriteReg(CCxxx0_IOCFG0,0x06)) Error_Counter++;  // IOCFG0   GDO0 output pin configuration.
	if (CC2500_WriteReg(CCxxx0_FIFOTHR,0x07)) Error_Counter++;   //FIFOTHR
	if (CC2500_WriteReg(CCxxx0_SYNC1,0xD3)) Error_Counter++;	//SYNC1 MSB
	if (CC2500_WriteReg(CCxxx0_SYNC0,0x91)) Error_Counter++;     //SYNC0 LSB
	if (CC2500_WriteReg(CCxxx0_PKTLEN,64)) Error_Counter++;   // PKTLEN    Packet length.
	if (CC2500_WriteReg(CCxxx0_PKTCTRL1,0x02)) Error_Counter++;   // PKTCTRL1  Packet automation control.
	if (CC2500_WriteReg(CCxxx0_PKTCTRL0,0x05)) Error_Counter++;  // PKTCTRL0  Packet automation control.
	if (CC2500_WriteReg(CCxxx0_ADDR,0x01)) Error_Counter++;  // ADDR      Device address.

if (CC2500_WriteReg(CCxxx0_CHANNR,0x00)) Error_Counter++;  // CHANNR    Channel number.
	if (CC2500_WriteReg(CCxxx0_FSCTRL1,0x07)) Error_Counter++;  // FSCTRL1   Frequency synthesizer control.
	if (CC2500_WriteReg(CCxxx0_FSCTRL0,0x00)) Error_Counter++;  // FSCTRL0   Frequency synthesizer control.
	if (CC2500_WriteReg(CCxxx0_FREQ2,0x5D)) Error_Counter++;  // FREQ2     Frequency control word, high u8.
	if (CC2500_WriteReg(CCxxx0_FREQ1,0x93)) Error_Counter++;  // FREQ1     Frequency control word, middle u8.
	if (CC2500_WriteReg(CCxxx0_FREQ0,0xB1)) Error_Counter++;  // FREQ0     Frequency control word, low u8.
	if (CC2500_WriteReg(CCxxx0_MDMCFG4,0x2D)) Error_Counter++;  // MDMCFG4   Modem configuration.
	if (CC2500_WriteReg(CCxxx0_MDMCFG3,0x3B)) Error_Counter++;  // MDMCFG3   Modem configuration.
	if (CC2500_WriteReg(CCxxx0_MDMCFG2,0x73)) Error_Counter++;  // MDMCFG2   Modem configuration.
	if (CC2500_WriteReg(CCxxx0_MDMCFG1,0x22)) Error_Counter++;  // MDMCFG1   Modem configuration.

	if (CC2500_WriteReg(CCxxx0_MDMCFG0,0xF8)) Error_Counter++;  // MDMCFG0   Modem configuration.
	if (CC2500_WriteReg(CCxxx0_DEVIATN,0x47)) Error_Counter++;  // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
	if (CC2500_WriteReg(CCxxx0_MCSM2,0x00)) Error_Counter++;   // MCSM2     Main Radio Control State Machine configuration.
	if (CC2500_WriteReg(CCxxx0_MCSM1,0x02)) Error_Counter++;   // MCSM1     Main Radio Control State Machine configuration.
	if (CC2500_WriteReg(CCxxx0_MCSM0,0x18)) Error_Counter++;   // MCSM0     Main Radio Control State Machine configuration.
	if (CC2500_WriteReg(CCxxx0_FOCCFG,0x1D)) Error_Counter++;  // FOCCFG    Frequency Offset Compensation Configuration.
	if (CC2500_WriteReg(CCxxx0_BSCFG,0x1C)) Error_Counter++;  // BSCFG     Bit synchronization Configuration.
	if (CC2500_WriteReg(CCxxx0_AGCCTRL2,0xC7)) Error_Counter++;  // AGCCTRL2  AGC control.
	if (CC2500_WriteReg(CCxxx0_AGCCTRL1,0x00)) Error_Counter++;  // AGCCTRL1  AGC control.
	if (CC2500_WriteReg(CCxxx0_AGCCTRL0,0xB2)) Error_Counter++;  // AGCCTRL0  AGC control.

	if (CC2500_WriteReg(CCxxx0_WOREVT1,0x00)) Error_Counter++;  // WOREVT1
    if (CC2500_WriteReg(CCxxx0_WOREVT0,0x00)) Error_Counter++;  // WOREVT0
    if (CC2500_WriteReg(CCxxx0_WORCTRL,0x00)) Error_Counter++;  // WORCTRL
    if (CC2500_WriteReg(CCxxx0_FREND1,0xB6)) Error_Counter++;  // FREND1    Front end RX configuration.
	if (CC2500_WriteReg(CCxxx0_FREND0,0x10)) Error_Counter++;  // FREND0    Front end RX configuration.
	if (CC2500_WriteReg(CCxxx0_FSCAL3,0xEA)) Error_Counter++;  // FSCAL3    Frequency synthesizer calibration.
	if (CC2500_WriteReg(CCxxx0_FSCAL2,0x0A)) Error_Counter++;  // FSCAL2    Frequency synthesizer calibration.
	if (CC2500_WriteReg(CCxxx0_FSCAL1,0x00)) Error_Counter++;  // FSCAL1    Frequency synthesizer calibration.
	if (CC2500_WriteReg(CCxxx0_FSCAL0,0x11)) Error_Counter++;  // FSCAL0    Frequency synthesizer calibration.
	if (CC2500_WriteReg(CCxxx0_RCCTRL1,0x00)) Error_Counter++;   //RCCTRL1

	if (CC2500_WriteReg(CCxxx0_RCCTRL0,0x00)) Error_Counter++;   //RCCTRL0
	if (CC2500_WriteReg(CCxxx0_FSTEST,0x59)) Error_Counter++;  // FSTEST    Frequency synthesizer calibration.
	if (CC2500_WriteReg(CCxxx0_PTEST,0x00)) Error_Counter++;   //PTEST
	//CC2500_WriteReg(CCxxx0_AGCTEST,0x00);  //AGCTEST
	//CC2500_WriteReg(CCxxx0_TEST2,0x88);  // TEST2     Various test settings.
	//CC2500_WriteReg(CCxxx0_TEST1,0x31);  // TEST1     Various test settings.
	//CC2500_WriteReg(CCxxx0_TEST0,0x0B);  // TEST0     Various test settings.
#endif

Uart_TxChar(0xAA);
Uart_TxChar(Error_Counter);
}
void CC2500_SetRecvAddr(CC2500_RECV_ADDR AddrMode,unsigned char SpecAddr)
{
	CC2500_WriteReg(CCxxx0_ADDR,SpecAddr);
	CC2500_WriteReg(CCxxx0_PKTCTRL1,AddrMode);

	CC2500_SetRxd();
}

void CC2500_Init(void)
{
	unsigned char i;
	//CC2500_Reset();
	//CC2500_RfSettings();
	//CC2500_SetRxd();
	RF_Module_init();

	CC2500_Select();
		while(SPI_MISO_READ()== TRUE);
	CC2500_WriteByte(CCxxx0_PATABLE|WRITE_BURST);
		for(i=0;i<8;i++)
		{
			CC2500_WriteByte(paTable_CC2500[i]);
		}
		CC2500_NoSelect();


}

void RF_Module_init(void)
{
	unsigned char i,ErrorCount;
	for(i=0x00;i<0x2F;i++)   // configure registers of CC2500
		{
	if( CC2500_WriteReg(i,CC_rfSettings[i])) ErrorCount++;
		}
	command(SIDLE);
	command(SFRX);
//SPI_SS_Enable();
//while(bit_is_set(PINB,DD_MISO));
//spi_TxByte(0x80);
//Uart_TxChar(0xAA);
	//for(i=0x00;i<0x2F;i++)   // configure registers of CC2500
	//	{
	//	Uart_TxChar(CC2500_ReadReg(i));// data byte
	//	}
	//	Uart_TxChar(0x55);
//SPI_SS_Disable();
}
