#include "user.h"

void initial(void)
{
		P0M	=	0x01;
		P0UR=	0x01;
		P0	=	0x00;

		P1M =	0xDF;
		P1UR=	0xFF;
		P1 	=	0x00;

		P5M =	0xFF;
		P5UR=	0xFF;
		P5	=	0x00;

		FTC0IEN=0;
		FTC0ENB=0;
		TC0M=0x74;
		TC0C=0xc2;
		TC0R=0xc2;	
		FTC0IRQ=0;
		FTC0IEN=1;
		FTC0ENB=1;
		FGIE=1;

		FT0IEN=0;
		FT0ENB=0;
		T0M=0x20;
		T0C = 0x64;
		FT0IRQ=0;
		FT0IEN=1;
		FT0ENB=1;
		FGIE=1;
}
