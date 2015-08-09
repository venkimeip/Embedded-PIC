#include<htc.h>
#include "LCD_h.h"
#include "DigIO.h"
// prototypes
void Lcd8_Cmd(char a);
Lcd8_Clear();
void Lcd8_Set_Cursor(char a, char b);
void Lcd8_Init();
void Lcd8_Write_Char(char a);
void Lcd8_Write_String(char *a);
void Lcd8_Shift_Right();
void Lcd8_Shift_Left();


void Lcd8_Cmd(char a)
{ 
 Set_LCD_RS_off();             // => RS = 0
  Lcd8_Port(a);             //Data transfer
  Set_LCD_EN_on();             // => E = 1
  __delay_ms(5);
 Set_LCD_EN_off();            // => E = 0
}

Lcd8_Clear()
{
	  Lcd8_Cmd(1);
}

void Lcd8_Set_Cursor(char a, char b)
{
	if(a == 1)
	  Lcd8_Cmd(0x80 + b);
	else if(a == 2)
		Lcd8_Cmd(0xC0 + b);
}

void Lcd8_Init()
{
	Lcd8_Port(0x00);
	Set_LCD_RS_off(); 
	__delay_ms(25);
	///////////// Reset process from datasheet /////////
  Lcd8_Cmd(0x30);
__delay_ms(5);
  Lcd8_Cmd(0x30);
	__delay_ms(15);
  Lcd8_Cmd(0x30);
  /////////////////////////////////////////////////////
  Lcd8_Cmd(0x38);    //function set
  Lcd8_Cmd(0x0C);    //display on,cursor off,blink off
  Lcd8_Cmd(0x01);    //clear display
  Lcd8_Cmd(0x06);    //entry mode, set increment
}

void Lcd8_Write_Char(char a)
{
  Set_LCD_RS_on();             // => RS = 1
   Lcd8_Port(a);             //Data transfer
   Set_LCD_EN_on();             // => E = 1
  __delay_ms(4);
   Set_LCD_EN_off();          // => E = 04
}

void Lcd8_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	 Lcd8_Write_Char(a[i]);
}

void Lcd8_Shift_Right()
{
	Lcd8_Cmd(0x1C);
}

void Lcd8_Shift_Left()
{
	Lcd8_Cmd(0x18);
}
//End LCD 8 Bit Interfacing Functions
