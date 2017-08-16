#include	"rxdata.h"

	u8 temp;
	bit rx_ok_f;
	bit kuaishan;

//***************************************************************************
//! \brief       ���ڽ��մ�����
//! \param       ��
//! \return      ��
//***************************************************************************
void RxData (void)
{
	if(RX_pack_ok)
	{
		RX_pack_ok = 0;
		if(RX_data[3] == 0x0d)						//�û��� if(RX_data[3] == 0x0D)	
		{
			switch(RX_data[4])
			{
				case 0xA3 :		//��Ʒ�ػ�����ʾ��Ϣ  Ϩ��ģʽ[7 6]  ��ʾ״̬[5 4]  ���ػ�����[3 2 1]  ����״̬[0]
				{ 
					if(RX_data[5] == 0xf0)				//����ʾ
					{
						send_data[1] &= 0xbf;
					}
					else if(RX_data[5] == 0xc0)			//����ʾ
					{
						send_data[1] |= 0x40;
					}
					else if(RX_data[5] == 0x08)			//�ػ�  ģʽ����
					{
						send_data[1] 	&= 0xc0;
						send_data[2]	= 0x00;			//��λ����
						send_data[3] 	= 0x00;			//��ʱ�ػ�ʱ������
						send_data[4] 	= 0x00;
						receive_data[3] 	= 0x00;			//��ʱ�ػ�ʱ������
						receive_data[4] 	= 0x00;
					send_data[1] 	|= 0x08;
					}
					else if(RX_data[5] == 0x09)			//����
					{
						send_data[1] &= 0xcf;
						send_data[1] |= 0x20;
						send_data[5] = 0x00;			//ԤԼ����ʱ������
						send_data[6] = 0x00;
						receive_data[5] = 0x00;			//ԤԼ����ʱ������
						receive_data[6] = 0x00;
					send_data[1] 	|= 0x08;
					}
					break;
				}
				case 0xA5 :
				{	
					if(RX_ptr_buf<=9)
					{
						if(RX_data[5]==0xD1)				//��ʱ�ػ�
						{
							send_data[3] = RX_data[6]&0x3f;
							send_data[4] = RX_data[7]&0x3f;
						}
						else if(RX_data[5]==0xe1)			//ԤԼ����
						{
							send_data[5] = RX_data[6]&0x3f;
							send_data[6] = RX_data[7]&0x3f;
						}
					}
					else if(RX_ptr_buf <= 13) 
					{
						if(RX_data[5]==0xD1 || RX_data[9]==0xD2)		//��ʱ�ػ�
						{
							send_data[3] = RX_data[6]&0x3f;
							send_data[4] = RX_data[7]&0x3f;
						}
						else if(RX_data[5]==0xe1 || RX_data[9]==0xe2)	//ԤԼ����
						{
							send_data[5] = RX_data[6]&0x3f;
							send_data[6] = RX_data[7]&0x3f;
						}
					}
					send_data[1] 	|= 0x08;
					break;
				}
				case 0xA4 :	//��Ʒ����(ģʽ)��Ϣ  ��������[7~4]1011  ��ǰ����(ģʽ)[3~0] 0000��׼ 0001���� 0010���� 0011����
				{
					if(RX_data[5] == 0xb0)					//�趨��λ
					{
						if(RX_data[6] == 0x01)
						{
							send_data[2] = RX_data[6] - 1;						
						}
						else if(RX_data[6] == 0x02)
						{
							send_data[2] = RX_data[6] - 1;						
						}
						else if(RX_data[6] == 0x03)
						{
							send_data[2] = RX_data[6] - 1;						
						}
						send_data[1] &= 0xf8;
					}
					else if(RX_data[5] == 0xb1)				//�趨����ģʽ�µ��¶�
					{
						if(RX_data[6] == 0x01)
						{
							send_data[2] = 3 - RX_data[6];						
						}
						else if(RX_data[6] == 0x02)
						{
							send_data[2] = 3 - RX_data[6];						
						}
						else if(RX_data[6] == 0x03)
						{
							send_data[2] = 3 - RX_data[6];						
						}
						send_data[1] &= 0xf8;
						send_data[1] |= (RX_data[6] & 0x07);
					}
					break;
				}
				default : {}
			}
			In_send			=	1;
			data_ptr		=	0;
			send_data_buf	=	0xa1;
			chksum_send 	=	0xa1;
		}
		else if(RX_data[3] == 0x01)
		{
			if(RX_data[4] == 0x02)
			kuaishan = 1;
		}
	}
}
