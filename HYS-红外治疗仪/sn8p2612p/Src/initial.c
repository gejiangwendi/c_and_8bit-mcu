#include "user.h"


void initial(void)
{
	/*************** IO������ ****************/
		P0M	=	0x00;	//P0.0��Ϊ����ģʽ
		P0UR=	0x01;

		P1M =	0xCF;	// P1.4 P1.5��Ϊ����ģʽ
		P1UR=	0xCF;
		P1 	=	0x00;

		P5M =	0xFF;
		P5UR=	0xFF;
		P5  =   0XFF;
	/*************** pwm TC0���� ****************/
		FTC0ENB	=	0;
		TC0M	=	0x50;	// TC0 ʱ�ӣ�Fcpu/2
		TC0C	=	0x8A;	// 
		TC0R	=	0x8A;
		FTC0OUT	=	1;
		FALOAD0	=	1;
	/*************** int T0���� ****************/
		FT0IEN=0;
		FT0ENB=0;
		T0M=0x00;	//����T0ʱ��= Fcpu/256
		T0C=0x64;	//T0C��ֵ 10ms
		FT0IRQ=0;
		FT0IEN=1;
		FT0ENB=1;
}
