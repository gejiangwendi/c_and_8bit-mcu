#include		"MC96F8316.h"
#define uint	unsigned int
#define uchar	unsigned char
#define BUSY 	P25	  //in
#define DATA 	P34	  //out
#define CLK 	P35	  //out
uint	xdata	Ctrl_buf[]	={	0xFE01,	//��ӭʹ�þ�׵����׵�����ǣ���ѡ������ʱ��
									0xFD02,	//��ӭʹ�ú�һ����׵����׵�����ǣ���ѡ������ʱ��
									0xFC03,	//5���ӣ���׵������ѡ����ѡ�����Ʒ���
									0xFB04,	//20���ӣ���׵������ѡ����ѡ�����Ʒ���
									0xFA05,	//25���ӣ���׵������ѡ����ѡ�����Ʒ���
									0xF906,	//30���ӣ���׵������ѡ����ѡ�����Ʒ���
									0xF807,	//15���ӣ�����������ѡ����ѡ�����Ʒ���
									0xF708,	//20���ӣ�����������ѡ����ѡ�����Ʒ���
									0xF609,	//25���ӣ�����������ѡ����ѡ�����Ʒ���
									0xF50A,	//30���ӣ�����������ѡ����ѡ�����Ʒ���
									0xF40B,	//�Զ����������������ǿ�ȡ�
									0xF30C,	//��ģ����������ǿ�ȡ�
									0xF20D,	//�������������ǿ�ȡ�
									0xF10E,	//��ޣ����������ǿ�ȡ�
									0xF00F,	//���ã����������ǿ�ȡ�
									0xEF10,	//��Ħ�����������ǿ�ȡ�
									0xEE11,	//���������������ǿ�ȡ�
									0xED12,	//�����Ⱦĵ���
									0xEC13,	//�����Ⱦĵ��¡�����������
									0xEB14,	//�����Ⱦ�����
									0xEA15,	//�����Ⱦĸ��£�����������¶���������Ƥ����
									0xE916,	//�����ȾĹر�
									0xE817,	//�����Ⱦġ��������ر�
									0xE718,	//��������
									0xE619,	//�����ر�
									0xE51A,	//��ȷ�ϵ缫�Ƿ���ȷ����
									0xE41B,	//��ȷ�����Է�ʽ�Ƿ���ȷ
									0xE31C,	//��·�쳣�����ܼ�����
									0xE21D,	//���ܼ��޽�������������ʹ��
									0xE11E,	//��·�쳣���ѹر�
									0xE01F,	//��·�쳣����رյ�Դ
									0xDF20,	//�¶ȸߣ���ȷ��
									0xDE21,	//�����쳣����رյ�Դ
									0xDD22,	//�������������缫
									0xDC23,	//��ȷ���ֿ����Ƿ���ȷ����
									0xDB24,	//�����ѽ�����ллʹ��
									0xDA25,	//��ӭʹ�þ�׵����׵�����ǣ��Լ��У���ȴ�
									0xD926,	//��ӭʹ�ú�һ����׵����׵�����ǣ��Լ��У���ȴ�
									0xD827,	//�Լ�����ɣ���ѡ������ʱ��
									0xD728,	//ǿ��1
									0xD629,	//ǿ��2
									0xD52A,	//ǿ��3
									0xD42B,	//ǿ��4
									0xD32C,	//ǿ��5
									0xD22D,	//ǿ��6
									0xD12E,	//ǿ��7
									0xD02F,	//ǿ��8
									0xCF30,	//ǿ��9
									0xCE31,	//ǿ��10
									0xCD32,	//ǿ��11
									0xCC33,	//ǿ��12
									0xCB34,	//ǿ��13
									0xCA35,	//ǿ��14
									0xC936,	//ǿ��15
									0xC837,	//ལ�������
									0xC738,	//ལ�������
									0xC639	//��
									};
uchar	j_static	=	0;
uint	ctr_buf		=	0xFFF1;
uchar	i_static;
uchar	clk_num;
uchar	num_1s;
uint	num_500us;

bit		f_1s		=	0;
bit		start_on	=	0;
bit 	stop_on		=	0;
bit 	start		=	0;
bit		wr_in		=	0;
bit 	f_500us		=	0;
void write_speak(void)	/*����ʱ wr_in=1;ctr_buf=Ctrl_buf[*]*/
{
	if(wr_in)			
	{
		if(stop_on)
		{
			i_static++;
			if(i_static == 4)
			{
				i_static=0;
				CLK=1;
				wr_in=0;
				stop_on=0;
				start=0;
			}
		}
		else if(!start_on && start)
		{
			clk_num++;
			if(clk_num<31)
			{
				if(clk_num%2 == 1)
				{
					CLK=0;
		 			if(ctr_buf & 0x8000)	 
					DATA=1;
					else
					DATA=0;
					ctr_buf<<=1;
				}
				else
				{
					CLK=1;
				}
			}
			else if(clk_num == 31)
			{
				CLK=0;
				stop_on=1;
			}
		}
		else if(start_on)
		{
			i_static++;
			if(i_static == 20)
			{
				i_static=0;
				start_on=0;
				start=1;
				CLK=1;
			}
		}
		else if(!start)
		{
 			if(ctr_buf & 0x8000)	 
				DATA=1;
			else
				DATA=0;
			ctr_buf<<=1;
			CLK=0;
			start_on=1;
		}
	}
}

void main()
{
	P2IO    &=	~0x20;		// in
	P3IO    |=	0x30;		// out
	CLK=1;
	DATA=1;
	T0CR	=	0x80;
	T0CR	|=	0x03;		//Fx/4->4us
	T0DR	=	0x83;		//4us*125=500us  125/0.95372=131
    IE2     = 	0x02;		//T0	en
    EA      = 	1;
	while(1)
	{
		if(f_500us)
		{
			f_500us=0;
			write_speak();
		}
		if(f_1s)	// 3s
		{
			f_1s=0;
			num_1s++;
			if(num_1s == 5)
			{
				num_1s=0;
				j_static += 1;
				if(j_static == 57)
				j_static = 0;
				ctr_buf=Ctrl_buf[j_static];
				wr_in=1;
			}
		}
	}
}
void T0_Int_Handler(void) interrupt 13 using 1
{
	f_500us		=	1;
	num_500us++;
	if(num_500us == 2000)  // 1s
	{
		num_500us	=	0;
		f_1s=1;
	}
}
