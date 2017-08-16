#include	"User.h"
#include	"Key.h"
#include	"KeyProcess.h"
#include	"Led.h"
#include	"IntGnd.h"
#include	"InitalSys.h"
#include	"Buzzer.h"

extern	uint	KeyInbuf;
extern	uint	KeyChkbuf;
extern	uint	KeyFIFO;
extern 	uint	Keynum;
extern	bit		F1ms;
extern 	bit		BUZZER_ON;
extern 	bit		FBUZZER;
extern 	bit		KEY_ON;

/**********Ö÷ ³Ì Ðò**********/

void main(void)
{
	InitalSystem();
	Premain();
	while(1)
	{
		WDTR = 0x5A;
		KeyScan();
		DeKeychat();
		LedApp();
		KeyProcess();
		Buzzer();
	}
}