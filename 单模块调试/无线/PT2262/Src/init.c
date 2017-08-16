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
	//	FT0ENB=0;
	//	FT0IEN=0;
	//	FT0IRQ=0;

	T0M=0x70;		// fcpu/2
	FT0TB =0;
	T0C=0x38;		// 100us >> 
	FT0IEN=1;
 	FT0ENB=1;

	FGIE=1;			//使能总中断
}
