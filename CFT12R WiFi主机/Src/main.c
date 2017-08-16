#include "user.h"

	bit f_50ms;
	bit f_250ms;
	bit f_10ms;
	bit f2_10ms;
	bit f3_10ms;
	bit f4_10ms;

    uint num_10ms;
	uint num2_10ms;
	uint temp1s;

	uint BUZ_CNT;
	uint BUZ_CNT1;

void main(void)
{
	WDTR = 0x5A;
	init();
	while(1)
	{
		WDTR = 0x5A;
		key();
		display();
		buzzer();
	}
}

void __interrupt [0x08] isr(void)
{
	if(FT0IEN)
	{
		if(FT0IRQ)
		{
			FT0IRQ = 0;
			T0C=0x64;	//T0C≥ı÷µ 10ms
			f_10ms = 1;
			f2_10ms = 1;
			f3_10ms = 1;
			f4_10ms = 1;
			num_10ms++;
		}
	}
}

