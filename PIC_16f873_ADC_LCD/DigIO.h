#ifndef _DIG_IO
#define _DIG_IO

#define TRUE 1
#define FALSE 0


#define ADC_AN2 0x02
#define ADC_AN3 0x03
#define ADC_AN4 0x04


void init_DigIO(void);
unsigned char Read_switch(void);

void Set_LCD_RS_on(void);
void Set_LCD_RS_off(void);
void Set_LCD_EN_on(void);
void Set_LCD_EN_off(void);
void Lcd8_Port(unsigned char a);
unsigned int Read_Adc(unsigned char Channel);
#endif
