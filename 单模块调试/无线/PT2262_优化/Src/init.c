#include "user.h"

void init(void)
{
	/*--------Inital I/O---------*/

	P0M	 	=	0X00;						//输入
	P0UR 	=	0X00;						//上拉电阻

	P1M	 	=	0X00;						//key234为输入
	P1UR 	=	0XFF;						//使能上拉电阻

	P2M		=	0xFF;						//led为输出
	P2UR	= 	0X00;

	P5M		=	0XFF;
	P5UR	=	0X00;

	P2  	=	0X07;

	/*------Inital T0---100us----*/

	FT0ENB=0;
	FT0IEN=0;
	FT0IRQ=0;
	T0M=0x70;		// fcpu/2
	FT0TB =0;
//	T0C=0x38;		// 100us 
	T0C=0x9c;		// 50us 
	FT0IEN=1;
 	FT0ENB=1;

	/*------Inital P00---上升/下降沿----

	FP00IRQ=0;		//int0中断标志清零
	PEDGE=0x18;		//Level change trigger
	INTEN|=0x01;	//使能int0

	//*----------Inital TC0-------------*

	TC0C	=	 206;	//50us
	TC0R	=	 206;	//
	TC0M	=    0XE4;	//1110 0100 fcpu/4 / Enable TC0 auto-reload /
	FTC0IEN = 	 0;		//unEnable TC0 interrupt service
	FTC0ENB =	 1;		//Enable TC0 timer*/

	/*-------使能总中断----------*/

	FGIE=1;			
}