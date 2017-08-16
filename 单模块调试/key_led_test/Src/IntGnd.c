#include	"User.h"
#include 	"Key.h"
#include	"IntGnd.h"

extern 	bit		F1ms;
extern	bit		Fkeyin;
extern	uint	KeyChat;

/***************°´¼üÏû¶¶¶¯*********************/

void	DeKeychat(void)
{
	if(F1ms ==1)
	{
		F1ms = 0;
		if(Fkeyin && KeyChat)
		{
			KeyChat--;		
		}
	}	
}