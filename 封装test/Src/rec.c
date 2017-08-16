#include	"rec.h"

//***************************************************************************
//! \brief       �������ģ��
//! \Call        125 us
//***************************************************************************

u16 REC_data;
u8  REC_bit_cnt;

bit REC_tb;
bit REC_sta;
bit REC_BIT_chk;
u8 REC_count;
u8 REC_L_cnt_buf;
u8 REC_H_cnt_buf;

void rec(void)
{
	if(!REC)			
	{  
		if(REC_sta) // H -> L
		{  
			REC_sta=0; 
			REC_H_cnt_buf = REC_count; 
			REC_count=0;
			if(REC_tb) 	
			{ 
				if(REC_L_cnt_buf > REC_H_cnt_buf)
				{ 
					REC_BIT_chk = 1;
				}
				else if(REC_H_cnt_buf > REC_L_cnt_buf)
				{ 
					REC_BIT_chk = 0;
				}
				else		
				{
ERROR:				REC_bit_cnt = 0;
					REC_tb = 0;
					return;
				}
				REC_data <<= 1;
				if(REC_BIT_chk)
				{
					REC_data |= 0x001;
				}
				if(++REC_bit_cnt == 16)
				{
					REC_tb=0;
					switch(REC_data)
					{
						case 0x0F01 :
						{
							break;
						}
						case 0x0F02 :
						{
							break;
						}
						default : {}
					}
				}
			} 
			else if(REC_H_cnt_buf > 60 && REC_H_cnt_buf < 90 && REC_L_cnt_buf > 2 && REC_L_cnt_buf < 20)
			{
				REC_tb = 1;	// �ж�ͬ��λ
				REC_bit_cnt = 0;
			}
		} 
		else // L...
		{
			REC_count ++; 			
		}
	}
	else
	{ 
		if(!REC_sta) // L -> H
		{  
			REC_sta = 1; 
			REC_L_cnt_buf = REC_count; 
			REC_count = 0; 			
		}
		else  // H...
		{
			REC_count ++; 			
		}
	}
}

//***************************************************************************
//! \brief       ң�ذ�����������
//! \Call        125 us
//***************************************************************************

u8  REC_10ms_cnt;
bit key_out;
bit L_key_in;
u8  L_key_num;
u8  L_Keybuf;
bit L_key3sin;
bit undisin_;
u8 key3s_cnt;

void L_keyout_chk(void)
{
	if(!key_out)
	{
		REC_10ms_cnt ++;
		if(REC_10ms_cnt >= 20)	// ������200msû���յ���Ч��ֵ�����ж�Ϊ key_out
		{
			REC_10ms_cnt = 0;
			if(L_key_num == 1 && !L_key3sin && !undisin_)
			{
				// δ��3s  key_on=1;
			}
			else if(L_key3sin)
			{
				L_key3sin = 0;
			}
			L_Keybuf = 0;
			L_key_in = 0;
			key_out = 1;
			undisin_ = 0;
		}
	}
}

