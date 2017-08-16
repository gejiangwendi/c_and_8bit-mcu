#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

#include "stm8s.h"

#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_i2c.h"
#include "stm8s_tim4.h"

//#include "stm8s_uart1.h"
//#include "stm8s_adc1.h"
//#define USE_FULL_ASSERT    (1) 

#ifdef  USE_FULL_ASSERT

#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif 

#endif 
