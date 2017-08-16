/*******************************************************************************************************
File name:		27XX_ADC_03.c
Author:			Lian_Jin
Email:			lian_jin@sonix.com.cn
Date��			2011/9/19
Description:	ADC Collected Program
				ADC channel: 			P45					 	
				AD Accuracy��			8  bit  
				Filtering approach ��	Remove the maximum and minimum
				Output Register : 		ADC_Result
________________________________________________________________________________________________________
--------------------------------------------------------------------------------------------------------
				EXT_V00         			Data:	2011/9/22
				Compiler Version��			V141
________________________________________________________________________________________________________
--------------------------------------------------------------------------------------------------------
Copyright (C) 2008
Sonix RomConverter - Version 2.00.001
----------------------------------------
EPROM Check Sum   : 38042 [0x949A] 
Security Check Sum: 18954 [0x4A0A] 
----------------------------------------
Rom total size : 4092 [0xFFC] words
Rom has  used  : 396 [0x18C] words			[composed by: all segments size]
Rom Remains    : 3696 [0xE70] words
---------------------------------------
Ram total size    : 256 [0x100] bytes
RamBank0 has used :  31 [0x1f ] bytes			[composed by: Ram hole + all data segments size]
RamBank0 remains  :  97 [0x61 ] bytes
RamBank1 has used :   0 [0x00 ] bytes			[composed by: Ram hole + all data segments size]
RamBank1 remains  : 128 [0x80 ] bytes
---------------------------------------
���޸ļ�¼����
*******************************************************************************************************/
//------------------------------------------------------------------------------------------------------

#include	"user.h"

#define	uint  	unsigned int
#define	uchar  	unsigned char
#define ulong	unsigned long
#define	AL		10						//The length of the ArrayADC[]; 

uint	DelayTime;
uint	Add_Time;
uint	ADC_Result;
ulong	ADC_Buf;
uint	__RAM	ArrayADC[10] = {0};

void	InitalADC(void);	
void	ADC_Scan(void);
void	ADC_DataAverage(void);

//------------------------------------------------------------------------------------------------------

/*******************************************************************************************************
***********************************************�� �� ��************************************************* 
*******************************************************************************************************/
void	main(void)
{
	InitalADC();
	while(1)
	{
		WDTR = 0x5A;
	
		ADC_Scan();
		
		ADC_DataAverage();
	}
}
/*******************************************************************************************************
*****************************************�жϷ������***************************************************
*******************************************************************************************************/
__interrupt	isr(void)
{
	/***�жϷ������***/
}
/*******************************************************************************************************
ADC ɨ�����	void 	ADC_Scan(void)
�� ��  �� �ܣ�	AD����ɨ��	
				input:P45		output:ADC_Result Register
*******************************************************************************************************/
void	ADC_Scan(void)	
{
	for(Add_Time=0;Add_Time<10;	Add_Time++)	
	{
		FADS = 1;						 			//Start ADC
		while(!FEOC);
		ArrayADC[Add_Time]= ADB;
	}
}
/*******************************************************************************************************
ADC �˲�����	void	ADC_DataAverage(void)
�� ��  �� �ܣ�	����ȥ���ֵ��Сֵ�ķ��� ADC_Result = ADC_buf/8
*******************************************************************************************************/
void	ADC_DataAverage(void)		
{
	uint	i,j,temp;								//ArrayADC[]Ԫ�ذ���������
	for( i=0;i<AL-1;i++)			
	{
		for(j=i+1;j<AL;j++)								
		{
			if(ArrayADC[i]>ArrayADC[j])
			{
				temp = ArrayADC[i];
				ArrayADC[i] = ArrayADC[j];
				ArrayADC[j] = temp;
			}
		}	 
	}
									//�������
	for(i=1;i<=AL-2;i++)
	{
		ADC_Buf += ArrayADC[i];
	}	

	ADC_Result = ADC_Buf>>3;
	ADC_Buf = 0;
}
/*******************************************************************************************************
ADC��ʼ������	void 	InitalADC(void)
��  ��  �� �ܣ�	AD�Ĵ�������
				Input:P45		AD channel��P45
				8 bit ADC 
*******************************************************************************************************/
void	InitalADC(void)
{
	P4CON = 0x20;					//Selected AIN5(P4.5) as ADC I/O Port
	P4M = 0x00;						//Set P4.5 as input state
	P4UR = 0xDF;					//Prohibited P4.5 pull-up resistor
	FADLEN = 0;						//Set Fcpu/1;8-Bit ADC

	ADM = 0X15;						//ѡ��ͨ��5
	FADENB = 1;						//Enable ADC
	NOP(100);
}

