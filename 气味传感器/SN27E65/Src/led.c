#include	"user.h"

extern bit f2_1s;

extern bit    DSP_OFF;
extern bit    LOCK_ON;        
extern bit     RST_ON;         
extern bit      RST_T;
extern bit     LOCK_T;
extern bit     FUN_SP;

extern bit	   f_FP04;
extern bit	   f_FP03;

extern uint     POWER;

bit    		  SYS_LED;  
bit    		  RST_LED;  
bit   		 LOCK_LED; 
uint 		 TIME_LED;
uint 		POWER_LED;

void	led		(void)
{
	uint temp1;
	if(!DSP_OFF)
	{
		P0M  |=	0x1d;
		P5M  |=	0x08;
		if(LOCK_T)
		{
			if(f2_1s)
			{
				f2_1s = 0;
				LOCK_LED = ~LOCK_LED;
			}
		}
		else if(RST_T)
		{
			if(f2_1s)
			{
				f2_1s = 0;
				RST_LED = ~RST_LED;
			}
		}
		else if(f2_1s)
		{
			f2_1s = 0;
		}
		if(LOCK_LED || RST_LED || f_FP03 || f_FP04)
		{
			FP43 = 0;
			L_4H_RST = RST_LED;
			if(!FUN_SP)
			{
				E_8H_LOCK = LOCK_LED;
				FP04 = f_FP04;
				FP03 = f_FP03;
			}
			for(temp1=0;temp1<100;temp1++);
			FP43 = 1;
		}
		if(TIME_LED>0 && TIME_LED<5 && !FUN_SP)
		{
			FP06 = 0;
			switch(TIME_LED) 
			{
				case 1 : P0 = (P0&0XE0)|0X10; break;
				case 2 : P0 = (P0&0XE0)|0X08; break;
				case 3 : P0 = (P0&0XE0)|0X04; break;
				case 4 : P0 = (P0&0XE0)|0X01; break;
				default : break;
			}
			for(temp1=0;temp1<100;temp1++);
			FP06 = 1;
		}
		if((POWER_LED>0 && POWER_LED<5)||SYS_LED)
		{
			FP05 = 0;
			I_O = SYS_LED;
			switch(POWER_LED) 
			{
				case 1 : P0 = (P0&0XE0)|0X01; break;
				case 2 : P0 = (P0&0XE0)|0X04; break;
				case 3 : P0 = (P0&0XE0)|0X08; break;
				case 4 : P0 = (P0&0XE0)|0X10; break;
				default : break;
			}
			if(FUN_SP)
			P0 = (P0&0XE0);
			for(temp1=0;temp1<100;temp1++);
			FP05 = 1;
		}
	}
}
