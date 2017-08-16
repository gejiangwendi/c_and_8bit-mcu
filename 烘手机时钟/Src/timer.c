#include "user.h"

extern uint key_fifo;
extern uint buz_cnt2;
extern uint buz_cnt3;
extern bit  buzzer_on;
extern bit  key3s_on;
extern bit  key_on;
	   bit  sys_on;
	   bit  f_1s;
	   bit  timer_on;
	   bit  buzzer1_on;
	   bit  buzzer2_on;
	   bit  buzzer3_on;
	   bit  buzzer4_on;
	   uint time1;
	   uint time2;

void timer(void)
{
	if(key_on || key3s_on)
	{
		switch(key_fifo)
		{
			case 1 : 
			{
				if(!sys_on)
				{
					sys_on = 1;
					time1 = 0;
					time2 = 0;
					buz_cnt2 = 0;
					buz_cnt3 = 0;
					buzzer1_on = 0;
					buzzer3_on = 0;
					buzzer4_on = 0;
					buzzer2_on = 1;
					buzzer_on = 1;
					timer_on = 0;
				}
				else
				{
					sys_on = 0;
					buz_cnt2 = 0;
					buz_cnt3 = 0;
					buzzer2_on = 0;
					buzzer3_on = 0;
					buzzer4_on = 0;
					buzzer1_on = 1;	
					buzzer_on = 1;
					P1 &= 0xF0;
					timer_on = 0;
				}
				break;
			}
			case 2 : 
			{
				if(sys_on && !timer_on && time1 < 99)
				if(key_on)
				time1 += 1;
				else if(key3s_on)
				{
					time1 += 3;
					if(time1 > 99)
					{
						time1 = 99;
						time2 = 59;					
					}
				}
				if(sys_on)
				{
					buz_cnt2 = 0;
					buz_cnt3 = 0;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer3_on = 0;
					buzzer4_on = 1;
					buzzer_on = 1;
				}
				break;
			}
			case 3 : 
			{
				if(sys_on && !timer_on)
				{
					if(key_on)
					{
						if(time2 < 59)
						time2++;
						else if(time1 < 99)
						{
							time2 = 0;
							time1++;
						}
					}
					else if(key3s_on)
					{
						if(time2 < 59)
						{
							time2 += 3;
							if(time2 >59)
							{
								if(time1 < 99)
								{
									time1++;
								}
								else
								{
									time2 = 59;
								}
							}
						}
						else if(time1 < 99)
						{
							time2 = 2;
							time1 ++;
						}
					}
				}
				if(sys_on)
				{
					buz_cnt2 = 0;
					buz_cnt3 = 0;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer3_on = 0;
					buzzer4_on = 1;
					buzzer_on = 1;
				}
				break;
			}
			case 4 : 
			{
				if(sys_on)
				{
					if(timer_on)
					{
						timer_on = 0;
						time1 = 0;
						time2 = 0;
					}
					else if(time1 || time2)
					{
						timer_on = 1;
					}
					buz_cnt2 = 0;
					buz_cnt3 = 0;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer3_on = 0;
					buzzer4_on = 1;
					buzzer_on = 1;
				}
				break;
			}
			default : {};
		}
		key_on = 0;
		key3s_on = 0;

	}
	if( f_1s)
	{
		f_1s = 0;
		if(sys_on && timer_on)
		{
			if(time2 > 0)
			time2 --;
			else
			{
				if(time1 > 0)
				{
					time1 --;
					time2 = 59;
				}
				else
				{
					buz_cnt2 = 0;
					buz_cnt3 = 0;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer4_on = 0;
					buzzer3_on = 1;
					buzzer_on = 1;
				}
			}
		}
	}
}
