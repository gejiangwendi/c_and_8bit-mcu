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
			if((++b_time)==200)
			{
				b_time=0;
				FP54=1;
				BUZZER_ON=0;
			}
		}
	}
}
