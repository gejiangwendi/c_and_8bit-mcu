#ifndef	_USER_H_
#define _USER_H_

#define	uint unsigned int
#define	uchar unsigned char

#define	BUZZER FP54
#define	K1 FP00
#define	K2 FP10
#define	K3 FP12
#define	K4 FP13

extern void int0_init(void);
extern void delay_ms(uint x);
extern int key_scan(void);
extern void key_serve(int num);
extern void buzzer(void);

extern bit KEY_EN;
extern int led456;
extern int led123;
extern int P2_TEMP[];

#endif	