#ifndef _ADJUST_H_
#define _ADJUST_H_

#include <reg52.h>
#define	uchar	unsigned char
#define	uint	unsigned int

sbit key=P3^7;
sbit key1=P3^0;
sbit key2=P3^1;
sbit key3=P3^2;

extern uchar miao,shi,fen;
extern void TimeReresh(uchar add,uchar dat);
void KeyScan(void);



#endif