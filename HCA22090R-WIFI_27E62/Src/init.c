#include	"init.h"

#include	"delay.h"

//***************************************************************************
//! \brief       ϵͳ��ʼ������
//! \			 IO���š���ʱ�������ڳ�ʼ��
//! \param       ��
//! \return      ��
//***************************************************************************
void SYS_Init(void)
{
	Delay_ms(250);

	P0M  	&=	0xbb;
	P0M  	|=	0x28;
	P0UR	=	0x40;
	FP05 	=	0;

	P4M  	|=	0x60;
	P4UR	=	0x00;
	P4 		|=	0x60;

	P5M  	&=	0xFB;
	P5M  	|=	0x08;
	P5UR	=	0x04;
	FP53 	=	1;

	FGIE	=	0;
	FUTXPEN	=	0;
	FURXPEN	=	0;
	if(BodeRate-9 == 0)			// 9600
	{
		URRX	&=	0XFd;
		URRX	|=	0X05;
		URCR	=	0Xe6;								
	}
	else if(BodeRate-11 == 0)	// 115200
	{
		URRX	&=	0XF8;
		URCR	=	0Xbb;
	}
	FURXEN 	=	1;
	FUTXEN	=	1;
	FURXIEN = 	1;
	FURXIRQ = 	0;

	FT0IEN	=	0;
	FT0ENB	=	0;
	T0M		=	0x70;
	T0C		=	130;
	FT0IEN	=	1;
	FT0IRQ	=	0;
	FT0ENB	=	1;
	FGIE	= 	1;
	Delay_ms(250);
}

//***************************************************************************
//! \brief       WiFi��λ����
//! \			 �͸�WiFiģ�鸴λ����һ�������壬ʹ�临λ
//! \param       ��
//! \return      ��
//***************************************************************************
void Wifi_Rest(void)
{
	FP45 = 0;
	Delay_ms(250);
	FP45 = 1;
	Delay_ms(250);
}
