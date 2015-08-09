#include<htc.h>
#include "DigIO.h"

void init_DigIO(void)
{

/*
TRISA<5:0>: PORTA Tri-State Control bit
1 = PORTA pin configured as an input (tri-stated)
0 = PORTA pin configured as an output
*/
TRISA &= 0b11101111;//make RA4/ Alarm output
PORTA &= 0x11101111;// Clear RA4/ Alarm

TRISC &= 0b11011111; //make RC5 / heater output
PORTC &= 0b11011111; // Clear RC5 / Heater

TRISA |= 0b00100000;//make RA5/ Switch input
PORTA &= 0b11011111;// Clear Switch input

}
//-----------------------------------------------------------
unsigned char read_pressure_switch(void)
{
unsigned char ret_val=0;
ret_val = PORTA;

ret_val &=0b00100000;//make RA5/ Switch input
		if(ret_val)
		{
		ret_val = FALSE;
		}
		else
		{
		ret_val = TRUE;
		}

return ret_val;
}

//-----------------------------------------------------------
void alarm_on(void)
{
PORTA |= 0b00010000;// SET RA4/ Alarm
}
//-----------------------------------------------------------
void alarm_off(void)
{
PORTA &= 0b11101111;// Clear RA4/ Alarm
}
//-----------------------------------------------------------
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