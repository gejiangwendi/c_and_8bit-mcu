/*******************************************************************************************************
File name:		SIO.c
Author:			Lian_Jin
Email:			lian_jin@sonix.com.cn
Date��			2011/10/25
Description:
				�����������ģ�飬MCU��93C46ͨ�ţ�
				��ָ��λ�ã�д�����ݣ��ٶ�ȡ������������ReadBuf�
��ע�⡿��
				���������ֲ���8bit����SIOBֻ�� 8bit	���������λҪʹ��IO��ģ��ʱ����ʵ�ַ��ͣ�
				��Ҫ����I/O����GPIO������SIO����֮����л���
*******************************************************************************************************/

//------------------------------------------------------------------------------------------------------

#include	"User.h"
#include	"SIO.h"

uint	ReadDataBuf_;
uint	_ReadDataBuf_;
uint	ReadDataBuf;
uint	ReadDataBuf_0;
uint	ReadDataBuf_1;
uint	ReadDataBuf_2;
bit		FirstOP;			//��һλ������
uint	StartCommand;		//��ʼ
uint	TransmitData;		//Ҫ���͵�����
uint	TransmitAddress;	//��ŵĵ�ַ
uint	ReadAddress;
uint	DisableCommand;
//------------------------------------------------------------------------------------------------------

/*******************************************************************************************************
�������ƣ�	Serial_Trs_Rec(void) 
�����ܣ�	�����������
			Trs = Transmit    Rec = Receive
*******************************************************************************************************/
void	Serial_Trs_Rec(void)
{
//------------------------------------------------------------------------------------------------------
//	д���� 
//------------------------------------------------------------------------------------------------------
	FirstOP = 0;
	StartCommand = 0X60;			
	EW_EN_Or_DS(FirstOP ,StartCommand);

	FirstOP = 0;
	TransmitAddress = 0X8F;
	TransmitData = 0X11;
	SIO_WRITE(FirstOP,TransmitAddress,TransmitData);		//д��

	FirstOP =  1;
	ReadAddress = 0X0F;
	ReadDataBuf = SIO_READ(FirstOP,ReadAddress);			//��ȡ
//------------------------------------------------------------------------------------------------------
//	ȫд��֤
//------------------------------------------------------------------------------------------------------
	FirstOP =  1;
	ReadAddress = 0X05;
	ReadDataBuf_0 = SIO_READ(FirstOP,ReadAddress);			//�ȶ�ȡ

	FirstOP = 0;
	TransmitAddress = 0X20;
	TransmitData = 0X22;
	WRAL(FirstOP,TransmitAddress,TransmitData);				

	FirstOP =  1;
	ReadAddress = 0X05;                     
	ReadDataBuf_1 = SIO_READ(FirstOP,ReadAddress);          //��ȡ
//------------------------------------------------------------------------------------------------------
//	ȫ������֤
//------------------------------------------------------------------------------------------------------	
	FirstOP = 0;
	StartCommand = 0X40;
	ERAL(FirstOP,StartCommand);								//ȫ��

	FirstOP =  1;
	ReadAddress = 0X0F;
	ReadDataBuf_2 = SIO_READ(FirstOP,ReadAddress);			//��ȡ

//------------------------------------------------------------------------------------------------------
//	д��ֹ��֤
//------------------------------------------------------------------------------------------------------
	FirstOP = 0 ;
	DisableCommand = 0X00;
	EW_EN_Or_DS(FirstOP,DisableCommand);//д��ֹ

	FirstOP = 0;
	TransmitAddress = 0X8F;
	TransmitData = 0X99;
	SIO_WRITE(FirstOP,TransmitAddress,TransmitData);		//д�� 

	FirstOP =  1;
	ReadAddress = 0X0F;
	_ReadDataBuf_ = SIO_READ(FirstOP,ReadAddress);			//��ȡ

}

/*******************************************************************************************************
�������ƣ�	void	EW_EN_Or_DS(bit FirstOP_Reg,uint StartCommand_Reg) 
�����ܣ�	д�����д��ֹ, 					11��д����   00��д��ֹ
			FirstOP_Reg: ��һλ������			StartCommand_Reg: ��ʼ����
*******************************************************************************************************/
void	EW_EN_Or_DS(bit FirstOP_Reg,uint StartCommand_Reg)
{
	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;
					
	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = StartCommand_Reg;
	FSTART = 1;												//������ϣ�FSTART��ϵͳ�Զ�����
	while(FSIOBZ);

	FSENB = 0;
	SCS = 0;
}
/*******************************************************************************************************
�������ƣ�	void	SIO_WRITE(bit FirstOP_Reg, uint TransmitAddress_Reg, uint TransmitData_Reg)
�����ܣ�	�������ݸ�93C46
			FirstOP_Reg ����һ��������       TransmitAddress_Reg��Ҫд��ĵ�ַ
			TransmitData_Reg��Ҫд�������
*******************************************************************************************************/
void	SIO_WRITE(bit FirstOP_Reg,uint TransmitAddress_Reg,uint TransmitData_Reg)
{	
	ulong	i;
	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;

	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = TransmitAddress_Reg;
	FSTART = 1;
	while(FSIOBZ);			

	SIOB = TransmitData_Reg;		//��Ҫ���͵�����
	FSTART = 1;
	while(FSIOBZ);					//�ȴ�MCU���ݴ������
//------------------------------------------------------------------------------------------------------
	SCS = 0;						// ����93C46ʱ��
	SCS = 1;						// ������CS�ߵ͵�ƽ�ź� 93C46 �ſ�ʼд��
			


//	while(!SDI);					����й��ϣ�ʹ��while�п��ܵ��¿��Ź����
	for(i=0;i<0X0D05;i++)			//���93C46��DOλBusy/Ready״̬,�ʱ��Ϊ5ms
	{
		if(SDI == 1)
		break;
	}

	SCS = 0;
	FSENB = 0;	
}
/*******************************************************************************************************
�������ƣ�	uint	SIO_READ(bit FirstOP_Reg,uint ReceiveAddress_Reg)
�����ܣ�	��93C46��ȡ����
			FirstOP_Reg����һ��������		ReceiveAddress_Reg������ȡ�ĵ�ַ
*******************************************************************************************************/
uint	SIO_READ(bit FirstOP_Reg,uint ReceiveAddress_Reg)
{
	SCS = 1;	

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;

	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = ReceiveAddress_Reg;
	FSTART = 1;
	while(FSIOBZ);
//-----------------------------------------------------------------------------------------------------
// 	������������Ҫ����CLK���Żᴫ����
//-----------------------------------------------------------------------------------------------------
	FCPHA = 1;				//���½��ض�ȡ����
	FSTART = 1;
	while(FSIOBZ);

	FCPHA = 0;				//MCU����������ȷ��ȡ����
	SCS = 0;
	FSENB = 0;

	return(SIOB);
}
/*******************************************************************************************************
�������ƣ�	uint	WRAL(bit FirstOP_Reg,uint ReceiveAddress_Reg)
�����ܣ�	��93C46��ȡ����
			FirstOP_Reg����һ��������		ReceiveAddress_Reg������ȡ�ĵ�ַ
*******************************************************************************************************/
void	WRAL(bit FirstOP_Reg,uint StartCommand_Reg,uint TransmitData_Reg)
{
	ulong	i;	

	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;

	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = StartCommand_Reg;
	FSTART = 1;
	while(FSIOBZ);			

	SIOB = TransmitData_Reg;
	FSTART = 1;	
	while(FSIOBZ);

	SCS = 0;			// ����93C46ʱ��
	SCS = 1;			// ������CS�ߵ͵�ƽ�ź� 93C46 �ſ�ʼд��
			
 	for(i=0;i<0X0D05;i++)	//���93C46��DOλBusy/Ready״̬,�ʱ��Ϊ5ms
	{
		if(SDI == 1)
		break;
	}

	SCS = 0;
	FSENB = 0;	
}
/*******************************************************************************************************
�������ƣ�	uint	ERASE_AL(bit FirstOP_Reg,uint StartCommand_Reg)
�����ܣ�	��93C46��ȡ����
			FirstOP_Reg����һ��������		StartCommand_Reg����ʼ����
*******************************************************************************************************/

void	ERAL(bit FirstOP_Reg,uint StartCommand_Reg)
{
	ulong	i;
	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;
					
	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = StartCommand_Reg;
	FSTART = 1;					//������ϣ�FSTART��ϵͳ�Զ�����
	while(FSIOBZ);

	SCS = 0;
	SCS = 1;

	for(i=0;i<0X0D05;i++)	
	{
		if(SDI == 1)
		break;
	}

	FSENB = 0;
	SCS = 0;
}
