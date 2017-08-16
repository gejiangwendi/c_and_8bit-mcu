#include "user.h"

void buzzer(void)
{
	/**************设置TC0OUT（P5.4）**************/
	TC0M = 0x60;	//TC0速率=Fcpu/4
	TC0C = 131;		//自动加载参考值设置
	TC0R = 131;
	FTC0OUT = 1;	//TC0的输出信号由P5.4输出，禁止P5.4的普通I/O功能
	FALOAD0 = 1;	//使能TC0自动装载功能
	FTC0ENB = 1;	//开启TC0定时器
}

