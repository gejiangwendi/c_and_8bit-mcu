#include "user.h"

extern	bit	 f_10ms;
extern	bit  f_1s;
		bit  buzzer_on;
		bit  SEG_OK;
		uint SEG;
        uint SEG2;
		uint num_10ms ;

void main(void)
{
	WDTR = 0x5A;
	STKP |= 0x07;
	initial();
	while(1)
	{
		WDTR = 0x5A;
		key();
		timer(); 
		led_dsp();
	}
}

void __interrupt [0x08] isr(void)
{
	if(FTC0IEN && FTC0IRQ)	
	{
		FTC0IRQ = 0;
		if(buzzer_on)
		{
			FP00 = ~FP00; 
		}
		SEG2++;
		if(SEG2 >= 20)
		{
			SEG2 = 0;
			SEG ++;
			SEG_OK = 1;
		}
	}
	if(FT0IEN && FT0IRQ)
	{
		FT0IRQ = 0;
		T0C = 0x64;
		f_10ms = 1;
		num_10ms++;
		if(num_10ms >= 100)
		{
			num_10ms = 0;
			f_1s = 1;
		}
	}
}