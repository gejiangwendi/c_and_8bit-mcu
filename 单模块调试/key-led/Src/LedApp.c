#include	"User.h"
#include	"Led.h"
extern		uint	KeyFIFO;
extern		bit 	FKEY;
extern		bit		key1_flag;
extern		bit		K4_ON;
uint		Keynum=0;
bit			KEY_ON=0;
bit 		k2_chk_3s=0;
/******按键键值转换为Led的亮或灭*****************/

void 	LedApp(void)
{
	if(FKEY==1 && key1_flag==1)			//Key1使能其它按键
	{
		key1_flag = 0;
		FP54 = 1;
	}
 	if(FKEY==0 && key1_flag==1)			//Key1禁止其它按键
	{
		key1_flag = 0;
		FP54 = 0;
		K4_ON=0;
	}
 	if(KeyFIFO==0XFE && KEY_ON==1 && FKEY==1)			//Key2
	{
		Keynum = 2;
		KeyFIFO=0XFF;
		KEY_ON=0;
		k2_chk_3s=1;
	}
 	else if(KeyFIFO==0X0FB && KEY_ON==1 && FKEY==1)			//Key3
	{
		Keynum = 3;
		KeyFIFO=0XFF;
		KEY_ON=0;
	}
 	else if(KeyFIFO==0XF7 && KEY_ON==1 && FKEY==1)			//Key4
	{
		Keynum = 4;
		KeyFIFO=0XFF;
		KEY_ON=0;
	}
}