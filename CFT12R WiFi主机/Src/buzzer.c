#include "user.h"

void buzzer(void)
{
	/**************����TC0OUT��P5.4��**************/
	TC0M = 0x60;	//TC0����=Fcpu/4
	TC0C = 131;		//�Զ����زο�ֵ����
	TC0R = 131;
	FTC0OUT = 1;	//TC0������ź���P5.4�������ֹP5.4����ͨI/O����
	FALOAD0 = 1;	//ʹ��TC0�Զ�װ�ع���
	FTC0ENB = 1;	//����TC0��ʱ��
}

