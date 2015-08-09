#include<htc.h>
#include "Adch.h"

void init_adc(void)
{
   TRISA |= 0x03;//make adc channels input
   CMCON0 = 7;                //  Turn off Comparators
   ANSEL = ADC_INPUTS;            // AN0 and AN1 is ADC input
ADCON1 = 0x10;			//  run oscillatr as 8 x prescalar   
//ADCON0 |= (Channel <<2);// Set ADC Channel
ADCON0 = 0x01;			//  Left justify, Use Vdd, No Channel , Do not start, Turn on
   
//GODONE = 1;//Start ADC operation
}


unsigned char Read_Adc(unsigned char Channel)
{

ADCON0 &= 0xE3; // Clear Channel field
ADCON0 |= (Channel <<2);// Set ADC Channel
adc_delay(100);
GODONE = 1;//Start ADC operation
while(GODONE == 1 );

return ADRESH;
 // MSB 8 bits of ADC REsult are returned
}

unsigned char Read_Adc_E0(void)

{
unsigned char ret_val, temp;
temp=Read_Adc(AN0);

		if(temp >= ADC_Cutoff_E0_MIN)
		{
		ret_val = E0_E1_SHORT;
		}
		else /*if(temp <= ADC_Cutoff_E0_MIN)*/
		{
		ret_val = E0_E1_OPEN;
		}
	

return ret_val;
}
//----------------------------------------------------------------
unsigned char Read_Adc_E1(void)
{
unsigned char ret_val, temp;
temp=Read_Adc(AN1);

		if(/*(temp <= ADC_Cutoff_E1_MAX) && */(temp >= ADC_Cutoff_E1_MIN))
		{
		ret_val = TRUE;
		}
		else
		{
		ret_val = FALSE;
		}

return ret_val;

}

void adc_delay(unsigned char x)
{
unsigned char y;
for(y=0;y<x;y++)
{
;
}

}
