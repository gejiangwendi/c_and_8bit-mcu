#include	"led.h"

#include	"delay.h"

u8 led_data[4] = {0xda,0x81};
bit led_data_ok = 1;
u8 temp2;
u8 led_cnt;
u8 LED_CODE[12] = { 0xeb,0x81,0xda,0xd9,0xb1,0x79,0x7b,0xc1,0xfb,0xf9 };  // 0~9 
bit	undis_ok;

//***************************************************************************
//! \brief       led��ʾ����
//! \param       ��
//! \return      ��
//***************************************************************************
void led(void)
{
	if(led_data_ok && !un_display)	// ���led��ʾ���������ɣ��Ҳ���Ϩ��״̬
	{
		led_cnt ++;
		switch(led_cnt)
		{
			case 1 :
			{
				led_wr(0xc0);		// ���� led0
				led_wrDATA(led_data[0]);
				break;
			}
			case 2 :
			{
				led_wr(0xc2);		// ���� led1
				led_wrDATA(led_data[1]);
				break;
			}
			case 3 :
			{
				led_wr(0xc8);		// ���� led2 SW RHY SLP
				led_wrDATA(led_data[2]);
				break;
			}
			case 4 :
			{
				led_wr(0xca);		// ���� led3 ECO TIMER
				led_wrDATA(led_data[3]);
				break;
			}
			default :	// led��ʾ������ɣ�cnt����
			{
				led_cnt = 0;
				led_data_ok = 0;	// �� ��ڱ�־λ
			}
		}
	}
	else if(un_display && !undis_ok)	// �������Ϩ��״̬���һ�û��ִ��Ϩ��
	{
//		__asm("nop")
		led_wr(0xc0);	led_wrDATA(0);
		led_wr(0xc2);	led_wrDATA(0);
		led_wr(0xc8);	led_wrDATA(0);
		led_wr(0xca);	led_wrDATA(0);
//		__asm("nop")
		undis_ok = 1;	// Ϩ���ɹ���־λ
	}
}

//***************************************************************************
//! \brief       ʱ����ʾ�Ӻ���
//! \param       ��
//! \return      ��
//***************************************************************************
void time_dsp(void)
{
	if(time_to < 6)						// ��ʱ��С��3 hour������*.*��ʽ��ʾ
	{
		led_data[1] = LED_CODE[time_to/2] | 0x04;	// ʮλ
		led_data[0] = LED_CODE[5*(time_to%2)];		// ��λ
	}
	else if((time_to-3)<10)				// ��ʱ��С��10 hour������*.*��ʽ��ʾ
	{
		led_data[1] = LED_CODE[time_to-3] | 0x04;
		led_data[0] = 0xeb;
	}
	else								// ��ʱ��>=10 hour������**.��ʽ��ʾ
	{
		led_data[1] = LED_CODE[(time_to-3)/10];
		led_data[0] = LED_CODE[(time_to-3)%10] | 0x04;
	}
}

//***************************************************************************
//! \brief       LED��ʾ д��ַ�Ӻ���
//! \param       ��
//! \return      ��
//***************************************************************************
void led_wr(u8 com)
{
	u8 i;
	STB=1;
		delay(4);
	STB=0;
		delay(4);
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(com & 0x01)
		DIO=1;
		else
		DIO=0;
		delay(4);
		com>>=1;
		CLK=1;
		delay(4);
	}
}

//***************************************************************************
//! \brief       LED��ʾ д�����Ӻ���
//! \param       ��
//! \return      ��
//***************************************************************************
void led_wrDATA(u8 dat)
{
	u8 i;
	delay(4);
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(dat & 0x01)
		DIO=1;
		else
		DIO=0;
		delay(4);
		dat>>=1;
		CLK=1;
		delay(4);
	}
}
