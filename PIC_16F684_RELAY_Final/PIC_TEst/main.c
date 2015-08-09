#define _LEGACY_HEADERS
#include <htc.h>
#include "Timerh.h"
#include "Adch.h"
#include "DigIO.h"
#include "SW_TIMER.h"

__CONFIG(INTIO & WDTDIS & PWRTEN & MCLRDIS & UNPROTECT \
  & UNPROTECT & BORDIS & IESODIS & FCMDIS);
unsigned char WaterSensed_State=E0_E1_OPEN;
unsigned char WaterSensed_PrevState=E0_E1_OPEN;
unsigned char Switch_State=FALSE;
unsigned char Switch_PrevState=FALSE;
unsigned char pressuresw_Flag =0;
void main(void)
{

		init_DigIO();
	  	init_timer();
	   	
		init_adc();	   ////
		init_SWTimer();   
     // Enable peripherial interrupts and start processing
     PEIE = 1; // Enable peripheral interrupt
     GIE = 1; // Enable global interrupt
 Start_Timer(TIMER_3,10); 
unsigned char tempcounter;
//Switch Off alarm and heater;
alarm_on();
heater_off();
while (1)
	{


if (GetTimer_State(TIMER_3) ==TIMER_EXPIRED)
{
 Start_Timer(TIMER_3,10); // Call every 10ms cyclic timer

if(Read_Adc_E1() == TRUE)//true
{

WaterSensed_State = Read_Adc_E0();
/*

if(WaterSensed_State == E0_E1_SHORT)
{
	alarm_on();
	heater_on();

}
else
{
	alarm_off();
	heater_off();


}
*/

				
	            
			//-------------------------------------------------------------------------------------
				if ((WaterSensed_PrevState == E0_E1_SHORT  ) && ( WaterSensed_State == E0_E1_OPEN ))
				{
				Start_Timer(TIMER_0,5000); // For 5 Seconds
                pressuresw_Flag = FALSE;
				}
				else if (GetTimer_State(TIMER_0) ==TIMER_EXPIRED)
				{
				alarm_on();
				heater_off();
	         
				Stop_Timer(TIMER_0);
				
				}
			//-------------------------------------------------------------------------------------
				
				 
		 

	

//-------------------------------------------------------------------------------------
				if ((WaterSensed_PrevState == E0_E1_OPEN )  && ( WaterSensed_State == E0_E1_SHORT ))
			{
				Start_Timer(TIMER_1,5000);// For 5 Seconds
				}
			else  if (GetTimer_State(TIMER_1) ==TIMER_EXPIRED)
				{


				alarm_off();
				pressuresw_Flag = TRUE;
				Stop_Timer(TIMER_1);
				
				}

WaterSensed_PrevState =WaterSensed_State;
			//-------------------------------------------------------------------------------------
			
			
				if (E0_E1_UNKNOWN == WaterSensed_State) //ADC E0 is inbetween 1 and 2 Volts which is error case;
				{
					alarm_on();
					heater_off();
				
				}

			// Delay 2 sec
			//------------Pressure switch case----true---------------------------------------------------------------------
			
if (pressuresw_Flag)
  {
			Switch_State = read_pressure_switch();
			if ((Switch_PrevState == FALSE )&& (Switch_State == TRUE))
			{
				Start_Timer(TIMER_2,2000);
			
			}

			if ((GetTimer_State(TIMER_2) ==TIMER_EXPIRED) &&  (Switch_State == TRUE))		
			{
			heater_on();
			alarm_off();
			}
		
		
			 if(Switch_State == FALSE)
				{
				Stop_Timer(TIMER_2);
				heater_off();
			
				}
   }
		

			//----------------------------------------------------------------------------------------

	Switch_PrevState=Switch_State;
}

	else	{ // E1 voltage is  other than  1.25
		alarm_on();
		heater_off();
		}



 // While ends
}
}
}