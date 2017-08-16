#include"user.h"

uchar xRx_Buffer[6]; /* [0]��д	[1]λ��	 [2]������ʶ  [3]��ֵ  [4]����ֵ  [5]chk_sum */
uchar Rx_Buffer;
uchar R_count;
uchar RX_ptr;
uchar no_ack_times;
uchar data_fa_times;
uchar counter;
uchar f2_139us;
uchar R_start;
uchar RX_OK;	 
uchar RX_pack_ok;	 
uchar RX_in;

void UART1_Init(void)
{
	UART1_CR2	&=	~0x08;	//ʹ����ʹ�� TEN=1��
	UART1_CR2 &= 	~0x24;	//ʹ����ʹ�� REN=1; RIEN=1;		
	
	UART1_CR1	=		0x00;	//����M�ֳ���8λ����λ
	UART1_CR3	=		0x00;	//1λֹͣλ
	
	UART1_BRR2=		0x00;	//00-0d:9600��fcpu=fmaster=2MHz)
	UART1_BRR1=		0x0d;	//00-1a:4800; 01-34:2400
	
	UART1_CR2	|=	0x48;	//ʹ����ʹ�� TEN=1��TCIEN=1;
	UART1_CR2 |= 	0x24;	//ʹ����ʹ�� REN=1; RIEN=1;
}

void rx_pack(void)
{
	if(RX_OK)
	{
		RX_OK = 0;
		if(RX_in)
		{
			xRx_Buffer[RX_ptr-2] = Rx_Buffer;
			RX_ptr ++;
			if(RX_ptr > 7)
			{
				RX_ptr = 0;
				RX_in = 0;
				RX_pack_ok = 1;	 //���ճɹ� ����xRx_Buffer[6]��[0]��д [1]λ�� [2]������ʶ [3]��ֵ [4]����ֵ [5]chk_sum
			}
		}
		else
		{
			if(Rx_Buffer == 0xaa)
			{
				RX_ptr ++;
				if(RX_ptr == 2)
				{
					RX_in = 1;
				}
			}
			else
			{
				RX_ptr = 0;
			/*	data_fa_times ++;
				if(data_fa_times<5)
				counter = 99; 
				else
				{
					////////////////////////////////////////////init  E1////////////////////////////////////////////
				}  				*/
			}
		}
	}

}