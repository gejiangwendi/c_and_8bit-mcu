#include "user.h"

void init(void)
{
	/*--------Inital I/O---------*/

	P0M	 	=	0X00;						//����
	P0UR 	=	0X00;						//��������

	P1M	 	=	0X00;						//key234Ϊ����
	P1UR 	=	0XFF;						//ʹ����������

	P2M		=	0xFF;						//ledΪ���
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

	/*------Inital P00---����/�½���----

	FP00IRQ=0;		//int0�жϱ�־����
	PEDGE=0x18;		//Level change trigger
	INTEN|=0x01;	//ʹ��int0

	//*----------Inital TC0-------------*

	TC0C	=	 206;	//50us
	TC0R	=	 206;	//
	TC0M	=    0XE4;	//1110 0100 fcpu/4 / Enable TC0 auto-reload /
	FTC0IEN = 	 0;		//unEnable TC0 interrupt service
	FTC0ENB =	 1;		//Enable TC0 timer*/

	/*-------ʹ�����ж�----------*/

	FGIE=1;			
}