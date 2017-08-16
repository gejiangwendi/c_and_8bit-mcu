#include "user.h"

void initial(void)
{
	u8 temp1;
	/*************** IO������ ****************/
		P0M		&=	0xfb;
		P0M		|=	0x01;
		P0UR	=	0x01;
	 	BT_OUT	=	0;	// 1��Ч

		P1M 	=	0x1f;
		P1UR	=	0xfe;
	 	L_OUT	=	1;	// 0��Ч
	 	M_OUT	=	1;	// 0��Ч
	 	H_OUT	=	1;	// 0��Ч
	 	SW_OUT	=	1;	// 0��Ч

		P2M 	=	0xe0;
		P2UR	=	0xff;

		P5M 	=	0x0d;
		P5UR	=	0x0d;
	 	HUM_OUT	=	1;	// 0��Ч
	 	ION_OUT	=	1;	// 0��Ч

		notest = 1;
		if((P2 & 0x1f) == 0x0b)
		{
			delayms(10);
			if((P2 & 0x1f) == 0x0b)
			{
				notest = 0;
				testmode_slp = 0;// test mode
				testmode_timer = 1;
			}
		}
		if(notest)
		{
			testmode_slp = 20;
			testmode_timer = 60;
		}

	/*************** int T0���� ****************/
		FT0IEN=0;
		FT0ENB=0;
		T0M=0x70;	//T0ʱ��=Fcpu/8  0x60->Fcpu/4  0x70->Fcpu/2
		T0C=0xCC;	//T0C��ֵ 0xC2 125us
		FT0IRQ=0;
		FT0IEN=1;
		FT0ENB=1;
		FGIE=1;

/****************  led ��ʼ��  ****************/
		led_wr(0x03);	// 7λ 10��
		led_wr(0x40);	// 0x44 �̶���ַ
		led_wr(0xc0);
		for(temp1=0;temp1<14;temp1++)
		led_wrDATA(0xff);
		led_wr(0x8b);
		__asm("nop")
}
