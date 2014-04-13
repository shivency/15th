#ifndef	_LCD1602_H_
#define _LCD1602_H_

#include <reg52.h>
#define LCD_DATA P0
#define	uchar	unsigned char
#define	uint	unsigned int
#define yh 0x80  //第一行的初始位置
#define er 0x80+0x40 //第二行初始位置

sbit	LCD_RS = P1^0;
sbit	LCD_RW = P1^1;
sbit 	LCD_EN = P2^5;

void LCD1602WriteCommand(uchar command);
void LCD1602WriteData(uchar Data);
void LCD1602Config(void);
void LCD1602WriteStr(uchar * str, uchar length);
#endif