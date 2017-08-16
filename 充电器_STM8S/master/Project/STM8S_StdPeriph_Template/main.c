#include "stm8s.h"
#include "main.h"

static void GPIO_Config(void);
static void TIM4_Config(void);
static void IIC_Config(void);
void UISetChk(void);

void main()
{
	GPIO_Config();
	TIM4_Config();
	IIC_Config();
		while (1)
    {
			UISetChk();
		}
}

static void IIC_Config(void)
{
	I2C_Init(I2C_SPEED, 0xA0, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);

	I2C_ITConfig((I2C_IT_TypeDef)(I2C_IT_EVT | I2C_IT_BUF) , ENABLE);
	
  enableInterrupts();
}

static void GPIO_Config(void)
{
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);
	
	GPIO_DeInit(GPIOA);
	GPIO_Init(GPIOA, GPIO_PIN_1 | GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_SLOW);
	GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);

	GPIO_DeInit(GPIOC);
	GPIO_Init(GPIOC, GPIO_PIN_HNIB|GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);

	GPIO_DeInit(GPIOD);
	GPIO_Init(GPIOD, GPIO_PIN_ALL, GPIO_MODE_IN_PU_NO_IT);
}

__IO uint8_t Tx_Idx = 0;
__IO uint8_t TxBuffer[BUFFERSIZE] = {0x16, 0x17, 0, 0};
void Delay(__IO uint32_t nCount);

void iic_send_data(u8 u, u8 i)
{
  TxBuffer[2] = u;
  TxBuffer[3] = i;

	while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY));
  I2C_GenerateSTART(ENABLE);
//	Delay(1000);
//	while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY));
}

#define LED1_REV GPIO_WriteReverse(GPIOA, GPIO_PIN_1)
#define LED2_REV GPIO_WriteReverse(GPIOA, GPIO_PIN_2)

extern bool f_10ms;


uint8_t read_u(void)
{
	uint8_t u_status;
		uint8_t port_value_u;
		port_value_u = (GPIO_ReadInputData(GPIOD) & 0x7C);	//|(GPIO_ReadInputData(GPIOC) & 0x08)
		switch(port_value_u)
		{
			case 0x3c : 	u_status = 0;		break;
			case 0x5c : 	u_status = 1;		break;
			case 0x6c : 	u_status = 2;		break;
			case 0x74 : 	u_status = 3;		break;
			case 0x78 : 	u_status = 4;		break;
			default :				u_status = 5;		break;
		}
		return u_status;
}

uint8_t read_i(void)
{
	uint8_t i_status;
		uint8_t port_value_i = GPIO_ReadInputData(GPIOC) & 0xF0;
		switch(port_value_i)
		{
			case 0x70 : 	i_status = 0;		break;
			case 0xb0 : 	i_status = 1;		break;
			case 0xd0 : 	i_status = 2;		break;
			case 0xe0 : 	i_status = 3;		break;
			default :				i_status = 4;		break;
		}
		return i_status;
}


void UISetChk(void)
{
	static u8 key_cnt = 0;
	static bool key_buf;
	static bool keyin = FALSE;
	bool key_sta;
	u8 u_buf , i_buf;
	if(f_10ms)
	{
		f_10ms = FALSE ;
		if((GPIO_ReadInputData(GPIOA) & 0X08) == 0X08)
		{
			key_sta = FALSE;
			if(key_buf != key_sta)
			{
				key_buf = FALSE;
				keyin = FALSE;
			}
		}
		else
		{
			key_sta = TRUE;
			if(key_buf != key_sta)
			{
				key_buf = TRUE;
				keyin = TRUE;
				key_cnt = 5;
			}
		}
		if(keyin)
		{
			if(key_cnt != 0)
			{
				key_cnt --;
			}
			else
			{
				keyin = FALSE;
				u_buf = read_u();
				i_buf = read_i();
				if(u_buf < 5 && i_buf < 4)
				{
					iic_send_data(u_buf, i_buf);
				}
			}
		}
	}
}

static void TIM4_Config(void)
{
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 156);
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  enableInterrupts();
	TIM4_Cmd(ENABLE);
}

void Delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)  {}
}
#endif

