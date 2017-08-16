#include	"User.h"
#include	"KeyProcess.h"

extern 	uint	Keynum;
extern 	bit		KEY_ON;
extern 	bit		LED;
		bit		BUZZER_ON=0;
		int 	led_left=0;
		int 	led_right=3;
		int 	P2_TEMP[]={0x06,0x05,0x03,0x0f,0x17,0x27};
		int 	led_T1=0;
		int 	led_T2=0;
		int 	led_cir=0;
		bit 	K4_ON=0;
void KeyProcess(void)
{
	if(Keynum!=0)
	{
		if(Keynum==2)
		{
			K4_ON=0;
			led_left++;
			if(led_left==4)
			{
				led_left=1;
			}
			if(led_left==1)
			{
				P2|=0x07;
				P2&=0xfe;
			}
			else if(led_left==2)
			{
				P2|=0x07;
				P2&=0xfd;
			}
			else if(led_left==3)
			{
				P2|=0x07;
				P2&=0xfb;
			}
		}
		else if(Keynum==3)
		{
			K4_ON=0;
			led_right++;
			if(led_right==7)
			{
				led_right=4;
			}
			if(led_right==4)
			{
				P2&=0x07;
				P2|=0x08;
			}
			else if(led_right==5)
			{
				P2&=0x07;
				P2|=0x10;
			}
			else if(led_right==6)
			{
				P2&=0x07;
				P2|=0x20;
		}
		}
		else if(Keynum==4)
		{
			K4_ON=~K4_ON;
			led_cir=0;
		}
		BUZZER_ON=1;
		Keynum = 0;
	}
	if(K4_ON&&LED)
	{
		LED=0;
		led_T1++;
		if(led_T1==200)			//25ms
		{
			led_T1=0;
			led_T2++;
			if(led_T2==4)
			{
				led_T2=0;
				P2=P2_TEMP[led_cir];
				led_cir++;
				if(led_cir==6)
				{
					led_cir=0;	
				}
			}
		}
	}
}