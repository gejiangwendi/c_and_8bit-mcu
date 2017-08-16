#include	"user.h"


void	initial		(void)
{
	WDTR	=	0x5A;
/***********************  IO  ***************************/

	// IO口作通用输入输出时 GCHS，POCON必须为0
	// P02, P03, P10，P11   P0OC,P1OC打开open-drain功能 要求引脚为输出模式 使能上拉电阻

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
	FGIE	=	0;		//允许中断STKP.7
	FT0IEN	=	0;
	FT0ENB	=	0;
	//	T0M [ T0ENB T0rate2 T0rate1 T0rate0 - - - T0TB ]
	T0M		=	0x00;	// fcup/256
	T0C		=	100;	// 10ms T0C initial value = 256 - (T0 interval time * input clock)

	FT0IEN	=	1;		//中断使能
	FT0IRQ	=	0;		//中断请求标志清零
	FT0ENB	=	1;		//T0使能
//	STKP	|=	0x80;
	FGIE	=	1;		//允许中断STKP.7

/***********************  PWM0(TC0)  ***************************/

 	TC0M	=	0;		//清TC0M	
	TC0M	=	0x30;	//设置TC0时钟源和TC0Rate

	TC0C	=	156;		//设置TC0C和TC0R寄存器获得PWM周期
	TC0R	=	156;		//TC0R初始值= 256 -（TC0中断间隔时间* TC0时钟Rate）

	FTC0IRQ	=	0;		//清TC0IRQ

	FTC0IEN=	1;		//使能TC0中断
	FTC0ENB	=	1;		//使能TC0定时器

/********************  PWM1(TC1)  ************************

 	TC1M	=	0;		//清TC0M	
	TC1M	=	0x10;	//设置TC0时钟源和TC0Rate

	TC1C	=	56;		//设置TC0C和TC0R寄存器获得PWM周期
	TC1R	=	56;		//TC0R初始值= 256 -（TC0中断间隔时间* TC0时钟Rate）

	TC1D	=	76;		//设置TC0D寄存器获得PWM占空比,必须大于TC0R

	FTC1ENB	=	1;		//使能TC0定时器
	FPWM1OUT=	1;		//使能PWM

//***********************  TC2  ***************************/

 	TC2M	=	0;		//清TC0M	
	TC2M	=	0x30;	//时钟源和TC2Rate  Fcpu / 16

	TC2C	=	236;		//设置TC2周期 0.1ms
	TC2R	=	236;

	FTC2IRQ	=	0;		//清TC2IRQ

	FTC2IEN=	1;		//使能TC2中断
	FTC2ENB	=	1;		//使能TC2定时器

/***********************  ADC  ***************************/

	//	    Bit 7 Bit 6   Bit 5  Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
	//	      -   ADCKS1  ADLEN ADCKS0   -     -   ADB1  ADB0 
	//		ADCKS[1 0]ADC's clock rate 00 = Fcpu/16, 01 = Fcpu/8, 10 = Fcpu/1, 11 = Fcpu/2 
	//		ADLEN: ADC's 分辨率 0 = 8-bit. 1 = 10-bit.
	FADCIEN = 0;		//禁止ADC中断

	ADM 	= 0xb5;		//允许P4.5 ADC输入.使能ADC功能

	ADR 	= 0;		//设置AD转换速率Fcpu/16 8-bit
	FADCIRQ	= 0;		//清除ADC中断请求标志

	FADCIEN = 1; 		//使能ADC中断
	FGIE	= 1; 		//使能GIE
//	FADS	= 1; 		//启动一次AD转换，结束后自动清零

}