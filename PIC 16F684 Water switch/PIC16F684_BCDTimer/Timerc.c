//Timer_C File
#define _LEGACY_HEADERS
#include <htc.h>
#include "Timerh.h"

void init_timer(void)

{
//use timer1 which is 16bit
 TMR1H = 0xFC;
 TMR1L =0x17;
 T1CON = 0x01; // Enable Timer1 and Internal Timer clk is FOsc/4 -> 1MHz
    
 TMR1IF=0; // Clear timer interrupt flag
 TMR1IE =1;// Enable timre interrupt
    

}


//---------------------------------------

static void interrupt isr(void)

{
// Timer 1ms isr
    if (TMR1IF)                          // A TMR1 interupt occurred

    {
	Ref1ms_counter++;
    }
  TMR1H = 0xFC;
  TMR1L =0x17; // Timer initial reload value
  TMR1IF=0;    // clear TMR1 interrupt flag

}
