#ifndef _SW_TIMER
#define _SW_TIMER
#define SW_TIMER_COUNT 4

#define TIMER_0 0
#define TIMER_1 1
#define TIMER_2 2
#define TIMER_3 3

#define TIMER_RUNNING 1
#define TIMER_STOPPED 2
#define TIMER_EXPIRED 3


unsigned int TimerStart[SW_TIMER_COUNT];
unsigned char TimerState[SW_TIMER_COUNT];
unsigned int TimerTimeOutVal[SW_TIMER_COUNT];
void init_SWTimer(void);
void Start_Timer(unsigned char Timer_ID , unsigned int TimeoutVal);
unsigned char GetTimer_State(unsigned char TimerID);
void Stop_Timer(unsigned char TimerID);

#endif