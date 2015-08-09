#include<htc.h>
#include "DigIO.h"

void init_DigIO(void)
{
OPTION &=0x7F;// Enable Weak pullups for Switches
TRISB =0xF0;//RB0-RB3 -> Outputs ; RB4-RB7 -> Switch inputs ; 

}
//-----------------------------------------------------------
unsigned char read_switchs(void)
{
unsigned char ret_val=0;
ret_val = ~ PORTA;// Active low switches

ret_val &=0xF0;// Switch input

return ret_val;

}

//-----------------------------------------------------------
void TX_LED_on(void)
{
PORTB |= 0x01;//LED on RB0 
}

void TX_LED_off(void)
{
PORTB &= ~0x01;//LED on RB0 
}

void TX_LED_Toggle(void)
{
PORTB ^= 0x01;//LED on RB0 
}

//-----------------------------------------------------------
//--------------------------------------------------------