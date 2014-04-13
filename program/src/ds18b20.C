#include "ds18b20.h"
#include "delay.h"
#include <intrins.H>

void DS18B20Config(void)
 {
    
    unsigned char i = 100;  
    DS18B20_DS = 0;

    while(i--);
    DS18B20_DS = 1; 

    i = 4;
    while(i--);
 }
 
void DS18B20Wait(void)
 {
    unsigned int i = 4;
    while(DS18B20_DS);  
    while(~DS18B20_DS);
    while(i--);
}


bit DS18B20ReadBit(void)
{
    unsigned int i = 8;
    bit b;
    DS18B20_DS = 0;
    _nop_();   
    DS18B20_DS = 1; 
    _nop_(); 
    _nop_();
    b = DS18B20_DS;

    while(i--);
    return b;
}

unsigned char DS18B20ReadByte(void)
{
    unsigned int i;
    unsigned char j, dat = 0;

    for(i=0; i<8; i++){
        j = DS18B20ReadBit();
        dat = (j << 7) | (dat >> 1);
    }
    return dat;
}


void DS18B20WriteByte(unsigned char dat)
{
    unsigned int i = 8;
    unsigned char j;
    bit b;
    for(j = 0; j < 8; j++){
        b = dat & 0x01;
        dat >>= 1;
    
        if(b){
            DS18B20_DS = 0; 
            _nop_(); _nop_();                    
            DS18B20_DS = 1;    
            i = 8; while(i>0) i--;  
        }
        else{
        	DS18B20_DS = 0;
        	i = 8; while(i>0) i--;   
            DS18B20_DS = 1;
            _nop_(); _nop_();             
        }
    }
}


void DS18B20SendChangeCmd(void)
{
    DS18B20Config();    
    DS18B20Wait();   
    DelayMs(1);    
    DS18B20WriteByte(0xcc);
    DS18B20WriteByte(0x44);
}

void DS18B20SendReadCmd(void)
{
    DS18B20Config();
    DS18B20Wait();
    DelayMs(1);
    DS18B20WriteByte(0xcc); 
    DS18B20WriteByte(0xbe); 
}


int DS18B20GetTmpValue(void)
{
    unsigned int tmpvalue;
    int value; 
    float t;
    unsigned char low, high;
    DS18B20SendReadCmd();
    
    low = DS18B20ReadByte(); 
    high = DS18B20ReadByte();
   
    tmpvalue = high;
    tmpvalue <<= 8;
    tmpvalue |= low;
    value = tmpvalue;
    
    t = value * 0.0625;

    value = t * 100 + (value > 0 ? 0.5 : -0.5); 
    return value;
}

