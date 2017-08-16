/********************************************************************************************************
File name:		MSP_Byte_RX.c
Author:			Lian_Jin
Email:			lian_jin@sonix.com.cn
Date：			2011/10/25
Description:	Byte Read
********************************************************************************************************/

//-------------------------------------------------------------------------------------------------------
#include	"User.h"
extern	uint	ReadData_Buf;
//-------------------------------------------------------------------------------------------------------

/********************************************************************************************************
 名	称	：void	MSP_Byte_RX(uint RX_Command1,uint RX_Address,uint RX_command2)

功能描述：读取24C01中RX_Address里的数值，存放在ReadData_Buf里
********************************************************************************************************/
void	MSP_Byte_RX(uint RX_Command1,uint RX_Address,uint RX_command2)
{	
//-------------------------------------------------------------------------------------------------------
//	Inital	MSP			
//-------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------
//	Write Device Command		读写之间需要延时10ms
//-------------------------------------------------------------------------------------------------------
	FSEN = 1;
	while(!FMSPIRQ);
	FMSPIRQ = 0;
	MSPBUF = RX_Command1;

	while(!FMSPIRQ);
	FMSPIRQ = 0;
	if(FACKSTAT)			
	{
		goto EXIT_RX; 				
	}
//-------------------------------------------------------------------------------------------------------	
//	写入要读取的地址
//-------------------------------------------------------------------------------------------------------
	MSPBUF = RX_Address;
	while(!FMSPIRQ);
	FMSPIRQ = 0;
	if(FACKSTAT)			
	{
		goto EXIT_RX; 				
	}	 
//-------------------------------------------------------------------------------------------------------
//	写入读取指令
//-------------------------------------------------------------------------------------------------------
	FRSEN = 1;						//ReStart
	while(!FMSPIRQ);
	FMSPIRQ = 0;
	MSPBUF = RX_command2;
	while(!FMSPIRQ);
	FMSPIRQ = 0;
	if(FACKSTAT)			
	{
		goto EXIT_RX;  				
	}	
//-------------------------------------------------------------------------------------------------------
//	数据存入ReadData_Buf,并Stop
//-------------------------------------------------------------------------------------------------------	
	FRCEN = 1;

	while(!FMSPIRQ);
	FMSPIRQ = 0;

	ReadData_Buf = MSPBUF;			//数据存入RX_Buf

 	FACKDT = 1;	///0
	FACKEN = 1;
	while(!FMSPIRQ);
	FMSPIRQ = 0;
//-------------------------------------------------------------------------------------------------------
//	Stop
//-------------------------------------------------------------------------------------------------------

EXIT_RX:

	FPEN = 1;						 
	while(!FMSPIRQ);
	FMSPIRQ = 0;
}

 