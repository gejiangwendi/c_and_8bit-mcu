#include "user.h"

extern bit DECODE;
bit wx_sta; 						//无线信号输入脚的高低电平状态
bit tb_flag; 						//同步码接收成功标志
bit wx_ok; 							//一组无线码接收成功标志
bit L_H;

bit FFFC=0;

uchar wx_data,wx_data0,wx_data1,wx_data2; 	//存储24位无线数据
uchar wx_count,wxcount_buf; 		//低电平时间计数器
uchar wx_bit; 						//无线码位数

void decode(void)
{
	if(!DECODE)
	return;
	DECODE=0;
	if(FP00)								//检测无线I/O口为高
	{ 
		if(!wx_sta) 						//无线信号从低变高
		{  
			L_H=1; 
			wx_sta=1; 						
			wxcount_buf=wx_count; 
			if(tb_flag) 					//同步码标志为1 
			{ 
				if((0x02<wxcount_buf)&&(wxcount_buf<0x09))	//低电平脉宽范围在200us到900us之间
				{ 
					FFFC=1;
				}
				else if((0x0a<wxcount_buf)&&(wxcount_buf<0x14))	//低电平脉宽范围在1.1ms到2ms之间
				{ 
					FFFC=0;
				}
				else						//干扰码
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
				if(++wx_bit==24)	//接收完24位码，接收成功标志wx_ok置1
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
				tb_flag=1; 					//抵电平脉宽范围在13.5ms到20ms之间，把同步码标志置1
				else  
				goto loop2; 
			}
		}
		else {} //持续高电平中
	}
	else 									//检测无线I/O口为低
	{  
		if((!wx_sta))
		{
			if(L_H)
			{
				wx_count++; 						//无线信号为低电平，低电平脉宽计数器加1 
				if(wx_count>180)
				{
					wx_count=0;
					L_H=0;
				}
			}
		}
		else							//判断无线I/O口上一次检测的状态 
		{  
			wx_count=0; 					//无线信号从高变低，清零低电平脉宽计数器
			wx_sta=0; 
		} 
	}
}
