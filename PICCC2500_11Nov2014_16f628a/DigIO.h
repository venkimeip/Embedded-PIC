#ifndef _DIG_IO
#define _DIG_IO

#define TRUE 1
#define FALSE 0

void init_DigIO(void);
unsigned char read_switchs(void);

void TX_LED_on(void);
void TX_LED_off(void);
void TX_LED_Toggle(void);
#endif
