#include "user.h"
#include <stdlib.h>

bit tb_flag; 						//ͬ������ճɹ���־
bit wx_ok; 							//��������ճɹ���־
//bit SUCCESS=0;					//�������������ν��ճɹ���־
bit wx_sta; 						//�����ź�����ŵĸߵ͵�ƽ״̬

bit FFFC=0;

uchar wx_data,wx_data0,wx_data1,wx_data2; 	//�洢24λ��������
uchar wx_count; 					//�ߡ��͵�ƽʱ�������
uchar llcount_buf=0;
uchar hlcount_buf=0;
//uchar wx_num=0;
uchar wx_bit; 						//������λ��

void decode(void)
{
	if(!FP00)								//�������I/O��Ϊ��
	{  
		if(wx_sta)							//�ж�����I/O����һ�μ���״̬ 
		{  
			wx_sta=0; 
			hlcount_buf=wx_count; 
			wx_count=0; 						//�����źŴӸ߱�ͣ�����͵�ƽ���������
		} 
		else //if(!wx_sta)
		wx_count++; 							//�����ź�Ϊ�͵�ƽ���͵�ƽ�����������1 
	}
	else  //if(FP00)							//�������I/O��Ϊ��
	{ 
		if(!wx_sta) 
		{  
			wx_sta=1; 
			llcount_buf=wx_count; 
			wx_count=0; 							//�����źŴӵͱ�ߣ�����ߵ�ƽ���������
			if(tb_flag) 							//ͬ�����־Ϊ1 
			{ 
				if(abs(llcount_buf*3-hlcount_buf)<=25)		//�ߡ��͵�ƽ�����3��1
				{ 
					FFFC=1;
				}
				else if(abs(hlcount_buf*3-llcount_buf)<=25)	//�ߡ��͵�ƽ�����1��3
				{ 
					FFFC=0;
				}
				else						//������
				{
					loop2:
					//wx_num=0;
					wx_count=0;
					wx_bit=0;
					llcount_buf=0;
					hlcount_buf=0;
					tb_flag=0;
					wx_data0=0;
					wx_data1=0;
					wx_data2=0;
					return;
				}
				wx_data2<<=1;
				if(wx_data1&0x80)
				{
					wx_data2|=0X01;
				}
				wx_data1<<=1;
				if(wx_data0&0x80)
				{
					wx_data1|=0X01;
				}	
				wx_data0<<=1;
				if(FFFC)
				{
					wx_data0|=0X01;
				}
				if(++wx_bit==24)				//������24λ�룬���ճɹ���־wx_ok��1
				{
					tb_flag=0;
					wx_bit=0;
					if(wx_data2==0x76 && wx_data1==0xab && (wx_data0&0xf0)==0xA0)
					{
						wx_data=wx_data0&0X0F;
						wx_ok=1;
					}
				}
			} 
			else 		//tb_flag=0;
			{
				if(hlcount_buf!=0 && abs(llcount_buf-hlcount_buf*31)<=80) 
				tb_flag=1; 					//�ߵ͵�ƽ��Ϊ1��31ʱ����ͬ�����־��1 
				else
				{}
			}
		}
		else 			//if(wx_sta)
		{
				wx_count++; 				//�����ź�Ϊ�ߵ�ƽ���ߵ�ƽ�����������1 	
		}
	}
}
