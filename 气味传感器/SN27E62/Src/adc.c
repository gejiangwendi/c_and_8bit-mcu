#include	"user.h"
extern bit ADC_OK;
extern uint Adc_dat;
extern uint POWER;
extern void delay_100ms(void);
extern uint  	POWER_LED; 
uint PPM;
uint PPM_buf;
uint POWER_buf2;
uint temp1,temp2,temp5;
bit	f_FP04;
bit f_FP03;
bit delay_in;
float __ROM Adc_ref = 2.65;			
float __ROM Adc_ref_1 = 2.65+0.2;	
float __ROM Adc_ref_2 = 2.65+0.7;	
float 		Adc_cvt;				
uint Adc_cnt;

void	adc		(void)
{
	if(POWER_buf2 != POWER)
	{
		L_outp = 0;
		M_outp = 0; 	
		H_outp = 0; 
		temp1++;
		if(temp1 >= 250)
		{
			temp1 = 0;
			temp2++;
			if(temp2 >= 10)
			{
				temp2 = 0;
				POWER_buf2 = POWER;
				if(POWER == 1)
				{
					if(PPM == 0)
						L_outp = 1;
					else if(PPM == 1)
						M_outp = 1;
					else if(PPM == 2)
						H_outp = 1;
				}
				else
				{
					if(POWER == 2)
						L_outp = 1;  
					else if(POWER == 3)
						M_outp = 1;  
					else if(POWER == 4)
						H_outp = 1;
					FP44   = 1;
					f_FP04 = 0; 
					f_FP03 = 0;
				}
			}
		}
	}
	if(POWER == 1)
	{
		if(ADC_OK)
		{
			ADC_OK	=	0;
			Adc_cvt +=	(float)Adc_dat/51/255;
			Adc_cnt++;
			if(Adc_cnt==255)
			{
				Adc_cnt = 0;
				if(Adc_cvt > Adc_ref_2)
					PPM	=	2;
				else if(Adc_cvt > Adc_ref_1)
					PPM	=	1;
				else
					PPM	=	0;
				if(PPM_buf != PPM)
				{
					PPM_buf= PPM;
					L_outp = 0;
					M_outp = 0; 	
					H_outp = 0; 
					delay_in = 1;
				}
				Adc_cvt=0.0000001;
			}
		}
		if(delay_in)
		{
			temp5++;
			if(temp5 >= 1)
			{
				temp5 = 0;
				delay_in	=	0;
				if(PPM == 0)
				{
					L_outp = 1;
					f_FP04 = 1; 
					f_FP03 = 0;
				}
				else if(PPM == 1)
				{
					M_outp = 1;
					f_FP04 = 1;
					f_FP03 = 1;
				}
				else if(PPM == 2)
				{
					H_outp = 1;
					f_FP04 = 0; 
					f_FP03 = 1;
				}
			}
		}
	}
}
