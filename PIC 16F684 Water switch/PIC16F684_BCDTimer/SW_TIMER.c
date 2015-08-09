#include<htc.h>
#include "Timerh.h"
#include "SW_TIMER.h"

void init_SWTimer(void)
{
unsigned char counter=0;

	for (counter=0;counter <SW_TIMER_COUNT ; counter++)
	{
	TimerStart[counter]=0;
	TimerState[counter] =TIMER_STOPPED;
	TimerTimeOutVal[counter]=0;
	
	}


}

//---------------------------------------------------
void Start_Timer(unsigned char Timer_ID , unsigned int TimeoutVal)
{
TimerStart[Timer_ID] = Ref1ms_counter;
TimerState[Timer_ID] =TIMER_RUNNING;
TimerTimeOutVal[Timer_ID] =TimeoutVal;
}

//---------------------------------------------------
unsigned char GetTimer_State(unsigned char TimerID)
{
if ( TimerState[TimerID] == TIMER_RUNNING )
    {
		if( (Ref1ms_counter -TimerStart[TimerID]) > TimerTimeOutVal[TimerID] )
		TimerState[TimerID] =TIMER_EXPIRED;
	}
return TimerState[TimerID];
}
//---------------------------------------------------
void Stop_Timer(unsigned char TimerID) 
{
TimerState[TimerID] =TIMER_STOPPED;
}