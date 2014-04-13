#include "IR.h"
#include "lcd1602.h"


void IrDisplay(void)
{
    switch(g_ir_code[2])
    {
    case 0x0c:
        LCD1602WriteData(0x30 + 1);
        break;//1
    case 0x18:
        LCD1602WriteData(0x30 + 2);
        break;//2
    case 0x5e:
        LCD1602WriteData(0x30 + 3);
        break;//3
    default:
        break;
    }

    g_ir_accept = 0;
}

void IrAccpet(void)
{
    unsigned char i = 0, j = 1, k = 1;
    unsigned char coding,value;


    for(i = 0; i < 4; i++){
        for(j = 1; j <= 8; j++){
            coding = g_ir_data[k];
            if(coding>7)
                value |= 0x80;
            if(j < 8){
                value >>= 1;
            }
            k++;
        }
        g_ir_code[i] = value;
        value = 0;
    }
    g_ir_accept = 1;
}
