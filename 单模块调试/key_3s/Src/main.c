#include	<SN8P2501B.h>

#define		uint	unsigned int
#define		uchar	unsigned char

bit 	F1ms;
bit 	F1ms_2;
bit 	key_lock;

bit		Fkeyin;
bit		FkeyCvtOK;
uint	KeyStatus;
uint	KeyInbuf;
uint	KeyCvtbuf;
uint	KeyChkbuf;
uint	KeyChat;
uint	KeyFIFO;

bit		BUZZER_ON=0;
bit		FBUZZER=0;
uint 	b_time=0;
bit		BUZZER_3S=0;
uint 	LONG_BUZZER_TIME;

uint	Keynum=0;
bit		KEY_ON=0;
bit 	k2_chk_3s=0;

int 	led_left=0;
int 	led_right=3;
int 	P2_TEMP[]={0x06,0x05,0x03,0x0f,0x17,0x27};
int 	P2_temp;
int 	led_T1=0;
int 	led_T2=0;
int 	k2_T0_i=0;
int 	k2_T0_j=0;
int 	led_cir=0;

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
				BUZZER_ON=0;
				if(BUZZER_3S && LONG_BUZZER_TIME>0)
				{
					BUZZER_ON=1;
					LONG_BUZZER_TIME--;
					if(LONG_BUZZER_TIME==0)
					{
						BUZZER_3S=0;
					}
				}
			}
		}
	}
}

void	KeyScan(void)
{
	KeyInbuf = P1;
	if(KeyChkbuf != KeyInbuf)	
	{	
		KeyChkbuf = KeyInbuf;
		Fkeyin = 1;
		KeyChat = 20;
	}
	if(Fkeyin && (KeyChat==0))							 
	{
		Fkeyin  = 0;
		FkeyCvtOK = 1;
		KeyCvtbuf = KeyChkbuf;
	}
	if(FkeyCvtOK)
	{
		FkeyCvtOK = 0;
		KeyFIFO = KeyCvtbuf;
		KEY_ON=1;
	}			

	if(F1ms ==1)
	{
		F1ms = 0;
		if(Fkeyin && KeyChat)
		{
			KeyChat--;		
		}
	}	
}

void 	LedApp(void)
{
 	if(KeyFIFO==0XFE && KEY_ON==1)			//Key2
	{
		if(!key_lock)
		{
			Keynum = 2;
			KeyFIFO=0XFF;
			KEY_ON=0;
			BUZZER_ON=1;
		}
		k2_chk_3s=1;
	}
 	else if(KeyFIFO==0X0FB && KEY_ON==1)			//Key3
	{
		if(!key_lock)
		{
			Keynum = 3;
			KeyFIFO=0XFF;
			KEY_ON=0;
			BUZZER_ON=1;
		}
	}
}

void KeyProcess(void)
{
	if(Keynum!=0)
	{
		if(Keynum==2)
		{
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
		Keynum = 0;
	}

}

void key3s(void)
{
	if(F1ms_2) 
	{
		
		if(k2_chk_3s && !key_lock && FP10==0)
		{
			F1ms_2=0;
			if((++k2_T0_i)==100)			//25ms
			{
				k2_T0_i=0;
				if(++k2_T0_j==20)
				{
					k2_T0_j=0;
					k2_chk_3s=0;
					key_lock=1;
					BUZZER_ON=1;
					BUZZER_3S=1;
					LONG_BUZZER_TIME=10;
					P2_temp=P2;
					P2=0X07;

				}
			}
		}
		else if(k2_chk_3s && key_lock && FP10==0)
		{
			F1ms_2=0;
			if((++k2_T0_i)==100)		
			{
				k2_T0_i=0;
				if(++k2_T0_j==20)
				{
					k2_T0_j=0;
					k2_chk_3s=0;
					key_lock=0;
					BUZZER_3S=1;
					LONG_BUZZER_TIME=10;
					P2=P2_temp;
				}
			}
		}
		else k2_chk_3s=0;
	} 
}

int main(void)
{
/*---------------Inital I/O---------------------*/
	P1M 	=	0X00;		//key234为输入
	P1UR 	=	0XFF;		//使能上拉电阻

	P2M	=	0xFF;		//led为输出
	P2UR	= 	0X00;

	P5M		=	0XFF;
	P5UR	=	0X00;

	P2  	=	0X07;
/*---------------Inital TC0-----1ms-------------*/
	TC0C	=	 6;
	TC0R	=	 6;
	TC0M	=     0XD4;
	FTC0IEN = 	 1;
	FTC0ENB =	 1;
/*---------------Inital T0------0.125MS---------*/
	FT0ENB=0;		//buzzer
	FT0IEN=0;
	FT0IRQ=0;
	T0M=0x60;		// fcpu/4
	FT0TB =0;
	T0C=0xf8;		//0.125ms >> 4kHZ
	FT0IEN=1;
 	FT0ENB=1;

	FGIE=1;			//使能总中断
	while(1)
	{
		WDTR = 0x5A;
		KeyScan();
		LedApp();
		key3s();
		KeyProcess();
		Buzzer();
	}

	return 0;
}
void __interrupt [0x08] isr(void)
{
	if(FTC0IRQ)
	{
		FTC0IRQ = 0;
		F1ms = 1;
		F1ms_2=1;
	}
	if(FT0IRQ)			//8kHZ 0.125MS
	{
		FT0IRQ = 0;
		if(BUZZER_ON)
		{
			FP54=~FP54;
		}
		FBUZZER = 1;
	}
}
