/**********************************************************************************************************
File name:	Isr.c
Author:		Lian_Jin
Email:		lian_jin@sonix.com.cn
Description:
			�жϷ������ 
**********************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------*/

#include	"User.h"

extern 	bit F1ms;
/*-------------------------------------------------------------------------------------------------------*/

__interrupt	isr(void)
{
	if(FTC0IRQ)
	{
		FTC0IRQ = 0;
		F1ms = 1;
	}
}