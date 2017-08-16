/*Ԥ���롢����������ȵ�*/
#include <SN8P2501B.h>
#define uchar unsigned char
#define uint  unsigned int
#define Scl	FP20
#define Sda	FP21

uchar	__ROM	word_write[8]	=	{0,1,2,3,4,5,6,7};	
uchar	__ROM	word_clear[8]	=	{0,0,0,0,0,0,0,0};
uchar			word_read[8]	=	{0,0,0,0,0,0,0,0};

void Start(void)        /*��ʼ����*/
{
        Sda=1;
        Scl=1;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
        Sda=0;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
}
void Stop(void) 		/*ֹͣ����*/
{
        Sda=0;
        Scl=1;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
        Sda=1;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
}
void Ack(void)  		/*Ӧ��λ*/
{
        Sda=0;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
        Scl=1;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
        Scl=0;
}
void  NoAck(void)       /*����Ӧ��λ*/
{
        Sda=1;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
        Scl=1;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
        Scl=0;
}
void Send(uchar Data)   /*���������ӳ���,DataΪҪ���͵�����*/
{
    uchar BitCounter=8;		/*λ������*/
    uchar temp=Data;     	/*�м��������*/
    do
    {
		temp=Data;
		Scl=0;
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		__asm("NOP");
		if(temp & 0x80)		/* ������λ��1*/
	       	Sda=1;
		else
			Sda=0;
		Scl=1;
		temp=Data<<1;        /*RLC*/
		Data=temp;
		BitCounter--;
     }while(BitCounter);
     Scl=0;
}
uchar Read(void) 		/*��һ���ֽڵ�����,�����ظ��ֽ�ֵ*/
{
        uchar temp=0;
        uchar BitCounter=8;
        Sda=1;
		FP21M=0;//////////////////////////////////////////////
        do{												
          Scl=0;
			__asm("NOP");
			__asm("NOP");
			__asm("NOP");
			__asm("NOP");
          Scl=1;
			__asm("NOP");
			__asm("NOP");
			__asm("NOP");
			__asm("NOP");
          if(Sda)       /*���Sda=1;*/
                temp=temp|0x01;  /*temp�����λ��1*/
          else
                temp=temp&0xfe;  /*����temp�����λ��0*/
          if(BitCounter-1)
          {
		  	temp=temp<<1;
          }
          BitCounter--;
        }while(BitCounter);
		FP21M=1;///////////////////////////////////////////////
        return(temp);
}
void WrToROM(uchar __ROM Data[],uchar Address,uchar Num)/*дһ�����ݵ�AT24C02��*/
{
     uchar i=0;
     uchar __ROM *PData;
     PData=Data;
     Start();        
     Send(0xa0);		//Device Address 
     Ack();
     Send(Address); 	//Word Address
     Ack();
     for(i=0;i<Num;i++)
     {
        Send(*(PData+i));
        Ack();
     }
     Stop();
}
void  RdFromROM(uchar Data[],uchar Address,uchar Num)/*��һ�����ݴ�AT24C02*/
{
	uchar i=0;
	uchar *PData;
	PData=Data;
	Start();
	Send(0xa0); //A0��A1��A2�ӵأ���AT24C02��д��ַΪ0XA0
	Ack();
	Send(Address);
	Ack();
	for(i=0;i<Num;i++)
	{
        Start();
        Send(0xa1); //A0��A1��A2�ӵأ���AT24C02����ַΪ0XA1
        Ack();
        *(PData+i)=Read();
        NoAck();
        Stop();
	}
}

void delay(uchar temp)
{
	uchar i,j,k;
	for(i=0;i<temp;i++)
	{
		for(j=0;j<20;j++)
		for(k=0;k<50;k++)
		{
			__asm("NOP");
		}
		WDTR=0X5A;
	}
}

void main()
{
	WDTR=0X5A;
	P2M=0XFF;
	uchar m,n=0;
    while(1)
	{
		WrToROM(word_write,0x70,8);
		
		RdFromROM(word_read,0x70,8);
		
		delay(200);
		
		for(m=0;m<8;m++)
		{
			if(word_read[m] == m)
			n++;
		}
		if(n == 8)
		{
			n=0;
			FP23=~FP23;
			FP24=~FP24;
			FP25=~FP25;
		}

		WrToROM(word_clear,0x70,8);

		RdFromROM(word_read,0x70,8);
	}
}

