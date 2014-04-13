#include "delay.h"

void DelayMs(unsigned int ms)
{
	char i= 104;
	while(ms--)
		for(i= 104; i; i--)
			;
}

// void DelayUs(unsigned int us)
// {
// 	while(us--);
// }