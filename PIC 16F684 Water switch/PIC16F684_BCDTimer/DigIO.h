#ifndef _DIG_IO
#define _DIG_IO

#define TRUE 1
#define FALSE 0

void init_DigIO(void);
unsigned char Read_switch(void);
void Set_Relay_on(void);
void Set_Relay_off(void);
#endif
