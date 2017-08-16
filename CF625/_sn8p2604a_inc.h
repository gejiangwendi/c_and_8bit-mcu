ifndef __SN8P2604A__INC__H
SN8P2604A__INC__H equ 1
	L	EQU	0x80
	H	EQU	0x81
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
		FP01M	EQU	P0M.1
		FP00M	EQU	P0M.0
	PEDGE	EQU	0xbf
		FP00G1	EQU	PEDGE.4
		FP00G0	EQU	PEDGE.3
	P1W	EQU	0xc0
		FP17W	EQU	P1W.7
		FP16W	EQU	P1W.6
		FP15W	EQU	P1W.5
		FP14W	EQU	P1W.4
		FP13W	EQU	P1W.3
		FP12W	EQU	P1W.2
		FP11W	EQU	P1W.1
		FP10W	EQU	P1W.0
	P1M	EQU	0xc1
		FP17M	EQU	P1M.7
		FP16M	EQU	P1M.6
		FP15M	EQU	P1M.5
		FP14M	EQU	P1M.4
		FP13M	EQU	P1M.3
		FP12M	EQU	P1M.2
		FP11M	EQU	P1M.1
		FP10M	EQU	P1M.0
	P2M	EQU	0xc2
		FP27M	EQU	P2M.7
		FP26M	EQU	P2M.6
		FP25M	EQU	P2M.5
		FP24M	EQU	P2M.4
		FP23M	EQU	P2M.3
		FP22M	EQU	P2M.2
		FP21M	EQU	P2M.1
		FP20M	EQU	P2M.0
	P5M	EQU	0xc5
		FP54M	EQU	P5M.4
		FP53M	EQU	P5M.3
		FP52M	EQU	P5M.2
		FP51M	EQU	P5M.1
		FP50M	EQU	P5M.0
	INTRQ	EQU	0xc8
		FTC1IRQ	EQU	INTRQ.6
		FT0IRQ	EQU	INTRQ.4
		FP01IRQ	EQU	INTRQ.1
		FP00IRQ	EQU	INTRQ.0
	INTEN	EQU	0xc9
		FTC1IEN	EQU	INTEN.6
		FT0IEN	EQU	INTEN.4
		FP01IEN	EQU	INTEN.1
		FP00IEN	EQU	INTEN.0
	OSCM	EQU	0xca
		FCPUM1	EQU	OSCM.4
		FCPUM0	EQU	OSCM.3
		FCLKMD	EQU	OSCM.2
		FSTPHX	EQU	OSCM.1
	WDTR	EQU	0xcc
	PCL	EQU	0xce
	PCH	EQU	0xcf
	P0	EQU	0xd0
		FP02	EQU	P0.2
		FP01	EQU	P0.1
		FP00	EQU	P0.0
	P1	EQU	0xd1
		FP17	EQU	P1.7
		FP16	EQU	P1.6
		FP15	EQU	P1.5
		FP14	EQU	P1.4
		FP13	EQU	P1.3
		FP12	EQU	P1.2
		FP11	EQU	P1.1
		FP10	EQU	P1.0
	P2	EQU	0xd2
		FP27	EQU	P2.7
		FP26	EQU	P2.6
		FP25	EQU	P2.5
		FP24	EQU	P2.4
		FP23	EQU	P2.3
		FP22	EQU	P2.2
		FP21	EQU	P2.1
		FP20	EQU	P2.0
	P5	EQU	0xd5
		FP54	EQU	P5.4
		FP53	EQU	P5.3
		FP52	EQU	P5.2
		FP51	EQU	P5.1
		FP50	EQU	P5.0
	T0M	EQU	0xd8
		FT0ENB	EQU	T0M.7
		FT0RATE2	EQU	T0M.6
		FT0RATE1	EQU	T0M.5
		FT0RATE0	EQU	T0M.4
	T0C	EQU	0xd9
	TC1M	EQU	0xdc
		FTC1ENB	EQU	TC1M.7
		FTC1RATE2	EQU	TC1M.6
		FTC1RATE1	EQU	TC1M.5
		FTC1RATE0	EQU	TC1M.4
		FTC1CKS	EQU	TC1M.3
		FALOAD1	EQU	TC1M.2
		FTC1OUT	EQU	TC1M.1
		FPWM1OUT	EQU	TC1M.0
	TC1C	EQU	0xdd
	TC1R	EQU	0xde
	STKP	EQU	0xdf
		FGIE	EQU	STKP.7
		FSTKPB2	EQU	STKP.2
		FSTKPB1	EQU	STKP.1
		FSTKPB0	EQU	STKP.0
	P0UR	EQU	0xe0
		FP01R	EQU	P0UR.1
		FP00R	EQU	P0UR.0
	P1UR	EQU	0xe1
		FP17R	EQU	P1UR.7
		FP16R	EQU	P1UR.6
		FP15R	EQU	P1UR.5
		FP14R	EQU	P1UR.4
		FP13R	EQU	P1UR.3
		FP12R	EQU	P1UR.2
		FP11R	EQU	P1UR.1
		FP10R	EQU	P1UR.0
	P2UR	EQU	0xe2
		FP27R	EQU	P2UR.7
		FP26R	EQU	P2UR.6
		FP25R	EQU	P2UR.5
		FP24R	EQU	P2UR.4
		FP23R	EQU	P2UR.3
		FP22R	EQU	P2UR.2
		FP21R	EQU	P2UR.1
		FP20R	EQU	P2UR.0
	P5UR	EQU	0xe5
		FP54R	EQU	P5UR.4
		FP53R	EQU	P5UR.3
		FP52R	EQU	P5UR.2
		FP51R	EQU	P5UR.1
		FP50R	EQU	P5UR.0
	@HL	EQU	0xe6
	@YZ	EQU	0xe7
	P1OC	EQU	0xe9
		FP11OC	EQU	P1OC.1
		FP10OC	EQU	P1OC.0
	STK7L	EQU	0xf0
	STK7H	EQU	0xf1
	STK6L	EQU	0xf2
	STK6H	EQU	0xf3
	STK5L	EQU	0xf4
	STK5H	EQU	0xf5
	STK4L	EQU	0xf6
	STK4H	EQU	0xf7
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
