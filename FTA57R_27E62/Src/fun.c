#include	"fun.h"

bit     f_1ms;
bit    f_10ms;
bit   f2_10ms;
bit      f_1s;

u8     num_1s;
u8     t0_num;
u8    num_1ms;
u8   num_10ms;
u8 nature_cnt;

u8    slp_cnt;
bit    sysbuf;
bit sys_3s_ok;
u8 	  num2_1s;
bit     swbuf;
u8 	 speedbuf;
bit     swbuf;

/****************************************************************************
 * \brief       ������ƺ���
 *        		���� ION SW MODE
 * \param       ��
 * \return      ��
 * *************************************************************************/
void Fun (void)
{
	if(sys_on)
	{
	 	if(sysbuf != sys_on)
		sysbuf = sys_on;
		if(!sys_3s_ok)
		{
			if(f_1s)
			{
				f_1s = 0;
				num2_1s++;
				if(num2_1s == 1)
				{
					H_M_L_OUT(2);
					speedbuf = 2;
				}
				else if(num2_1s == 3)
				{
					sys_3s_ok = 1;
					num2_1s = 0;
				}
			}
		}
		else
		{
			if(mode == 1 || mode == 2)
			{
				Nature_Out(speed);
			}
			else if(mode == 3)
			{
			}
			else if(mode == 4)
			{
				if(speedbuf != speed)
				{
					speedbuf = speed;

					H_M_L_OUT(speed);

				}
			}
		}
		if(swbuf != sw_on)
		{
			swbuf = sw_on;
			if(!sw_on)		SW_OUT = 1;
			else		SW_OUT = 0;
		}
	}
	else
	{
		if(sysbuf != sys_on)
		{
			sysbuf = sys_on;
			H_M_L_OUT(0);
		}
	}
}

//***************************************************************************
//! \brief       ���� �������
//! \param       spd ������ǿ�� 1 - �� 2 - �� 3 - ǿ ����ֵ - �����
//! \return      ��
//***************************************************************************
void H_M_L_OUT(u8 spd)
{
	H_OUT	=	1;
	M_OUT	=	1;
	L_OUT	=	1;
	switch(spd)
	{
		case 1 :
		{
			L_OUT	=	0;
			break;
		}
		case 2 :
		{
			M_OUT	=	0;
			break;
		}
		case 3 :
		{
			H_OUT	=	0;
			break;
		}
		default :
		{
			;
		}
	}
}

//***************************************************************************
//! \brief       ���� ��Ȼ���������
//! \param       speed �趨�ķ���ֵ
//! \return      ��
//***************************************************************************
void Nature_Out(u8 spd_)
{
	if(f_1s)
	{
		f_1s = 0;
		num_1s++;
		if(num_1s == 25)
		{
			num_1s = 0;
			nature_cnt++;
			if(nature_cnt >= 32)	// 25s * 32 = 800s
			{
				nature_cnt = 0;
				slp_cnt ++;
				if(slp_cnt > 1)		// �೤ʱ��˯��ģʽ��ǿ�Ƚ�һ��
				{
					slp_cnt = 0;
					if(mode == 2 && spd_ > 1)
					{
						spd_ -= 1;
						////////////////////////////////////////time_speed_dsp(1);
					}
				}
			}
								if(spd_ == 3)
								switch(nature_cnt)
								{
									case 0 :
									case 6 :
									case 10 :
									case 15 :
									case 19 :
									case 22 :
									case 27 :
									{
										H_M_L_OUT(3);
										break;
									}
									case 2 :
									case 8 :
									case 12 :
									case 24 :
									{
										H_M_L_OUT(2);
										break;
									}
									case 4 :
									case 17 :
									case 20 :
									case 30 :
									{
										H_M_L_OUT(1);
										break;
									}
									default : {}
								}
								else if(spd_ == 2)
								switch(nature_cnt)
								{
									case 4 :
									case 10 :
									case 15 :
									case 23 :
									{
										H_M_L_OUT(3);
										break;
									}
									case 0 :
									case 5 :
									case 12 :
									case 19 :
									case 24 :
									case 29 :
									{
										H_M_L_OUT(2);
										break;
									}
									case 2 :
									case 8 :
									case 17 :
									case 22 :
									case 27 :
									case 31 :
									{
										H_M_L_OUT(1);
										break;
									}
									default : {}
								}
								else if(spd_ == 1)			
								switch(nature_cnt)
								{
									case 6 :
									case 22 :
									{
										H_M_L_OUT(3);
										break;
									}
									case 2 :
									case 10 :
									case 14 :
									case 20 :
									case 27 :
									case 31 :
									{
										H_M_L_OUT(2);
										break;
									}
									case 0 :
									case 4 :
									case 8 :
									case 12 :
									case 17 :
									case 24 :
									case 29 :
									{
										H_M_L_OUT(1);
										break;
									}
									default : {}
								}
		}
	}
}

//***************************************************************************
//! \brief       ���� ʱ���־λ����
//! \param       ��
//! \return      ��
//***************************************************************************
void Time_Flag(void)
{
	if(f_dt)
	{
		f_dt = 0;
		f2_dt = 1;
		t0_num++;
		if(t0_num == 8)
		{
			t0_num = 0;
			f_1ms = 1;
			num_1ms++;
			if(num_1ms == 10)
			{
				num_1ms = 0;
				f_10ms = 1;
				num_10ms++;
				if(num_10ms == 100)
				{
					num_10ms = 0;
					f_1s = 1;
				}
			}
		}
	}
}

//***************************************************************************
//! \brief       ��ʱ����
//! \param       nms ��ʱ��ms��
//! \return      ��
//***************************************************************************
void Delay_ms(u8 nms)		
{
	volatile u8 i;
	volatile u8 j;
	for(i=0;i<nms;i++)
	{
		WDTR = 0x5A;
		for(j=0;j<135;j++)
		{
			;
		}
	}
}
