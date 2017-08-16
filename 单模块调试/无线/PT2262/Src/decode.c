#include "user.h"

extern bit DECODE;
bit wx_sta; 						//�����ź�����ŵĸߵ͵�ƽ״̬
bit tb_flag; 						//ͬ������ճɹ���־
bit wx_ok; 							//һ����������ճɹ���־
bit L_H;

bit FFFC=0;

uchar wx_data,wx_data0,wx_data1,wx_data2; 	//�洢24λ��������
uchar wx_count,wxcount_buf; 		//�͵�ƽʱ�������
uchar wx_bit; 						//������λ��

void decode(void)
{
	if(!DECODE)
	return;
	DECODE=0;
	if(FP00)								//�������I/O��Ϊ��
	{ 
		if(!wx_sta) 						//�����źŴӵͱ��
		{  
			L_H=1; 
			wx_sta=1; 						
			wxcount_buf=wx_count; 
			if(tb_flag) 					//ͬ�����־Ϊ1 
			{ 
				if((0x02<wxcount_buf)&&(wxcount_buf<0x09))	//�͵�ƽ����Χ��200us��900us֮��
				{ 
					FFFC=1;
				}
				else if((0x0a<wxcount_buf)&&(wxcount_buf<0x14))	//�͵�ƽ����Χ��1.1ms��2ms֮��
				{ 
					FFFC=0;
				}
				else						//������
				{
					loop2:
					wx_count=0;
					wx_bit=0;
					wxcount_buf=0;
					tb_flag=0;
					return;
				}
				if(wx_bit>=16)
				{
					wx_data2<<=1;
					if(wx_data1&0x80)
					{
						wx_data2|=0X01;
					}
				}
				if(wx_bit>=8)
				{
					wx_data1<<=1;
					if(wx_data0&0x80)
					{
						wx_data1|=0X01;
					}	
				}
				wx_data0<<=1;
				if(FFFC)
				{
					wx_data0|=0X01;
				}
				if(++wx_bit==24)	//������24λ�룬���ճɹ���־wx_ok��1
				{
					tb_flag=0;
					wx_bit=0;
					if(wx_data2==0x76 && wx_data1==0xab && (wx_data0&0xf0)==0xA0)
					{
						wx_ok=1;
						wx_data=wx_data0&0x0f;
					}
					else goto loop2;
				}
			} 
			else
			{
				if((0x5B<wxcount_buf)&&(wxcount_buf<0x9B)) 
				tb_flag=1; 					//�ֵ�ƽ����Χ��13.5ms��20ms֮�䣬��ͬ�����־��1
				else  
				goto loop2; 
			}
		}
		else {} //�����ߵ�ƽ��
	}
	else 									//�������I/O��Ϊ��
	{  
		if((!wx_sta))
		{
			if(L_H)
			{
				wx_count++; 						//�����ź�Ϊ�͵�ƽ���͵�ƽ�����������1 
				if(wx_count>180)
				{
					wx_count=0;
					L_H=0;
				}
			}
		}
		else							//�ж�����I/O����һ�μ���״̬ 
		{  
			wx_count=0; 					//�����źŴӸ߱�ͣ�����͵�ƽ���������
			wx_sta=0; 
		} 
	}
}
