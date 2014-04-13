#include "DS1302.h"
extern uchar miao,shi,fen;

void DS1302WriteByte(uchar Data)
{
	char a = 0;
	ACC = Data;
	DS1302_RST = 1;
	for(a = 8; a>0; a--)
	{
		DS1302_IO = ACC0;
		DS1302_CLK = 0;
		DS1302_CLK = 1;
		ACC = ACC>>1;
	}
}

uchar DS1302ReadByte(void)
{
	char a = 0;
	DS1302_RST = 1;
	for(a = 8; a>0; a--)
	{
		ACC7 = DS1302_IO;
		DS1302_CLK = 1;
		DS1302_CLK = 0;
		ACC = ACC>>1;

	}
	return (ACC);
}

void DS1302WriteCommand(uchar add,uchar Data)
{

	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	DS1302WriteByte(add);
	DS1302WriteByte(Data);
	DS1302_CLK = 1;
	DS1302_RST = 0;
}

uchar DS1302ReadCommand(uchar add)
{
	uchar temp;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	DS1302WriteByte(add);
	temp = DS1302ReadByte();
	DS1302_CLK = 1;
	DS1302_RST = 0;
	return temp;
}

void DS1302Config(void)
{
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302WriteCommand(0x80,miao|0x00);//允许写
}

uchar BCDDecimal(uchar bcd)
{
	uchar Decimal;
	Decimal=bcd>>4;
	return(Decimal=Decimal*10+(bcd&=0x0F));
}