#ifndef _IR_H_
#define _IR_H_

#include <reg52.h>
sbit IR = P3^2;

extern unsigned char  g_ir_count; //红外全局变量
extern bit g_ir_accept, g_ir_display;
extern unsigned char g_ir_code[4];  //红外编码分四种：依次：引导-客户-操作-操作反码
extern unsigned char g_ir_data[33]; //存储每个电平的持续时间

void IrDisplay(void);
void IrAccpet(void);
#endif 