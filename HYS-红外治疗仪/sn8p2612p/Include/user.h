#ifndef		_USER_H_
#define 	_USER_H_

#include <SN8P2612.h>

#define		uint	unsigned int
#define		uchar	unsigned char
#define		FAN_CTL FP12
#define		RLY_CTL FP13

extern void initial(void);
extern void key(void);
extern void led_dsp(void);

#endif	

