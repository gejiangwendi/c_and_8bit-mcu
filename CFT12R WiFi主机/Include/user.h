#ifndef		_USER_H_
#define 	_USER_H_

#include <SN8P2613.h>

#define		uint	unsigned int
#define		uchar	unsigned char
#define		FAN_CTL FP12
#define		RLY_CTL FP13

extern void init(void);
extern void key(void);
extern void display(void);
extern void buzzer(void);

extern  uint BUZ_CNT;
extern  uint BUZ_CNT1;
extern  uint num_10ms;
extern  uint time;
extern  uint t_cnt1;
extern  uint t_cnt2;

extern	bit f_10ms;
extern	bit f2_10ms;
extern	bit f3_10ms;
extern	bit f4_10ms;
extern	bit f_50ms;
extern	bit f_250ms;
extern  bit delay_10s_in;
extern  bit delay_500ms_in;
extern  bit timer_on;
extern  bit Standby;
extern  bit buzzer_on;
extern  bit led_on_wait;
extern  bit sys_on;
extern  bit buzzer_on;
extern  bit buzzer1_on;

#endif	
