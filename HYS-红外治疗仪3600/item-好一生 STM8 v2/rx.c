#include"user.h"

uchar xRx_Buffer[6]; /* [0]读写	[1]位数	 [2]按键标识  [3]键值  [4]修正值  [5]chk_sum */
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
	UART1_CR2	&=	~0x08;	//使发送使能 TEN=1；
	UART1_CR2 &= 	~0x24;	//使接收使能 REN=1; RIEN=1;		
	
	UART1_CR1	=		0x00;	//设置M字长，8位数据位
	UART1_CR3	=		0x00;	//1位停止位
	
	UART1_BRR2=		0x00;	//00-0d:9600（fcpu=fmaster=2MHz)
	UART1_BRR1=		0x0d;	//00-1a:4800; 01-34:2400
	
	UART1_CR2	|=	0x48;	//使发送使能 TEN=1；TCIEN=1;
	UART1_CR2 |= 	0x24;	//使接收使能 REN=1; RIEN=1;
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
				RX_pack_ok = 1;	 //接收成功 存于xRx_Buffer[6]：[0]读写 [1]位数 [2]按键标识 [3]键值 [4]修正值 [5]chk_sum
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