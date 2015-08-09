#define _LEGACY_HEADERS
#include <htc.h>
#include "Timerh.h"
#include "Spi.h"
#include "DigIO.h"
#include "SW_TIMER.h"
#include "RF_Module.h"

__CONFIG(INTIO & WDTDIS & PWRTEN & MCLRDIS & UNPROTECT \
 & UNPROTECT & BORDIS );

unsigned char temp;;

void main(void)
{

		init_DigIO();
	  	init_timer();
	   	init_SWTimer();   
     	init_spi();
		CC2500_Init();
// Enable peripherial interrupts and start processing
     PEIE = 1; // Enable peripheral interrupt
     GIE = 1; // Enable global interrupt
 Start_Timer(TIMER_0,1000); 
unsigned char tempcounter;

while (1)
	{
if(GetTimer_State(TIMER_0) == TIMER_EXPIRED)
{
Start_Timer(TIMER_0,250);
RF_Module_Rxchar();
TX_LED_Toggle();
}



 // While ends
}
}
