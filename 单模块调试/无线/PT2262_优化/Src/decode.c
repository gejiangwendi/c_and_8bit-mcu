#include "user.h"
#include <stdlib.h>

bit tb_flag; 						//同步码接收成功标志
bit wx_ok; 							//无线码接收成功标志
//bit SUCCESS=0;					//无线码连续三次接收成功标志
bit wx_sta; 						//无线信号输入脚的高低电平状态

bit FFFC=0;

uchar wx_data,wx_data0,wx_data1,wx_data2; 	//存储24位无线数据
uchar wx_count; 					//高、低电平时间计数器
uchar llcount_buf=0;
uchar hlcount_buf=0;
//uchar wx_num=0;
uchar wx_bit; 						//无线码位数

void decode(void)
{
	if(!FP00)								//检测无线I/O口为低
	{  
		if(wx_sta)							//判断无线I/O口上一次检测的状态 
		{  
			wx_sta=0; 
			hlcount_buf=wx_count; 
			wx_count=0; 						//无线信号从高变低，清零低电平脉宽计数器
		} 
		else //if(!wx_sta)
		wx_count++; 							//无线信号为低电平，低电平脉宽计数器加1 
	}
	else  //if(FP00)							//检测无线I/O口为高
	{ 
		if(!wx_sta) 
		{  
			wx_sta=1; 
			llcount_buf=wx_count; 
			wx_count=0; 							//无线信号从低变高，清零高电平脉宽计数器
			if(tb_flag) 							//同步码标志为1 
			{ 
				if(abs(llcount_buf*3-hlcount_buf)<=25)		//高、低电平脉宽比3：1
				{ 
					FFFC=1;
				}
				else if(abs(hlcount_buf*3-llcount_buf)<=25)	//高、低电平脉宽比1：3
				{ 
					FFFC=0;
				}
				else						//干扰码
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
				if(++wx_bit==24)				//接收完24位码，接收成功标志wx_ok置1
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
				tb_flag=1; 					//高低电平比为1：31时，把同步码标志置1 
				else
				{}
			}
		}
		else 			//if(wx_sta)
		{
				wx_count++; 				//无线信号为高电平，高电平脉宽计数器加1 	
		}
	}
}
