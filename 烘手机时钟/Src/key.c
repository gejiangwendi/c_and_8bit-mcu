#include "user.h"

extern	bit timer_on;
extern	bit buzzer_on;
extern	bit buzzer1_on;
extern	bit buzzer2_on;
extern	bit buzzer3_on;
extern	bit buzzer4_on;
		bit key_on;
		bit key3s_on;
		bit key_in;
		bit f_10ms;
		bit key_3s_in;
		uint KeyChat;
		uint key_num;
		uint key_buf;
		uint key_fifo;
		uint num_1s;
		uint buz_cnt2;
		uint buz_cnt3;

void key(void)
{
	uint temp;
	if(f_10ms)
	{
		f_10ms = 0;
		if(!FP15)
		{
			key_num = 1;
		}
		else
		{
			P5M &= 0xF8;
			for(temp=0;temp<10;temp++);
			temp = P5 & 0x07; 
			P5M |= 0x07;
			if(temp != 0x07)
			{
				switch(temp)
				{
					case 0x05 : key_num = 2; break;	
					case 0x06 : key_num = 3; break;	
					case 0x03 : key_num = 4; break;
					default : key_num = 0; break;
				}
			}
			else
			{
				key_num = 0;
			}
			if(buzzer3_on && key_num != 1)
			{
				key_num = 0;
			}
		}
		if(key_buf != key_num)
		{
			key_buf = key_num;
			key_3s_in=0;
			KeyChat=0;
			num_1s=0;
			if(key_num)
			{
				key_in = 1;
			}
			else
			{
				key_in = 0;

			}
		}
		if(key_in && KeyChat==5)							 
		{
			key_on = 1;
			key_fifo = key_buf;
			if(key_buf==1 || key_buf==4)
			{
				key_in = 0;
				KeyChat = 0;
			}
		}
		if(key_in && KeyChat>=110)							 
		{
			KeyChat = 10;
			if(key_buf==2 || key_buf==3)
			{
				if(key_3s_in == 0)
				{
					num_1s++;
					if(num_1s == 2)
					{
						num_1s = 0;
						key_3s_in=1;
					}
				}
				else
				{
					key3s_on = 1;
				}
			}
		}
		if(key_in)
		{
			KeyChat++;
		}
		if(buzzer4_on || buzzer3_on || buzzer2_on || buzzer1_on)
		{
			buz_cnt2 ++;
			if(buz_cnt2 == 15) 
			{
				if(buzzer4_on || buzzer3_on || buzzer2_on)
				{
				 	buzzer_on = 0;
				}
				if(buzzer4_on)
				{
					buzzer4_on = 0;
				}
			}
			else if(buz_cnt2 == 20)
			{
				if(buzzer3_on || buzzer2_on)
				{
					buzzer_on = 1;
				}
			}
			else if(buz_cnt2 == 35)
			{
				buzzer_on = 0;
				if(buzzer1_on)
				{
					buzzer1_on = 0;
				}
				if(buzzer2_on)
				{
					buzzer2_on = 0;
				}
			}
			else if(buz_cnt2 >= 50)	
			{
				buz_cnt2 = 0;
				if(buzzer3_on)
				{
					buz_cnt3 ++;
					if(buz_cnt3 >= 120)
					{
						buzzer3_on = 0;
						timer_on = 0;
					}
					else
					buzzer_on = 1;
				}
				else
				{
					buzzer3_on = 0;
				}
			}
		}
	}
}