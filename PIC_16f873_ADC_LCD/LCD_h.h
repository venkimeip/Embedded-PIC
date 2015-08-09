#ifndef LCD_H
#define LCD_H

#define LCD_LINE_1 (1)
#define LCD_LINE_2 (2)
#define _XTAL_FREQ 4000000 
extern void Lcd8_Cmd(char a);
extern Lcd8_Clear();
extern void Lcd8_Set_Cursor(char a, char b);
extern void Lcd8_Init();
extern void Lcd8_Write_Char(char a);
extern void Lcd8_Write_String(char *a);
extern void Lcd8_Shift_Right();
extern void Lcd8_Shift_Left();

#endif
