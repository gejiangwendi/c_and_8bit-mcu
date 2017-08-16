#include	<SN8P2501B.h>
#define		uint	unsigned int
#define		uchar	unsigned char

bit 	f1ms=0;
uint 	num=0;
int 	t=0;
uint 	i=0;
bit 	F1ms;
bit 	F1ms_2;

bit		Fkeyin;
bit		FkeyCvtOK;
uint	KeyStatus;
uint	KeyInbuf;
uint	KeyCvtbuf;
uint	KeyChkbuf;
uint	KeyChat;
uint	KeyFIFO;

uint	Keynum=0;
bit		KEY_ON=0;
int 	k2_T0_i=0;
int 	k2_T0_j=0;
/*---------------按键扫描-------------------*/
void KeyScan(void)
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
/*---------------键值判断-------------------*/
void LedApp(void)
{
 	if(KEY_ON==1)
	{
		if(KeyFIFO==0XFE)
		{
			Keynum = 2;					//Key2
			KeyFIFO=0XFF;
			KEY_ON=0;
		}
	 	else if(KeyFIFO==0XFB)
		{
			Keynum = 3;					//Key3
			KeyFIFO=0XFF;
			KEY_ON=0;
		}
		else
		{
			KEY_ON=0;
		}
	}
}
/*------------基于按键的脉宽调制------------*/
void KeyProcess(void)
{
	if(Keynum==2)
	{
		Keynum = 0;
		t+=2;
		if(t>=12)
		t=10;
	}
	else if(Keynum==3)
	{
		Keynum = 0;
		t-=2;
		if(t<=0)
		t=0;
	}
}
/*------------基于脉宽调制的LED--------------*/
void led(void )
{
	if(f1ms)
	{
		f1ms=0;
		num++;
		if(num>=t)
		{
			P2=0X07;
		}
		if(num>=10)
		{
			if(t!=0)
			P2=0XF8;
			num=0;
		}
	}
}

int main(void)
{
/*---------------I/O口初始化-------------------*/
	P1M		=	0x00;
	P1UR	=	0Xff;
	P2M		=	0xff;
	P2UR	=	0Xff;
	P2		=	0XF8;
/*----------------TC0初始化--------------------*/
	TC0C	=	0x83;				// 1ms
	TC0R	=	0x83;
	TC0M	=   0Xd4;
	FTC0IEN = 	1;
	FTC0ENB =	1;
	FGIE	=	1;					// 使能总中断
/*-------------------主循环程序-----------------*/
	while(1)
	{
		WDTR = 0x5A;
		led();
		KeyScan();
		LedApp();
		KeyProcess();
	}
	return 0;
}
/*------------------中断服务程序----------------*/
void __interrupt [0x08] isr(void)
{

	if(FTC0IRQ)			// 1ms
	{
		FTC0IRQ = 0;
		f1ms=1;
		F1ms = 1;
		F1ms_2=1;
	}
}
