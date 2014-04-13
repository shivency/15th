#include <reg52.h>
#include <intrins.H>
#include <math.H>
#include "lcd1602.h"
#include "DS1302.h"
#include "delay.h"
#include "adjust.h"
#include "ds18b20.h"
#include "ir.h"

uchar miao = 0, shi = 0, fen = 0;

void Timer1Config(void);
void TimeReresh(uchar add,uchar dat);
void TempSisplay(int v, unsigned char position); 

void main(void)
{
	uchar tab_temper[]={"temper: "};
    uchar tab_time[]={"now:   :  :"};
    DS18B20SendChangeCmd();
    LCD1602Config();
    LCD1602WriteCommand(yh);
    LCD1602WriteStr(tab_temper, 8);
    LCD1602WriteCommand(er+3);
    LCD1602WriteStr(tab_time, 11);
	DS1302Config();
	Timer1Config();
	
	while(1){

		LCD1602WriteCommand(0xc0);
        TempSisplay(DS18B20GetTmpValue(), yh+8);
        DS18B20SendChangeCmd();
		KeyScan();

// 		TimeReresh(14,miao);
// 		TimeReresh(11,fen);
// 		TimeReresh(8,shi);
	}
}


void Timer1Config(void)
{
	TMOD=0x11;
	TH1=0;
	TL1=0;
	EA=1;
	ET1=1;
	TR1=1;
}

void timer(void) interrupt 3
{
	miao = BCDDecimal(DS1302ReadCommand(0x81));
	fen =  BCDDecimal(DS1302ReadCommand(0x83));
	shi  = BCDDecimal(DS1302ReadCommand(0x85));
	
// 		TimeReresh(14,miao);
// 		TimeReresh(11,fen);
// 		TimeReresh(8,shi);

}

void TimeReresh(uchar add,uchar dat)//reentrant//写时分秒
{
	LCD1602WriteCommand(er + add);
	LCD1602WriteData(0x30 + (int)(dat/10));
	LCD1602WriteData(0x30 + (int)(dat%10));
}

void TempSisplay(int v, unsigned char position) 
{
    unsigned char count;
    unsigned char datas[] = {0, 0, 0, 0, 0};
    unsigned int tmp = abs(v);
    datas[0] = tmp / 10000;
    datas[1] = tmp % 10000 / 1000;
    datas[2] = tmp % 1000 / 100;
    datas[3] = tmp % 100 / 10;
    datas[4] = tmp % 10;
    LCD1602WriteCommand(position);
    if(v < 0)
    {
        LCD1602WriteStr("- ", 2);
   }
    else
    {
       LCD1602WriteStr("+ ", 2);
    }
    if(datas[0] != 0)
    {
        LCD1602WriteData('0'+datas[0]);
    }
    for(count = 1; count != 5; count++)
    {
        LCD1602WriteData('0'+datas[count]);
        if(count == 2)
        {
            LCD1602WriteData('.');
        }
    }
}



