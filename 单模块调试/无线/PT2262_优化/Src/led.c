#include "user.h"

extern uchar wx_data;
extern bit wx_ok;	

void Led_key(void)
{
	if(wx_ok)
	{
		
		wx_ok=0;
		switch(wx_data)
		{
			case 0x09:		//ON
			{
				FP22=1;
				break;
			}
			case 0x0C:		//OFF
			{
				FP22=0;
				break;
			}
			case 0x08:		//��1
			{
				FP23=~FP23;
				break;
			}
			case 0x04:		//��2
			{
				FP24=~FP24;
				break;
			}
			case 0x01:		//��3
			{
				FP25=~FP25;
				break;
			}
			case 0x02:		//��
			{

				break;
			}
			case 0x06:		//��
			{

				break;
			}
			case 0x05:		//��
			{

				break;
			}
			case 0x03:		//��
			{

				break;
			}
			default  :{}
		}
	}
}