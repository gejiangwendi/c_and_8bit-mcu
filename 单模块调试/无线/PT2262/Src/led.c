#include "user.h"

uint NUM=0;

extern bit wx_ok;
extern uchar wx_data;

void Led_key(void)
{
	if(wx_ok)
	{						
		switch(wx_data)
		{
			case 0x09:		//ON
			{
				FP25=1;
				break;
			}
			case 0x0C:		//OFF
			{
				FP25=0;
				break;
			}
			case 0x08:		//µÆ1
			{
				FP24=~FP24;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}
				
