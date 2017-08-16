#include "timeflag.h"

u8	num250us;
u8	num10ms;
u8	num50ms;

bit f10ms;		
bit f10ms_2;		
bit f1_50ms;
bit f2_50ms;
bit f_500ms;
	
//***************************************************************************
//! \brief       ʱ���־���� 
//! \param       ��
//! \return      ��
//***************************************************************************
void TimeFlag (void)
{
	if(f025ms)
	{
		f025ms = 0;
		num250us ++;
		if(num250us == 40)
		{
			num250us =	0;
			f10ms	=	1;
			f10ms_2 =	1;
			num10ms ++;
			if(num10ms == 5)
			{
				num10ms = 0;
				f2_50ms = 1;
				f1_50ms = 1;
				num50ms++;
				if(num50ms == 10)
				{
					num50ms = 0;
					f_500ms = 1;
				}
			}
		}
	}
}
