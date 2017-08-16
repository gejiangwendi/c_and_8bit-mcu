#include	"user.h"
#include <stdlib.h>

extern bit		KEY_ON;
extern bit		KEY_ON_3s;
extern uint		KeyFIFO;
extern bit		DSP_OFF;
extern bit		BUZZER1_ON;

bit tb_flag; 				//同步码接收成功标志
bit wx_sta; 				//无线信号输入脚的高低电平状态
bit FFFC;
bit wx_ok;
bit wx_ok2;

uint wx_data,wx_data1,wx_data2; 	//存储16位无线数据
uint wx_count; 			//高、低电平时间计数器
uint llcount_buf;
uint hlcount_buf;
uint wx_bit; 				//无线码位数
uint temp3,temp4;

bit f_01ms;					

void hwjc(void)
{
	if(f_01ms)
	{
		f_01ms = 0;	
		if(!wx_ok2)
		{
			if(!HW_dat)			//检测无线I/O口为低
			{  
				if(wx_sta)		//判断无线I/O口上一次检测的状态 
				{  
					wx_sta=0; 
					hlcount_buf=wx_count; 
					wx_count=0; 	//无线信号从高变低，清零低电平脉宽计数器
					if(tb_flag) 	//同步码标志为1 
					{ 
						if(abs(llcount_buf/3-hlcount_buf)<=2)		//高、低电平脉宽比3：1
						{ 
							FFFC=0;
						}
						else if(abs(hlcount_buf/3-llcount_buf)<=2)	//高、低电平脉宽比1：3
						{ 
							FFFC=1;
						}
						else		//干扰码
						{
							loop2:
							//wx_num=0;
							wx_count=0;
							wx_bit=0;
							llcount_buf=0;
							hlcount_buf=0;
							tb_flag=0;
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
						if(FFFC)
						{
							wx_data1|=0X01;
						}
						if(++wx_bit==11)
						{
							tb_flag=0;
							wx_bit=0;
							if((wx_data2&0x07)==0x01)
							{
								wx_ok2 = 1;
								switch(wx_data1)
								{
									case 0x3f : KeyFIFO = 5; KEY_ON = 1; break;
									case 0x3e : KeyFIFO = 1; KEY_ON = 1; break;
									case 0x3b : KeyFIFO = 3; KEY_ON = 1; break;
									case 0x19 : KeyFIFO = 5; KEY_ON_3s = 1; wx_ok = 1; break;
									default : {KeyFIFO = 0;}
								}
								if(DSP_OFF && KeyFIFO!=0)
								{
									KEY_ON = 0;
									KEY_ON_3s=0;
									DSP_OFF	= 0;
									BUZZER1_ON = 1;
								}
							
							}
						}
					} 
					else  //if tb_flag=0;
					{
						if((hlcount_buf>60)&&(hlcount_buf<90)&&(llcount_buf>2)&&(llcount_buf<20))
						tb_flag=1; 			//高低电平比为1：31时，把同步码标志置1 
					}
				} 
				else //if(!wx_sta)
				wx_count++; 				//无线信号为低电平，低电平脉宽计数器加1 
			}
			else  //if(HW_dat)				//检测无线I/O口为高
			{ 
				if(!wx_sta) 
				{  
					wx_sta=1; 
					llcount_buf=wx_count; 
					wx_count=0; 			//无线信号从低变高，清零高电平脉宽计数器
				}
				else 			//if(wx_sta)
				{
						wx_count++; 		//无线信号为高电平，高电平脉宽计数器加1 	
				}
			}
		}
		else
		{
			temp3++;
			if(temp3 == 100)	//10ms
			{
				temp4++;
				if(temp4 == 10)
				{
					temp4=0;
					wx_ok2 = 0;
				}
			}
		}
	}
}
