#include "stm8s.h"

#define SLAVE_ADDRESS 0x0B

typedef enum{
NoLoad,
Charge,
ChargeOver } WorkStatus;

WorkStatus work_status = NoLoad;

#define TIM4_PERIOD       156

#define RED_LED_ON 				GPIO_WriteHigh(GPIOA, GPIO_PIN_1)
#define RED_LED_OFF 			GPIO_WriteLow(GPIOA, GPIO_PIN_1)
#define RED_LED_REV 			GPIO_WriteReverse(GPIOA, GPIO_PIN_1)
#define GREEN_LED_ON 		GPIO_WriteHigh(GPIOA, GPIO_PIN_2)
#define GREEN_LED_OFF 	GPIO_WriteLow(GPIOA, GPIO_PIN_2)
#define GREEN_LED_REV 	GPIO_WriteReverse(GPIOA, GPIO_PIN_2)

#define MOS_SWITCH_ON 	GPIO_WriteHigh(GPIOC, GPIO_PIN_3)
#define MOS_SWITCH_OFF 	GPIO_WriteLow(GPIOC, GPIO_PIN_3)

__IO uint32_t TimingDelay = 0;

float i_sum;

void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

static void CLK_Config(void);
static void TIM4_Config(void);
static void GPIO_Config(void);
static void PWM_Config(void);
static void ADC1_Config(void);
static void I2C_Config(void);
void ADC_PWM_LED_Fun(void);

float ADC_Read(uint8_t channel);
void I2C_WriteData(u8 tData);

static void Flash_Config(void);
unsigned char Flash_read(uint16_t add);

bool F_ADD;
uint16_t PWMVal;
extern bool f_500ms;

uint8_t	Duty_I = 3;
uint8_t	Duty_U = 4;

// *********************************************************
// *                                      main
// *********************************************************
void main(void)
{
	CLK_Config();
	TIM4_Config();
	GPIO_Config();
	PWM_Config();
	ADC1_Config();
	Flash_Config();
	I2C_Config();
	
  while (1)
  {
		ADC_PWM_LED_Fun();
  }
}

// *********************************************************
// *                                      CLK_Config
// *********************************************************
static void CLK_Config(void)
{
//fmaster=fcpu=2MHz
	CLK->ECKR=0x00;
	CLK->ICKR=0x01;
	CLK->CMSR=0xe1;
	CLK->SWR=0xe1;
	CLK->CKDIVR=0x18;
 
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);
	
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);
}

static void TIM4_Config(void)
{
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  enableInterrupts();
	TIM4_Cmd(ENABLE);
}

#define  TIM1_PRESCALER_1    ((u16)0x00)

static void PWM_Config(void)
{
	TIM1_PrescalerConfig(TIM1_PRESCALER_1,TIM1_PSCRELOADMODE_IMMEDIATE);//1分频即不分配 允许事件更新
	TIM1_OC1Init(TIM1_OCMODE_PWM2,TIM1_OUTPUTSTATE_ENABLE,TIM1_OUTPUTNSTATE_ENABLE,0,TIM1_OCPOLARITY_LOW,TIM1_OCNPOLARITY_HIGH,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_SET);//PWM1模式TIM1_CounterModeConfig(TIM1_COUNTERMODE_UP);//向上计数模式
	TIM1_ARRPreloadConfig(ENABLE);		//重新预装载使能
	TIM1_OC1PreloadConfig(ENABLE);		//比较器2预状态使能
	TIM1_SetCounter(0);		//初始化计数值
	TIM1_SetAutoreload(255);		//0.125us周期 40*0.125=5us 200khz 周期是5us 5/0.125
	TIM1_SetCompare1(0);		//占空比值
	TIM1_CtrlPWMOutputs(ENABLE);		//PWM控制使能
	TIM1_Cmd(ENABLE);//使能TIM1计数
	TIM1_CCxNCmd(TIM1_CHANNEL_1,ENABLE);//第二通道 输出使能

  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 255);
  TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_LOW);
	TIM2_SetCompare1(0);
  TIM2_OC1PreloadConfig(ENABLE);
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_Cmd(ENABLE);
}

#define PWM_MAX 255
uint8_t PWM_U[5]={64  , 85  , 107, 128 , 150 }; 
float pwm_u_f[5]={1.16, 1.58,	2.0, 2.42, 2.84};
uint8_t PWM_I[4]={51 , 76 ,	102, 127}; 
float pwm_i_f[4]={1.157, 1.657,	2.157, 2.657};
uint8_t I_VAL_PWM = 0;
uint8_t U_VAL_PWM = 0;

float i_value_s[21];
uint8_t i_ptr;

bool u_ok = FALSE;
bool i_ok = FALSE;

extern bool U_refu_led;
extern bool I_refu_led;

extern bool f_10ms;
bool value_in = FALSE;
bool U_I_pre;
bool BOOL_BUF = FALSE;

extern u8 kkkkkk;
extern bool kkkkkk_ok;
void rx_data_process(uint8_t rx_buf);


bool if_in_charge = FALSE;
u8 num_cnt1;
u8 switch_num = 0;
u8 dec = 20;

void ADC_PWM_LED_Fun(void)		// CH4 电池电压检测 CH3 pwm 电流检测 CH2 pwm电压检测
{
	bool i_cnt_ok = FALSE;
	static uint8_t i_cnt = 0;
	float adc_read_value;
	
	if(kkkkkk_ok)
	{
		rx_data_process(kkkkkk);
		kkkkkk_ok = FALSE;
	}

	if((!U_I_pre) && (work_status == NoLoad))
	{
		if(!value_in)
		{
			TIM2_SetCompare1(5);	// K1 电流输出 PWM_I[Duty_I]
			TIM1_SetCompare1(5);	// K2 电压输出 PWM_U[Duty_U]
			
			I_VAL_PWM = PWM_I[Duty_I];
			U_VAL_PWM = PWM_U[Duty_U];
			value_in = TRUE;
		}
		if(f_10ms)
		{
			f_10ms = FALSE;
			if(!i_ok && ADC_Read(2) < pwm_i_f[Duty_I] && I_VAL_PWM < PWM_MAX)
			{
					I_VAL_PWM ++;
					TIM2_SetCompare1(I_VAL_PWM);	// K1 电流输出
			}
			else
			{
				i_ok = TRUE;
			}
			if(!u_ok && ADC_Read(5) < pwm_u_f[Duty_U] && U_VAL_PWM < PWM_MAX)
			{
					U_VAL_PWM ++;
					TIM1_SetCompare1(U_VAL_PWM);	// K2 电压输出
			}
			else
			{
				u_ok = TRUE;
			}
			if(u_ok && i_ok)
			{
				U_I_pre = TRUE;
				MOS_SWITCH_ON;			// 打开输出
			}
		}
	}
	else
	switch(work_status)
	{
		case NoLoad :
		{
			if(f_10ms) 		// led process
			{
				f_10ms = FALSE;
				switch_num++;
				if(switch_num == 1)
				GREEN_LED_ON;
				else if(switch_num == 11)
				GREEN_LED_OFF;
				else if(switch_num == 101)
				{
					switch_num = 0;
				}
			}
			if(ADC_Read(4) > 0.08)
			{
				if(dec == 0)
				{
					work_status = Charge;
				//	MOS_SWITCH_ON;			// 打开输出
					dec = 20;
				}
				else
				dec--;
			}
/*		else if(f_10ms)
			{
				f_10ms = FALSE;
				if(ADC_Read(2) > pwm_i_f[Duty_I] && I_VAL_PWM > 0)
				{
						I_VAL_PWM --;
						TIM2_SetCompare1(I_VAL_PWM);	// K1 电流输出
				}
				if(ADC_Read(5) > pwm_u_f[Duty_U] && U_VAL_PWM > 0)
				{
						U_VAL_PWM --;
						TIM1_SetCompare1(U_VAL_PWM);	// K2 电压输出
				}
			}
*/	}
		break;
		case ChargeOver : 
		{
/*			if(f_500ms)		// led process
			{
				f_500ms = FALSE;
				RED_LED_REV;
			}
*/			if(ADC_Read(3) < 0.8)
				{
					if(dec == 0)
					{
						work_status = NoLoad;
						MOS_SWITCH_ON;			// 打开输出
						dec = 20;
					}
					else
					dec--;
					
				}
		}
		break;
		case Charge :
		{
			if(f_10ms)
			{
				f_10ms = FALSE;
				
				switch_num++;
				if(switch_num == 1)
				GREEN_LED_ON;
				else if(switch_num == 51)
				GREEN_LED_OFF;
				else if(switch_num == 101)
				{
					switch_num = 0;
				}

				if(i_cnt < 50) i_cnt ++;
				else i_cnt_ok = TRUE;
				i_value_s[0] = ADC_Read(4);
				i_sum = 0.0;
				for(i_ptr = 0;i_ptr < 20;i_ptr ++)
				{
					i_value_s[20-i_ptr] = i_value_s[19-i_ptr];
					i_sum += i_value_s[20-i_ptr];
				}
				i_value_s[0] = i_sum / 20.0;
				
				if(i_value_s[0] < 0.05 && i_cnt_ok)
				{
						MOS_SWITCH_OFF;
								work_status = ChargeOver;
								GREEN_LED_ON;
								i_cnt = 0;
								i_cnt_ok = FALSE;
/*					if(!if_in_charge)
					{
						MOS_SWITCH_OFF;
						if_in_charge = TRUE;
					}
					else
					{
						num_cnt1 ++;
						if(num_cnt1 == 200)
						{
							num_cnt1 = 0;
							if(ADC_Read(3) < 0.8)
							{
								work_status = NoLoad;
								MOS_SWITCH_ON;
							}
							else
							{
								work_status = ChargeOver;
								GREEN_LED_ON;
							}
								i_cnt = 0;
								i_cnt_ok = FALSE;
						}
					}*/
				}
			}
		}
		break;
		default :
		{
		}
		break;
	}
	if(U_refu_led)
	{
		if(GPIO_ReadOutputData(GPIOA) & 0x02 == 0x02)
		{
			BOOL_BUF = TRUE;
			GREEN_LED_OFF;
		}
		Delay(50);
		switch(Duty_U)
		{
			case 4 :
			GREEN_LED_ON;
			Delay(20);
			GREEN_LED_OFF;
			Delay(20);
			case 3 :
			GREEN_LED_ON;
			Delay(20);
			GREEN_LED_OFF;
			Delay(20);
			case 2 :
			GREEN_LED_ON;
			Delay(20);
			GREEN_LED_OFF;
			Delay(20);
			case 1 :
			GREEN_LED_ON;
			Delay(20);
			GREEN_LED_OFF;
			Delay(20);
			case 0 :
			GREEN_LED_ON;
			Delay(20);
			GREEN_LED_OFF;
			break;
			default : 
			break;
		}
		Delay(50);
		if(BOOL_BUF)
		{
			GREEN_LED_ON;
			BOOL_BUF = FALSE;
		}
		U_refu_led = FALSE;
	}
	else if(I_refu_led)
	{
		if(GPIO_ReadOutputData(GPIOA) & 0x04 == 0x04)
		{
			BOOL_BUF = TRUE;
			RED_LED_OFF;
		}
		Delay(50);
		switch(Duty_I)
		{
			case 3 :
			RED_LED_ON;
			Delay(20);
			RED_LED_OFF;
			Delay(20);
			case 2 :
			RED_LED_ON;
			Delay(20);
			RED_LED_OFF;
			Delay(20);
			case 1 :
			RED_LED_ON;
			Delay(20);
			RED_LED_OFF;
			Delay(20);
			case 0 :
			RED_LED_ON;
			Delay(20);
			RED_LED_OFF;
			break;
			default : 
			break;
		}
		Delay(50);
		if(BOOL_BUF)
		{
			RED_LED_ON;
			BOOL_BUF = FALSE;
		}
		I_refu_led = FALSE;
	}
}

static void GPIO_Config(void)
{
	GPIO_DeInit(GPIOA);
	GPIO_Init(GPIOA, GPIO_PIN_1|GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);
	RED_LED_OFF;	GREEN_LED_OFF;
	
	GPIO_DeInit(GPIOC);
	GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);
	MOS_SWITCH_OFF;
	
	GPIO_DeInit(GPIOD);
	GPIO_Init(GPIOD, GPIO_PIN_2|GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
	
	RED_LED_ON;
	Delay(50);
	
	RED_LED_OFF;
	GREEN_LED_ON;
	Delay(50);
	
	GREEN_LED_OFF;
		Delay(50);

}

static void ADC1_Config(void){
	ADC1_DeInit();

	ADC1->CR1 = 0x00;
	ADC1->CR2 = 0x30;
	
	ADC1->CSR = 0x00;
	ADC1->CSR|= 0x04;
	
	ADC1->TDRL = 0x1C;            //禁止 AIN4 AIN3 AIN2 施密特触发
}

float ADC_Read(uint8_t channel)
{
	uint8_t i;
	uint16_t Value = 0;
	float f_value;
	
	ADC1->CSR &= ~0x0f;
	ADC1->CSR |= channel;
	
	ADC1->CR1 |= 0x01;
	for(i=0; i<20; i++);    // 延时一段时间，至少7uS，保证ADC模块的上电完成
	ADC1->CR1 |= 0x01;    // 使能ADC转换
	
	while((0x80 & ADC1->CSR) == 0x00);
	
	Value =  (((uint16_t)ADC1->DRH) << 2) + ADC1->DRL;		//左对齐 ADC_DRH高8字节 max = 0x3ff = 1023;
	f_value = (float)Value*5.0/1024.0;
	
	return f_value;
}

static void I2C_Config(void)
{
	I2C_DeInit();
	I2C_Init(100000, SLAVE_ADDRESS, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);           
  /* Enable Error Interrupt*/
  I2C_ITConfig((I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
  enableInterrupts();
}

void Flash_write(uint16_t , uint8_t );

static void Flash_Config(void)
{
	do{
		FLASH->DUKR = (uint8_t)0xAE;	/* Unlock data memory */
		FLASH->DUKR = (uint8_t)0x56;
	} while((FLASH->IAPSR & 0x08) == 0); // 若解锁未成功
	if(Flash_read(0x4000)==0X16 && Flash_read(0x4001)==0X17)
	{
		Duty_U = Flash_read(0x4002);
		Duty_I = Flash_read(0x4003);
		I_VAL_PWM = PWM_I[Duty_I];
		U_VAL_PWM = PWM_U[Duty_U];
	}
	else
	{
		Flash_write(0x4000, 0x16);
		Flash_write(0x4001, 0x17);
		Flash_write(0x4002, 0x00);
		Flash_write(0x4003, 0x00);
	}
}

void Flash_write(uint16_t add, uint8_t data)
{
	unsigned char *p;
	p = (unsigned char *)add; // 指针p指向芯片内部的EEPROM
	*p = data; // 写入第一个字节
	while((FLASH->IAPSR & 0x04) == 0); // 等待写操作成功
}

unsigned char Flash_read(uint16_t add)
{
	unsigned char r_byte;
	unsigned char *p;
	p = (unsigned char *)add; 	// 指针p指向芯片内部的EEPROM
	r_byte = *p;		// 将写入的内容读到变量r_byte中
	return r_byte;
}

void Delay(__IO uint32_t nTime)	// 延时nTime*10ms
{
  TimingDelay = nTime;
  while (TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}
#endif

