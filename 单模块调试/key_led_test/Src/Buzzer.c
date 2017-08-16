#include	"User.h"
#include	"Buzzer.h"

extern 	bit		BUZZER_ON;
extern 	bit		FBUZZER;
		uint 	b_time=0;

void Buzzer(void)
{
	if(FBUZZER)
	{
		FBUZZER=0;
		if(BUZZER_ON)
		{
			FP54=~FP54;
			if((++b_time)==50)
			{
				b_time=0;
				BUZZER_ON=0;
			}
		}
	}
}
