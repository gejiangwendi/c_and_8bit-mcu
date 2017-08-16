ifndef __SN8P2501B__INC__H
SN8P2501B__INC__H equ 1
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
	PEDGE	EQU	0xbf
		FP00G1	EQU	PEDGE.4
		FP00G0	EQU	PEDGE.3
	P1W	EQU	0xc0
	P1M	EQU	0xc1
		FP10M	EQU	P1M.0
		FP12M	EQU	P1M.2
		FP13M	EQU	P1M.3
	P2M	EQU	0xc2
		FP20M	EQU	P2M.0
		FP21M	EQU	P2M.1
		FP22M	EQU	P2M.2
		FP23M	EQU	P2M.3
		FP24M	EQU	P2M.4
		FP25M	EQU	P2M.5
	P5M	EQU	0xc5
		FP54M	EQU	P5M.4
	INTRQ	EQU	0xc8
		FP00IRQ	EQU	INTRQ.0
		FT0IRQ	EQU	INTRQ.4
		FTC0IRQ	EQU	INTRQ.5
	INTEN	EQU	0xc9
		FP00IEN	EQU	INTEN.0
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
	P1	EQU	0xd1
		FP10	EQU	P1.0
		FP11	EQU	P1.1
		FP12	EQU	P1.2
		FP13	EQU	P1.3
	P2	EQU	0xd2
		FP20	EQU	P2.0
		FP21	EQU	P2.1
		FP22	EQU	P2.2
		FP23	EQU	P2.3
		FP24	EQU	P2.4
		FP25	EQU	P2.5
	P5	EQU	0xd5
		FP54	EQU	P5.4
	T0M	EQU	0xd8
		FT0TB	EQU	T0M.0
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
		FSTKPB1	EQU	STKP.1
		FSTKPB0	EQU	STKP.0
	P0UR	EQU	0xe0
		FP00R	EQU	P0UR.0
	P1UR	EQU	0xe1
		FP10R	EQU	P1UR.0
		FP12R	EQU	P1UR.2
		FP13R	EQU	P1UR.3
	P2UR	EQU	0xe2
		FP20R	EQU	P2UR.0
		FP21R	EQU	P2UR.1
		FP22R	EQU	P2UR.2
		FP23R	EQU	P2UR.3
		FP24R	EQU	P2UR.4
		FP25R	EQU	P2UR.5
	P5UR	EQU	0xe5
		FP54R	EQU	P5UR.4
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
