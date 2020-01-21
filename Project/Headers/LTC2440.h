#ifndef LTC_H
#define LTC_H

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_conf.h>
#include "usart.h"

#define LTC2440_RCC_BUSY		RCC_AHB1Periph_GPIOA
#define LTC2440_RCC_F0			RCC_AHB1Periph_GPIOA
#define LTC2440_RCC_SCK			RCC_AHB1Periph_GPIOA
#define LTC2440_RCC_SDO			RCC_AHB1Periph_GPIOA
#define LTC2440_RCC_nCS			RCC_AHB1Periph_GPIOA
#define LTC2440_RCC_nEXT		RCC_AHB1Periph_GPIOA
#define LTC2440_RCC_SDI			RCC_AHB1Periph_GPIOA

#define LTC2440_BUSY		GPIOA
#define LTC2440_F0			GPIOA
#define LTC2440_SCK			GPIOA
#define LTC2440_SDO			GPIOA
#define LTC2440_nCS			GPIOA
#define LTC2440_nEXT		GPIOA
#define LTC2440_SDI			GPIOA

#define LTC2440_Pin_BUSY		GPIO_Pin_1
#define LTC2440_Pin_F0			GPIO_Pin_2
#define LTC2440_Pin_SCK			GPIO_Pin_3
#define LTC2440_Pin_SDO			GPIO_Pin_6
#define LTC2440_Pin_nCS			GPIO_Pin_7
#define LTC2440_Pin_nEXT		GPIO_Pin_4
#define LTC2440_Pin_SDI			GPIO_Pin_0

#define SDI 0x17

void LTC2440_GPIO_init(void);
void delay(void);
uint8_t TEST_EOC(void);
uint32_t Read_LTC2440(unsigned char in_data);

#endif
