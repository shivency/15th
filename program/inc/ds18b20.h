#ifndef	_DS18B20_H_
#define	_DS18B20_H_

#include <reg52.h>

#define	uchar 	unsigned char
#define	uint	unsigned int

sbit  DS18B20_DS = P2^2;

void DS18B20Config(void);
void DS18B20Wait(void);
bit DS18B20ReadBit(void);
unsigned char DS18B20ReadByte(void);
void DS18B20WriteByte(unsigned char dat);
void DS18B20SendChangeCmd(void);
void DS18B20SendReadCmd(void);
int DS18B20GetTmpValue(void);

#endif