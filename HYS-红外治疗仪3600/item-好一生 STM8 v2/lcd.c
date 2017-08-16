#include"user.h"

extern	uchar	t_dsp;
extern	uchar	power_dsp;
extern	uchar	model;
extern	uchar	hwrj;
extern	uchar		SPEEKER_ON;
extern	uchar		AUTO_ON;
extern	uchar		SYS_ON;
extern	uchar		f_1s;

const	uchar	SEG_G[]={30,29,28,27,25,24,23,22};
const	uchar	DAT_G[]={0xfb,0x0b,0xbd,0x9f,0x4f,0xd7,0xf7,0x8b,0xff,0xdf};
uint 	en		=	0x8020;
uint 	bias	=	0x8520;
uint 	on		=	0x8060;
uint 	off		=	0x8040;
uint 	a_dsp	=	0xa000;
		uchar	DAT_buf[]={0x0f,0x0f};
		uchar 	k;
		uchar	dat_g2;
		uchar	t_dsp_buf;
		uchar	power_dsp_buf;
		uchar	model_buf;
		uchar	hwrj_buf;
		uchar		SPEEKER_ON_buf;
		uchar		AUTO_ON_buf;
		uchar		SYS_ON_buf;

void lcd(void)
{
	if(SYS_ON)
	{
		if(power_dsp != power_dsp_buf)
		{
			power_dsp_buf = power_dsp;
				dat_g2 = DAT_G[power_dsp/10]>>4;
				lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
				k++;
				dat_g2 = DAT_G[power_dsp/10]&0x0f;
				lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
				k++;
				dat_g2 = DAT_G[power_dsp%10]>>4;
				lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
				k++;
				dat_g2 = DAT_G[power_dsp%10]&0x0f;
				if(SPEEKER_ON && (dat_g2%2))
				dat_g2=dat_g2-1;
				DAT_buf[0]=dat_g2;
				lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
		}
		if(model != model_buf)
		{
			if(model_buf>0 && model_buf<=6)
			{
				if(model_buf <3)   			dat_g2 = 0x08>>model;
				else	   				dat_g2 = 0x10<<(model-3);
				lcd_13bit(a_dsp+(0x0080*31)+(0x0008*(dat_g2&0x0f)));
				lcd_13bit(a_dsp+(0x0080*21)+(0x0008*((dat_g2&0xf0)>>3)));
			}
			model_buf =	model;
		}
		if(hwrj != hwrj_buf)
		{
			hwrj_buf = hwrj;
				if(AUTO_ON)			DAT_buf[1]=(1<<hwrj) | 0x01;
				else 	 			DAT_buf[1]=(1<<hwrj) & 0x0e;
				lcd_13bit(a_dsp+(0x0080*26)+(0x0008*(DAT_buf[1])));
		}
		if(AUTO_ON != AUTO_ON_buf)
		{
			AUTO_ON_buf	= AUTO_ON;
				if(AUTO_ON)			DAT_buf[1] |= 0x01;
				else	 			DAT_buf[1] &= 0xfe;
				lcd_13bit(a_dsp+(0x0080*26)+(0x0008*(DAT_buf[1])));
		}
		if(t_dsp != t_dsp_buf)
		{
			t_dsp_buf =	t_dsp;
			if(t_dsp == 0)
			{
				Lcd_Init(0xff);	////////////////////////////////init////////////////////////////////////// 
			}
			dat_g2 = DAT_G[t_dsp/10]>>4;
			lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
			k++;
			dat_g2 = DAT_G[t_dsp/10]&0x0f;
			lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
			k++;
			dat_g2 = DAT_G[t_dsp%10]>>4;
			lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
			k++;
			dat_g2 = DAT_G[t_dsp%10]&0x0f;
			lcd_13bit(a_dsp+(0x0080*(SEG_G[k]))+(0x0008*dat_g2));
		}
		if(SPEEKER_ON != SPEEKER_ON_buf)
		{
			SPEEKER_ON_buf = SPEEKER_ON;
				if(SPEEKER_ON && (DAT_buf[0]%2))
				DAT_buf[0]=DAT_buf[0]-1;
				else if((SPEEKER_ON==0)&&(DAT_buf[0]%2==0))
				DAT_buf[0]=DAT_buf[0]+1;
				lcd_13bit(a_dsp+(0x0080*27)+(0x0008*DAT_buf[0]));
		}
	}
	if(SYS_ON != SYS_ON_buf)
	{
		SYS_ON_buf = SYS_ON;	
			if(SYS_ON)	   	Lcd_Init(0x00);
			else
			{
				t_dsp = 0;
				power_dsp = 0;
				hwrj = 0;
				model = 0;
				SPEEKER_ON = 1;
				DAT_buf[0] = 0;
				DAT_buf[1] = (1<<hwrj) | 0x01;
			}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(SYS_ON && t_dsp != 0)
	{
		if(f_1s)
		{
			if(model > 0)
			{
				//ģʽ��˸
				if(AUTO_ON)
				{
					//�Զ���˸
				}
			}
			if(hwrj)
			{
				//������˸
			}
		}
	}	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void write_add(uint add)
{
	uchar i,j;
	CS_OFF;
	for(i=0;i<9;i++)
	{
		WR_OFF;
		if(add&0x8000)
		DATA_ON;
		else
		DATA_OFF;
		add<<=1;
		for(j=0;j<6;j++) ;
		WR_ON;
		for(j=0;j<6;j++) ;
	}
}
void write_dat(uchar dat)
{
	uchar i,j;
	for(i=0;i<4;i++)
	{
		WR_OFF;
		if(dat&0x80)
		DATA_ON;
		else
		DATA_OFF;
		dat<<=1;
		for(j=0;j<6;j++) ;
		WR_ON;
		for(j=0;j<6;j++) ;
	}
}
void lcd_13bit(uint add_dat)
{
	uchar i,j;
	CS_OFF;
	for(i=0;i<13;i++)
	{
		WR_OFF;
		if(add_dat&0x8000)
		DATA_ON;
		else
		DATA_OFF;
		add_dat<<=1;
		for(j=0;j<6;j++) ;
		WR_ON;
		for(j=0;j<6;j++) ;
	}
	CS_ON;
	for(j=0;j<6;j++) ;
}
void lcd_12bit(uint com)
{
	uchar i,j;
	CS_OFF;
	for(i=0;i<12;i++)
	{
		WR_OFF;
		if(com & 0x8000)
		DATA_ON;
		else
		DATA_OFF;
		com<<=1;
		for(j=0;j<6;j++) ;
		WR_ON;
		for(j=0;j<6;j++) ;
	}
	CS_ON;
	for(j=0;j<6;j++) ;
}
void Lcd_Init(uchar dsp_dat)   // 0xff 0x00
{
	uchar num_1;
	CS_ON;
	WR_ON;
	DATA_ON;
	LED_OFF;
	for(num_1=0;num_1<10;num_1++);
	lcd_12bit(en);
	lcd_12bit(bias);
	lcd_12bit(on);
	for(num_1=0;num_1<10;num_1++);
	write_add(a_dsp + (0x0080*21));
	for(num_1=21;num_1<32;num_1++)
	write_dat(dsp_dat);
	for(num_1=0;num_1<10;num_1++);
	CS_ON;
	WR_ON;
	DATA_ON;
	LED_OFF;
}
