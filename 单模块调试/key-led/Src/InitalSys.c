#include	"User.h"

/********初始化程序中要用到的系统资源***********/

void	InitalSystem(void)
{
/*---------------Inital I/O---------------------*/
	FP00M	=	0X00;		//key1口输入
	P0UR	=	0XFF;		//使能上拉电阻

	P1M 	=	0X00;		//key234为输入
	P1UR 	=	0XFF;		//使能上拉电阻

	P2M	=	0xFF;		//led为输出
	P2UR	= 	0X00;

	P5M		=	0XFF;
	P5UR	=	0X00;

	P2  	=	0X07;
/*---------------Inital TC0---------------------*/
	TC0C	=	 6;
	TC0R	=	 6;
	TC0M	=     0XD4;
	FTC0IEN = 	 1;
	FTC0ENB =	 1;
/*---------------Inital T0----------------------*/
	FT0ENB=0;		//buzzer
	FT0IEN=0;
	FT0IRQ=0;
	T0M=0x70;		// fcpu/2
	FT0TB =0;
	T0C=0xf8;		// 4kHZ
	FT0IEN=1;
 	FT0ENB=1;
/*--------------Inital INT0---------------------*/
	FP00IRQ=0;		//int0中断标志清零
	PEDGE|=0x10;	//int0 下降沿触发
	PEDGE&=0x10;	
	INTEN|=0x01;	//使能int0
	FGIE=1;			//使能总中断
}

/***************预设参数*************************/	
void	Premain(void)
{										
	/*系统变量预设*/
	
}