#include "user.h"

extern void decode(void);
extern void init(void);
extern void Led_key(void);

bit DECODE=0;

int main(void)
{
	init();
	while(1)
	{
		WDTR = 0x5A;
		if(DECODE)
		{
			DECODE=0;
			decode();
		}
		Led_key();
	}
	return 0;
}

void __interrupt [0x08] isr(void)
{
/*	if(FP00IRQ)			//int0 Level change trigger
	{
		FP00IRQ = 0;
		FTC0IEN = 0;
		countbuf=count;
		if(FP00)

	}
	if(FT0CIRQ) 		//50us�ж�һ��
	{
		FT0CIRQ = 0;

		if(FP00)
		h++
		else
		l++
	}*/
	if(FT0IRQ) 			//100us�ж�һ��
	{
		FT0IRQ = 0;
		DECODE=1;
	}
}

