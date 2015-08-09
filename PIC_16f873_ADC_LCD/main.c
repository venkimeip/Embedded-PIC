#define _LEGACY_HEADERS
#include <htc.h>
#include "Timerh.h"
#include "DigIO.h"
#include "LCD_h.h"
#include "SW_TIMER.h"

//__CONFIG( WDTDIS & PWRTEN  & UNPROTECT \
//  & UNPROTECT & BORDIS & INTCLK & MCLRDIS  );
#define FOSC 4000000L
__CONFIG(INTIO/*XT*/ & WDTDIS & PWRTDIS & MCLRDIS & UNPROTECT & DUNPROTECT & \
  BORDIS & IESOEN & FCMDIS & LVPDIS & DEBUGEN);   // Address 0x2007
__CONFIG(BORV21);

unsigned char Elapsed_Secs=0;
unsigned char Elapsed_Mins=0;
unsigned char Elapsed_Hours=0;
unsigned char Input_Time=0;
unsigned char Time_Sec=0,Time_Min=0,Time_Hour=0;
unsigned int adc_result_an2=0;
unsigned char adc_result_an3=0;
unsigned char adc_result_an4=0;
unsigned int temp1,temp2,temp3;
void main(void)
{

		init_DigIO();
	  	init_timer();
	   	Lcd8_Init();
	
		init_SWTimer();   
     // Enable peripherial interrupts and start processing
     PEIE = 1; // Enable peripheral interrupt
     GIE = 1; // Enable global interrupt
 Start_Timer(TIMER_0,10); 
//unsigned char tempcounter;
//Switch Off alarm and heater;
//Input_Time =Read_switch();
//Lcd8_Set_Cursor(LCD_LINE_1,0);
//Lcd8_Write_String("Voltage ->");
Lcd8_Set_Cursor(LCD_LINE_1,0);
Lcd8_Write_String("Voltage:");

Lcd8_Set_Cursor(LCD_LINE_2,0);
Lcd8_Write_String("Current:");

//PORTC=0x80;
//TRISB=0x00;
while (1)
	{
//Lcd8_Set_Cursor(LCD_LINE_2,1);
//Lcd8_Write_Char(Time_Sec);
//PORTB++;
//PORTC ^=0x80;
if (GetTimer_State(TIMER_0 ==TIMER_EXPIRED))
{
//Display AN2
Lcd8_Set_Cursor(LCD_LINE_1,9);
adc_result_an2 = Read_Adc(ADC_AN3);
if(adc_result_an2 >10)
{
Lcd8_Write_Char('+');
}
else
{
Lcd8_Write_Char('-');
adc_result_an2 = Read_Adc(ADC_AN2);

}





adc_result_an2>>=1;
temp1=adc_result_an2/100;

//Lcd8_Set_Cursor(LCD_LINE_1,10);
Lcd8_Write_Char(temp1 | 0x30);

temp1=adc_result_an2/10;
temp1= temp1%10;
//Lcd8_Set_Cursor(LCD_LINE_2,11);
Lcd8_Write_Char(temp1 | 0x30);
Lcd8_Write_Char('.');
temp1= adc_result_an2%10;
//Lcd8_Set_Cursor(LCD_LINE_2,12);
Lcd8_Write_Char(temp1 | 0x30);
Lcd8_Write_Char('V');



//00000000000000000000000000000000000000000000000
// 4-20 ma
adc_result_an2 = Read_Adc(ADC_AN4);

#if 0
if(adc_result_an2 >2)
{
	adc_result_an2-=2;
}
adc_result_an2<<=2;
#endif
//adc_result_an2<<=2;
temp1=adc_result_an2/100;

Lcd8_Set_Cursor(LCD_LINE_2,10);
Lcd8_Write_Char(temp1 | 0x30);

temp1=adc_result_an2/10;
temp1= temp1%10;
//Lcd8_Set_Cursor(LCD_LINE_2,11);
Lcd8_Write_Char(temp1 | 0x30);
Lcd8_Write_Char('.');
temp1= adc_result_an2%10;
//Lcd8_Set_Cursor(LCD_LINE_2,12);
Lcd8_Write_Char(temp1 | 0x30);

Lcd8_Write_Char('m');
Lcd8_Write_Char('A');








//------------------------------------------------------------------
 Start_Timer(TIMER_0,2000); // Call every 1000ms cyclic timer

//----------------------------------------------------------------------------------------
}

	



 

// While ends
}
}