#include	"user.h"

extern uint num_1s;
extern uint t_cnt1;
extern uint t_cnt2;
extern uint t_cnt3;
extern uint POWER;
extern uint TIME;
extern uint	TIME_LED; 
extern uint	POWER_LED; 
extern bit BUZZER2_ON;
extern bit BUZZER3_ON;
extern bit LOCK_LED; 
extern bit RST_LED;  
extern bit LOCK_ON;        
extern bit SYS_ON;     
extern bit SYS_LED; 
extern bit DSP_OFF;
extern bit LOCK_T;
extern bit RST_ON;
extern bit RST_T;
extern bit model;	
extern bit f3_1s;
extern bit f_1s;

uint TIME2_buf;
uint t_cnt4;
uint t_cnt5;
uint t_cnt6;
bit  delay2_in;
bit  FUN_SP = 0;

void rst_cnt(uint t1,uint t2,uint t3)
{
	if(!RST_ON)
	t_cnt1 ++;
	if(t_cnt1>=t1)
	{
		t_cnt1 = 0;
		t_cnt2 ++;
		if(t_cnt2>=t2)
		{
			t_cnt2 = 0;
			t_cnt3 ++;
			if(t_cnt3>=t3)
			{
				t_cnt3 		= 	0;
				FUN_SP 		= 	1;		//关闭整机功能 标志位
				RST_ON 		= 	1;		//led 指示灯亮
				TIME   		= 	0;
				POWER  		= 	0;
				LOCK_ON		= 	0;
				LOCK_T 		= 	0;
				RST_T  		= 	0;
				DSP_OFF		=	0;
				TIME_LED	=	0;
				POWER_LED	=	0;
				LOCK_LED 	=	0; 
				RST_LED 	=	1;
			}
		}
	}
}
void rst(void)
{
	if(f_1s)
	{
		f_1s = 0;
		if(model)	// test 
		rst_cnt(5,1,1);
		else
		rst_cnt(216,250,200);
	}
	if(f3_1s)
	{
		f3_1s = 0;
		if(TIME2_buf != TIME)
		{
			TIME2_buf = TIME;
			if(TIME != 0)
			{
				delay2_in = 1;
			}
			else
			{
				t_cnt4 = 0;
				t_cnt5 = 0;
			}
		}
		if(delay2_in)
		{
			t_cnt4++;
			if(t_cnt4 >= 180)
			{
				t_cnt4 = 0;
				t_cnt5++;
				if((t_cnt5>=20&&TIME==1)||(t_cnt5>=40&&TIME == 2)||(t_cnt5>=80&&TIME == 3)||(t_cnt5>=160&&TIME==4))
				{
					TIME = 0;
					t_cnt5 = 0;
					if(SYS_ON)
					{
						SYS_ON		=	0;
						POWER 		=	0;
						POWER_LED 	=	0;
						TIME 		=	0;
						TIME_LED 	=	0;
						LOCK_ON 	=	0;
						LOCK_LED 	=	0;
						BUZZER3_ON	=	1;
					}
					else
					{
						SYS_ON 		=	1;
						BUZZER2_ON	=	1;
					}
					SYS_LED = SYS_ON;
				}
			}
		}
	}
}		
