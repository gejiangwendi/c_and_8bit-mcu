#include"user.h"

extern bit f_16ms;
extern void pwm_output(void);
extern void init(void);
extern uint	num_16ms;
extern uchar rTx_Ptr;
extern uchar xTx_Buffer[];
void delay(void)
{
	uint i,j,k;
	for(i=0;i<2;i++)
	for(j=0;j<100;j++)
	for(k=0;k<100;k++)
	{}
}

void main()
{
	init();
	while(1)
	{
		if(f_16ms)				//16ms
		{
			f_16ms=0;
			pwm_output();
		}
//		if(rTx_Ptr==0)						//�ж���һ�����ݷ��ꣿ
//		{
//			delay();
//			UARTDR	=	xTx_Buffer[rTx_Ptr];		//���Ϳ�ʼУ���� '0x18'
//			rTx_Ptr++;
//		}
	}
}