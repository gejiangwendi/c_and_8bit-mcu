#include "user.h"

extern uint time1;
extern uint time2;
extern bit  sys_on;
extern bit  SEG_OK;
extern uint SEG;
	   uint led_code[]={0xFE,0x32,0xEb,0x7B,0x37,0x7d,0xFd,0x3A, 0xFf,0x7f};
	   uint P1_code[]={0x08 , 0x04 , 0x02 , 0x01};

void led_dsp(void)
{
	if(SEG_OK)
	{
		SEG_OK = 0;
		if(SEG >= 4)
		SEG = 0;
		if(sys_on)
		{
			P1 &= 0xF0;
			switch(SEG)
			{
				case 0 : P5 = led_code[time1/10]; break;
				case 1 : P5 = led_code[time1%10]; break;
				case 2 : P5 = led_code[time2/10]; break;
				case 3 : P5 = led_code[time2%10]; break;
				default : {};
			}
			P1 |= P1_code[SEG];
		}
	}
}