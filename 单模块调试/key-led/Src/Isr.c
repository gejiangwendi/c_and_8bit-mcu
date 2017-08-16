#include	"User.h"
extern 	bit F1ms;
extern 	bit K4_ON;
bit 	FKEY=0;
bit 	key1_flag=0;
bit		FBUZZER = 0;
bit		LED = 0;
bit s=0;
extern bit BUZZER_ON;


/************中断服务程序*****************/

void __interrupt [0x08] isr(void)
{
	if(FTC0IRQ)
	{
		FTC0IRQ = 0;
		F1ms = 1;
	}
	if(FT0IRQ)			//8kHZ 0.125MS
	{
		if(BUZZER_ON)
		{
			FP54=~FP54;
		}
		FT0IRQ = 0;
		FBUZZER = 1;
		LED = 1;
		s=1;
	}
	if(FP00IRQ)
	{
		FP00IRQ=0;
		FKEY=~FKEY;
		key1_flag=1;
	}
}