#include<htc.h>
#include "DigIO.h"
#include "LCD_h.h"
void init_DigIO(void)
{
//CMCON0 = 7;//  Turn off Comparators
//OSCCON= 0x60;
ANSEL = 0x1C;//Enable ADCs
ANSELH=0;
C1ON=0;
C2ON=0;
TRISC =0x00;//All Outputs to LCD
PORTC=0x00;

TRISB =0x00;//All out, except RB2 -> SEL_SW
PORTB =0x00;

TRISA =0x2C;//
//PORTA =0x00;
// Init ADC

ADCS0=1;
ADON=1;
ADFM=1;
}
//-----------------------------------------------------------
unsigned char Read_switch(void)
{
unsigned char retval=0;
retval = PORTB;
retval &=0x04;// extract RB2
retval >>= 2;

return retval; // out format => PORTA[3..0] : PORTC [3..0]
}

//-----------------------------------------------------------
void Set_LCD_RS_on(void)
{
PORTB |= 0b00000001;// SET RB0
}
//-----------------------------------------------------------
void Set_LCD_RS_off(void)
{
PORTB &= 0b11111110;// Clear RB0
}
//-----------------------------------------------------------

void Set_LCD_EN_on(void)
{
PORTB |= 0b00000010; // SET RB1
}
//-----------------------------------------------------------
void Set_LCD_EN_off(void)
{
PORTB &= 0b11111101; // Clear RB1
}
//------------------------------------------------------------
void Lcd8_Port(char a)
{
	PORTC=a;
}

unsigned int Read_Adc(unsigned char Channel)
{

ADCON0 &= 0xE3; // Clear Channel field
ADCON0 |= (Channel <<2);// Set ADC Channel
__delay_ms(30);
GODONE = 1;//Start ADC operation
while(GODONE == 1 );

return ((ADRESH << 8) | ADRESL );
 // MSB 8 bits of ADC REsult are returned
}