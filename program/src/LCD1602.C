#include "lcd1602.h"
#include "delay.h"

void LCD1602WriteCommand(uchar command)
{
	LCD_RS = 0;
	LCD_DATA = command;
	DelayMs(1);
	LCD_EN = 1;
	DelayMs(1);
	LCD_EN = 0;
}

void LCD1602WriteData(uchar Data)
{
	LCD_RS = 1; 
	LCD_DATA = Data; 
	DelayMs(1);
	LCD_EN = 1;
	DelayMs(1);
	LCD_EN = 0;
}

//!!a lot of undefination
void LCD1602Config(void)
{  
	char i = 0;
	LCD_RW = 0;

	LCD1602WriteCommand(0x38);//设置液晶工作模式
	LCD1602WriteCommand(0x0c);//开显示不显示光标
	LCD1602WriteCommand(0x06);//整屏不移动，指针加一
	LCD1602WriteCommand(0x01);

}

void LCD1602WriteStr(uchar* str, uchar length)
{
    uchar i;
    for(i = 0; i < length; i++){
        LCD1602WriteData(str[i]);
     }
 }
