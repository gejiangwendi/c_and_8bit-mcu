#include	"User.h"
#include	"Key.h"

extern	bit 	KEY_ON;
		bit	Fkeyin;
		bit	FkeyCvtOK;
		bit	F1ms;
		uint	KeyStatus;
		uint	KeyInbuf;
		uint	KeyCvtbuf;
		uint	KeyChkbuf;
		uint	KeyChat;
		uint	KeyFIFO;

/*****读取按键状态，并存相应的键值到KeyFIFO中*****/

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
}