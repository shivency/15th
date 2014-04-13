#ifndef	_DS1302_H_
#define	_DS1302_H_

#include <reg52.h>
#define	uchar	unsigned char
#define	uint	unsigned int

sbit	DS1302_IO 	= P2^0;
sbit	DS1302_CLK	= P2^1;
sbit	DS1302_RST	= P2^4;
sbit    ACC0        = ACC^0;
sbit    ACC7        = ACC^7;

void DS1302WriteByte(uchar Data);
uchar DS1302ReadByte(void);
void DS1302WriteCommand(uchar add,uchar Data);
uchar DS1302ReadCommand(uchar add);
void DS1302Config(void);
uchar BCDDecimal(uchar bcd);

#endif