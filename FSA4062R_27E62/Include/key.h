#ifndef		_KEY_H_
#define 	_KEY_H_

#include "typedefine.h"

extern	bit f_10ms;
extern	bit F_125us;
extern	u8 num_10ms;
extern	u8 num_1s;
extern	u8 time_cnt1;
extern	u8 time_cnt2;
extern	u8 time_cnt3;

extern	bit buzzer_on;		// BI
extern 	bit buzzer1_on;		// BI��
extern 	bit buzzer2_on;		// BI BI
extern 	u8  BUZ_CNT;
extern 	bit buz_en;			// buzzerʹ��λ

extern	u8  led_data[];		// LED ��ʾ���뻺����
extern	bit f_display;		// ���� �������ʾ���ٶȡ���ʱ�䡱
extern	u8  LED_CODE[];		// LED ��ʾ����
extern	bit led_data_ok;	// LED ��ʾ�뻺�������ɱ�־
extern	bit	undis_ok;		// LED Ϩ���ɹ���־

void key(void);

#endif	
