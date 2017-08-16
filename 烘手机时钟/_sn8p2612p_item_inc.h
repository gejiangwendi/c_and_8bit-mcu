ifndef __SN8P2612__INC__H
SN8P2612__INC__H equ 1
	R	EQU	0x82
	Z	EQU	0x83
	Y	EQU	0x84
	PFLAG	EQU	0x86
		FZ	EQU	PFLAG.0
		FDC	EQU	PFLAG.1
		FC	EQU	PFLAG.2
		FLVD24	EQU	PFLAG.4
		FLVD36	EQU	PFLAG.5
		FNPD	EQU	PFLAG.6
		FNT0	EQU	PFLAG.7
	P0M	EQU	0xb8
		FP00M	EQU	P0M.0
		FP01M	EQU	P0M.1
	PEDGE	EQU	0xbf
		FP00G1	EQU	PEDGE.4
		FP00G0	EQU	PEDGE.3
	P1W	EQU	0xc0
	P1M	EQU	0xc1
		FP10M	EQU	P1M.0
		FP11M	EQU	P1M.1
		FP12M	EQU	P1M.2
		FP13M	EQU	P1M.3
		FP14M	EQU	P1M.4
		FP16M	EQU	P1M.6
		FP17M	EQU	P1M.7
	P5M	EQU	0xc5
		FP50M	EQU	P5M.0
		FP51M	EQU	P5M.1
		FP52M	EQU	P5M.2
		FP53M	EQU	P5M.3
		FP54M	EQU	P5M.4
		FP55M	EQU	P5M.5
		FP56M	EQU	P5M.6
		FP57M	EQU	P5M.7
	INTRQ	EQU	0xc8
		FP00IRQ	EQU	INTRQ.0
		FP01IRQ	EQU	INTRQ.1
		FT0IRQ	EQU	INTRQ.4
		FTC0IRQ	EQU	INTRQ.5
	INTEN	EQU	0xc9
		FP00IEN	EQU	INTEN.0
		FP01IEN	EQU	INTEN.1
		FT0IEN	EQU	INTEN.4
		FTC0IEN	EQU	INTEN.5
	OSCM	EQU	0xca
		FCPUM1	EQU	OSCM.4
		FCPUM0	EQU	OSCM.3
		FCLKMD	EQU	OSCM.2
		FSTPHX	EQU	OSCM.1
	WDTR	EQU	0xcc
	TC0R	EQU	0xcd
	PCL	EQU	0xce
	PCH	EQU	0xcf
	P0	EQU	0xd0
		FP00	EQU	P0.0
		FP01	EQU	P0.1
	P1	EQU	0xd1
		FP10	EQU	P1.0
		FP11	EQU	P1.1
		FP12	EQU	P1.2
		FP13	EQU	P1.3
		FP14	EQU	P1.4
		FP15	EQU	P1.5
		FP16	EQU	P1.6
		FP17	EQU	P1.7
	P5	EQU	0xd5
		FP50	EQU	P5.0
		FP51	EQU	P5.1
		FP52	EQU	P5.2
		FP53	EQU	P5.3
		FP54	EQU	P5.4
		FP55	EQU	P5.5
		FP56	EQU	P5.6
		FP57	EQU	P5.7
	T0M	EQU	0xd8
		FT0RATE0	EQU	T0M.4
		FT0RATE1	EQU	T0M.5
		FT0RATE2	EQU	T0M.6
		FT0ENB	EQU	T0M.7
	T0C	EQU	0xd9
	TC0M	EQU	0xda
		FTC0ENB	EQU	TC0M.7
		FTC0RATE2	EQU	TC0M.6
		FTC0RATE1	EQU	TC0M.5
		FTC0RATE0	EQU	TC0M.4
		FTC0CKS	EQU	TC0M.3
		FALOAD0	EQU	TC0M.2
		FTC0OUT	EQU	TC0M.1
		FPWM0OUT	EQU	TC0M.0
	TC0C	EQU	0xdb
	STKP	EQU	0xdf
		FGIE	EQU	STKP.7
		FSTKPB2	EQU	STKP.2
		FSTKPB1	EQU	STKP.1
		FSTKPB0	EQU	STKP.0
	P0UR	EQU	0xe0
	P1UR	EQU	0xe1
	P5UR	EQU	0xe5
	@YZ	EQU	0xe7
	P1OC	EQU	0xe9
	STK3L	EQU	0xf8
	STK3H	EQU	0xf9
	STK2L	EQU	0xfa
	STK2H	EQU	0xfb
	STK1L	EQU	0xfc
	STK1H	EQU	0xfd
	STK0L	EQU	0xfe
	STK0H	EQU	0xff
@RST_WDT	macro		
 		   MOV  A, #0x5A
		   B0MOV  WDTR, A
	endm

SleepMode	macro	
		B0BSET	FCPUM0
	endm

GreenMode	macro	
		B0BSET	FCPUM1
		NOP
		NOP
	endm

SlowMode	macro	
		B0BSET	FCLKMD
		B0BSET	FSTPHX
	endm

Slow2Normal	macro	
		B0BCLR	FSTPHX
		NOP
		NOP
		NOP
		B0BCLR	FCLKMD
	endm

endif
