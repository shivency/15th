#include "adjust.h"
#include "lcd1602.h"
#include "DS1302.h"
#include "delay.h"


static uchar key1n = 0;

void KeyScan(void)
{
	uchar temp = 0;
	key = 0;

	//key1为功能键
	if(key1  ==  0){
		DelayMs(5);

		if(key1  ==  0){
			while(!key1);
			key1n++;

			if(key1n  ==  5)
				key1n = 1;

			switch(key1n){
				case 1: 
				TR0 = 0;//关闭定时器
				LCD1602WriteCommand(er + 14);//写入光标位置
			   	LCD1602WriteCommand(0x0f);//设置光标为闪烁
			   	temp = miao / 10 * 16 + (miao) % 10;
			   	DS1302WriteCommand(0x8e, 0x00);
			   	DS1302WriteCommand(0x80, 0x80|temp);//miao
			   	DS1302WriteCommand(0x8e, 0x80);
			   	break;

			   	case 2:  
			   	LCD1602WriteCommand(er + 11);//fen
				break;

				case 3: 
				LCD1602WriteCommand(er + 8);//shi
				break;

				case 4:
				LCD1602WriteCommand(0x0c);//设置光标不闪烁
				TR0 = 1;//打开定时器
				temp = (miao) / 10 * 16 + miao % 10;
			   	DS1302WriteCommand(0x8e, 0x00);
			   	DS1302WriteCommand(0x80, 0x00|temp);//miao
			   	DS1302WriteCommand(0x8e, 0x80);
	            break;
	        }
	    }
	}

	//当key1按下以下。再按以下键才有效
	if(key1n != 0){ //上调键
		if(key2 == 0){
			DelayMs(5);
			if(key2 == 0){
				while(!key2);
				switch(key1n){

					case 1:
					miao++;
					if(miao == 60)  
						miao = 0;
					TimeReresh(14,miao);//写入新的秒数
					temp = (miao)/10*16 + (miao)%10;
				   	DS1302WriteCommand(0x8e,0x00);
				   	DS1302WriteCommand(0x80,0x80|temp);
				   	DS1302WriteCommand(0x8e,0x80);
					LCD1602WriteCommand(er + 0x0b);//因为设置液晶的模式是写入数据后，指针自动加一，在这里是写回原来的位置
					break;

					case 2:
					fen++;
					if(fen == 60)
						fen = 0;
					TimeReresh(11,fen);
					temp = (fen)/10*16 + (fen)%10;
				   	DS1302WriteCommand(0x8e,0x00);
				   	DS1302WriteCommand(0x82,temp);
				   	DS1302WriteCommand(0x8e,0x80);
					LCD1602WriteCommand(er + 8);
					break;

					case 3:shi++;
					if(shi == 24)
						shi = 0;
					TimeReresh(8,shi);
					temp = (shi)/10*16 + (shi)%10;
				   	DS1302WriteCommand(0x8e,0x00);
				   	DS1302WriteCommand(0x84,temp);
				   	DS1302WriteCommand(0x8e,0x80);
					LCD1602WriteCommand(er + 5);
					break;
				}
			}
		}

	if(key3 == 0){
		DelayMs(5);
		if(key3 == 0){
			while(!key3);

			switch(key1n){
				case 1:
				miao--;
				if(miao == -1)
					miao = 59;
				TimeReresh(14, miao);//写入新的秒数
				LCD1602WriteCommand(er + 14);//因为设置液晶的模式是写入数据后，指针自动加一，在这里是写回原来的位置
				break;

				case 2:
				fen--;
				if(fen == -1)
					fen = 59;
				TimeReresh(11,fen);
				temp = (fen)/10*16 + (fen)%10;
			   	DS1302WriteCommand(0x8e,0x00);
			   	DS1302WriteCommand(0x82,temp);
			   	DS1302WriteCommand(0x8e,0x80);
				LCD1602WriteCommand(er + 11);
				break;

				case 3:
				shi--;
				if(shi == -1)
					shi = 23;
				TimeReresh(8,shi);
				temp = (shi)/10*16 + (shi)%10;
			   	DS1302WriteCommand(0x8e,0x00);
			   	DS1302WriteCommand(0x84,temp);
			   	DS1302WriteCommand(0x8e,0x80);
				LCD1602WriteCommand(er + 8);
				break;	
			}
		}
	}
}



}