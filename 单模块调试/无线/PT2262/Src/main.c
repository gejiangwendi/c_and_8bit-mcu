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
		decode();
		Led_key();
	}
	return 0;
}

void __interrupt [0x08] isr(void)
{
	if(FT0IRQ) 			//100us÷–∂œ“ª¥Œ
	{
		FT0IRQ = 0;
		DECODE=1;
	}
}

