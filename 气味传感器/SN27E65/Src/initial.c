#include	"user.h"


void	initial		(void)
{
	WDTR	=	0x5A;
/***********************  IO  ***************************/

	// IO����ͨ���������ʱ GCHS��POCON����Ϊ0
	// P02, P03, P10��P11   P0OC,P1OC��open-drain���� Ҫ������Ϊ���ģʽ ʹ����������

	//  Bit 7 Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
	//	  -		P06  P05   P04   P03   P02   -     P00
	//	  -		-     -     -     -     -    P11   P10
	//	 P47   P46   P45   P44   P43    -     -     -
	//	  -		-     -     -     P53  P52   P51   P50
	P0M  	=	0xff;
	P0UR	=	0xFF;
	P0		=	0x00;
	P0OC	=	0x00;

	P1M  	=	0xff;
	P1UR	=	0xFF;
	P1		=	0x00;
	P1OC	=	0x00;

	P4M  	=	0x5f;		//A5 IN      p47 hwjc in 
	P4UR	=	0x5F;
	P4		=	0x10;
	P4CON	=	0x20;		

	P5M  	=	0xff;
	P5UR	=	0xFF;
	P5		=	0x00;
	P5CON	=	0x00;

	L_outp = 0;
	M_outp = 0; 	
	H_outp = 0; 

/***********************  TIMER0  ***************************/

	//	ADCIEN T1IEN   TC2IEN  TC1IEN  TC0IEN  T0IEN  P01IEN  P00IEN
	//	MSPIEN  UTXIEN  URXIEN SIOIEN  WAKEIEN
	FGIE	=	0;		//�����ж�STKP.7
	FT0IEN	=	0;
	FT0ENB	=	0;
	//	T0M [ T0ENB T0rate2 T0rate1 T0rate0 - - - T0TB ]
	T0M		=	0x00;	// fcup/256
	T0C		=	100;	// 10ms T0C initial value = 256 - (T0 interval time * input clock)

	FT0IEN	=	1;		//�ж�ʹ��
	FT0IRQ	=	0;		//�ж������־����
	FT0ENB	=	1;		//T0ʹ��
//	STKP	|=	0x80;
	FGIE	=	1;		//�����ж�STKP.7

/***********************  PWM0(TC0)  ***************************/

 	TC0M	=	0;		//��TC0M	
	TC0M	=	0x30;	//����TC0ʱ��Դ��TC0Rate

	TC0C	=	156;		//����TC0C��TC0R�Ĵ������PWM����
	TC0R	=	156;		//TC0R��ʼֵ= 256 -��TC0�жϼ��ʱ��* TC0ʱ��Rate��

	FTC0IRQ	=	0;		//��TC0IRQ

	FTC0IEN=	1;		//ʹ��TC0�ж�
	FTC0ENB	=	1;		//ʹ��TC0��ʱ��

/********************  PWM1(TC1)  ************************

 	TC1M	=	0;		//��TC0M	
	TC1M	=	0x10;	//����TC0ʱ��Դ��TC0Rate

	TC1C	=	56;		//����TC0C��TC0R�Ĵ������PWM����
	TC1R	=	56;		//TC0R��ʼֵ= 256 -��TC0�жϼ��ʱ��* TC0ʱ��Rate��

	TC1D	=	76;		//����TC0D�Ĵ������PWMռ�ձ�,�������TC0R

	FTC1ENB	=	1;		//ʹ��TC0��ʱ��
	FPWM1OUT=	1;		//ʹ��PWM

//***********************  TC2  ***************************/

 	TC2M	=	0;		//��TC0M	
	TC2M	=	0x30;	//ʱ��Դ��TC2Rate  Fcpu / 16

	TC2C	=	236;		//����TC2���� 0.1ms
	TC2R	=	236;

	FTC2IRQ	=	0;		//��TC2IRQ

	FTC2IEN=	1;		//ʹ��TC2�ж�
	FTC2ENB	=	1;		//ʹ��TC2��ʱ��

/***********************  ADC  ***************************/

	//	    Bit 7 Bit 6   Bit 5  Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
	//	      -   ADCKS1  ADLEN ADCKS0   -     -   ADB1  ADB0 
	//		ADCKS[1 0]ADC's clock rate 00 = Fcpu/16, 01 = Fcpu/8, 10 = Fcpu/1, 11 = Fcpu/2 
	//		ADLEN: ADC's �ֱ��� 0 = 8-bit. 1 = 10-bit.
	FADCIEN = 0;		//��ֹADC�ж�

	ADM 	= 0xb5;		//����P4.5 ADC����.ʹ��ADC����

	ADR 	= 0;		//����ADת������Fcpu/16 8-bit
	FADCIRQ	= 0;		//���ADC�ж������־

	FADCIEN = 1; 		//ʹ��ADC�ж�
	FGIE	= 1; 		//ʹ��GIE
//	FADS	= 1; 		//����һ��ADת�����������Զ�����

}