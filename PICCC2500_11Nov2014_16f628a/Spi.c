#include <htc.h>
#include "Spi.h"
#include "RF_Module.h"

/*
MOSI -RA0
MISO -RA1
SCK -RA2
SS - RA3

0010
*/

void init_spi(void)
{

		TRISA =0x02;//Set MOSI,SCK,SS as output
	    PORTA =0x08;// Set SS to High

}

unsigned char spi_TxByte(unsigned char txchar)
{

	unsigned char received_ch=0,index;
	for(index=0; index <8;index++)
	{
		if(txchar & 0x80)
		{
			SPI_MOSI_SETHIGH();
		}
		else
		{
			SPI_MOSI_SETLOW();
		}

		SPI_SCK_SETHIGH();

		received_ch <<=1;
		 if (SPI_MISO_READ())
		 {
			 received_ch |=0x01;
		 }
		 txchar <<=1;

		 Delay_ms(5);
		 SPI_SCK_SETLOW();
		 Delay_ms(5);
	}
	return received_ch;
}



void SPI_SS_Enable(void)
{
	PORTA &= ~(0x08); // Select Device
}

void SPI_SS_Disable(void)
{
	PORTA |= (0x08); //Slave reset
}

void Delay_ms(unsigned int delayms)
{
	unsigned int x,y;
	for(y=0;y<delayms;y++)
	{
	for (x=0;x < 100;/*5000 */ x++);
	}
}

void SPI_MOSI_SETHIGH(void)
{
	PORTA |= 0x01;
}
void SPI_MOSI_SETLOW(void)
{
	PORTA &= ~0x01;
}
void SPI_SCK_SETLOW(void)
{
	PORTA &= ~0x04;
}
void SPI_SCK_SETHIGH(void)
{
	PORTA |= 0x04;
}

unsigned char SPI_MISO_READ(void)
{
	return (PORTA & 0x02);
}

