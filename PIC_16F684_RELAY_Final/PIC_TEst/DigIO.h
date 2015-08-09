#ifndef _DIG_IO
#define _DIG_IO

#define TRUE 1
#define FALSE 0

void init_DigIO(void);
unsigned char read_pressure_switch(void);
void alarm_on(void);
void heater_on(void);
void alarm_off(void);
void heater_off(void);
#endif
