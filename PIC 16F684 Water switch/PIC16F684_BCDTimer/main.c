#define _LEGACY_HEADERS
#include <htc.h>
#include "Timerh.h"
#include "DigIO.h"
#include "SW_TIMER.h"

__CONFIG(INTIO & WDTDIS & PWRTEN & MCLRDIS & UNPROTECT \
  & UNPROTECT & BORDIS & IESODIS & FCMDIS);


unsigned char Elapsed_Secs=0;
unsigned char Elapsed_Mins=0;
unsigned char Elapsed_Hours=0;
unsigned char Input_Time=0;
unsigned char Time_Sec=0,Time_Min=0,Time_Hour=0;
void main(void)
{

		init_DigIO();
	  	init_timer();
	   	
	
		init_SWTimer();   
     // Enable peripherial interrupts and start processing
     PEIE = 1; // Enable peripheral interrupt
     GIE = 1; // Enable global interrupt
 Start_Timer(TIMER_0,10); 
unsigned char tempcounter;
//Switch Off alarm and heater;
Set_Relay_off();
Input_Time =Read_switch();
while (1)
	{

if (GetTimer_State(TIMER_0 ==TIMER_EXPIRED))
{
 Start_Timer(TIMER_0,1000); // Call every 1000ms cyclic timer
Time_Sec++;
Elapsed_Secs++;
	if(Time_Sec >59)
	{
	Time_Min++;
	Elapsed_Mins++;
	Time_Sec=0;
	
		if(Time_Min>59)
		{
		Time_Hour++;
		Elapsed_Hours++;
		Time_Min=0;
			if(Time_Hour >23)
			{
			Time_Hour=0;
			}
				
		}
	}
//----------------------------------------------------------------------------------------
}

if(Elapsed_Mins >= Input_Time)
{
Set_Relay_on();
}	



 

// While ends
}
}