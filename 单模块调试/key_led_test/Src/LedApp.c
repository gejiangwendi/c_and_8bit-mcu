#include	"User.h"
#include	"Led.h"
extern		uint	KeyFIFO;
extern		bit 	FKEY;
extern		bit		key1_flag;
uint		Keynum=0;
bit			KEY_ON=0;

/******������ֵת��ΪLed��������*****************/

void 	LedApp(void)
{
 	if(FKEY==1 && key1_flag==1)			//Key1ʹ����������
	{
		key1_flag = 0;
		FP54 = 1;
	}
 	if(FKEY==0 && key1_flag==1)			//Key1��ֹ��������
	{
		key1_flag = 0;
		FP54 = 0;
	}
 	if(KeyFIFO==0XFE && KEY_ON==1 && FKEY==1)			//Key2
	{
		Keynum = 2;
		KeyFIFO=0XFF;
		KEY_ON=0;

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