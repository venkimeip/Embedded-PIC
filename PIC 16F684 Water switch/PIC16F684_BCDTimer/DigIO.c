#include<htc.h>
#include "DigIO.h"

void init_DigIO(void)
{
CMCON0 = 7;//  Turn off Comparators
ANSEL = 0;//Disable ADCs

TRISC =0xEF;//RC4 -> Relay Out; All inputs
TRISA =0xFF;//All Inputs
PORTA =0;
PORTC=0;

}
//-----------------------------------------------------------
unsigned char Read_switch(void)
{
unsigned char retval=0,temp=0;
temp = PORTA;
temp &=0x0F;
temp = temp << 4;
retval = PORTC;
retval &=0x0F;


retval |=temp;


return retval; // out format => PORTA[3..0] : PORTC [3..0]
}

//-----------------------------------------------------------
void Set_Relay_on(void)
{
PORTC |= 0b00010000;// SET RC4 Relay
}
//-----------------------------------------------------------
void Set_Relay_off(void)
{
PORTC &= 0b11101111;// Clear RC4 Relay
}
//-----------------------------------------------------------
/*
void heater_on(void)
{
PORTC |= 0b00100000; // SET RC5 / Heater
}
//-----------------------------------------------------------
void heater_off(void)
{
PORTC &= 0b11011111; // Clear RC5 / Heater
}
//------------------------------------------------------------
*/