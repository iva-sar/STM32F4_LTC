#include "LTC2440.h"

void LTC2440_GPIO_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

// Busy
	RCC_AHB1PeriphClockCmd(LTC2440_RCC_BUSY, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LTC2440_Pin_BUSY;       	// select the pin to modify
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;       		// set the mode to output
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  		// set the I/O speed to 100 MHz
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;      		// set the output type to open-drain
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;    		// set the pull-up to none
  GPIO_Init(LTC2440_BUSY, &GPIO_InitStruct);       		// do the init
	
//SDO
	RCC_AHB1PeriphClockCmd(LTC2440_RCC_SDO, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LTC2440_Pin_SDO;
	GPIO_Init(LTC2440_SDO, &GPIO_InitStruct);
	
//F0	
	RCC_AHB1PeriphClockCmd(LTC2440_RCC_F0, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LTC2440_Pin_F0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(LTC2440_F0, &GPIO_InitStruct);
	
	GPIO_WriteBit(LTC2440_F0, LTC2440_Pin_F0, Bit_RESET);
	
//SCK
	RCC_AHB1PeriphClockCmd(LTC2440_RCC_SCK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LTC2440_Pin_SCK;
	GPIO_Init(LTC2440_SCK, &GPIO_InitStruct);
	
//nCS
	RCC_AHB1PeriphClockCmd(LTC2440_RCC_nCS, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LTC2440_Pin_nCS;
	GPIO_Init(LTC2440_nCS, &GPIO_InitStruct);
	
	GPIO_WriteBit(LTC2440_nCS, LTC2440_Pin_nCS, Bit_SET);
	
//nEXT
	RCC_AHB1PeriphClockCmd(LTC2440_RCC_nEXT, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LTC2440_Pin_nEXT;
	GPIO_Init(LTC2440_nEXT, &GPIO_InitStruct);
	
	GPIO_WriteBit(LTC2440_nEXT, LTC2440_Pin_nEXT, Bit_RESET);
	
//SDI
	RCC_AHB1PeriphClockCmd(LTC2440_RCC_SDI, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LTC2440_Pin_SDI;
	GPIO_Init(LTC2440_SDI, &GPIO_InitStruct);
	
	GPIO_WriteBit(LTC2440_SDI, LTC2440_Pin_SDI, Bit_RESET);
	
	GPIO_WriteBit(LTC2440_nCS, LTC2440_Pin_nCS, Bit_RESET);
}

 //delay
void delay(void)
{
	uint8_t i=0;
	for(i=0; i<100; i++)
	{
		;
	}
}

uint8_t TEST_EOC()
{
	uint8_t tmp=0;
	
	GPIO_WriteBit(LTC2440_nCS, LTC2440_Pin_nCS, Bit_RESET);
	delay();
	if (!GPIO_ReadInputDataBit(LTC2440_SDO, LTC2440_Pin_SDO))
		tmp=1;
	else
		tmp=0;
	GPIO_WriteBit(LTC2440_nCS, LTC2440_Pin_nCS, Bit_SET);
	return tmp;
}

uint32_t Read_LTC2440(uint8_t in_data)
{
	uint8_t i=0;
	uint32_t tmp=0;
	
	GPIO_WriteBit(LTC2440_SCK, LTC2440_Pin_SCK, Bit_RESET);
	delay();
	GPIO_WriteBit(LTC2440_nCS, LTC2440_Pin_nCS, Bit_RESET);
	delay();
	
	for(i=0;i<32;i++)
	{	
		if(in_data & 0x10)
			GPIO_WriteBit(LTC2440_SDI, LTC2440_Pin_SDI, Bit_SET); //OSR input
		else
			GPIO_WriteBit(LTC2440_SDI, LTC2440_Pin_SDI, Bit_RESET);
		in_data<<=1;
		delay();
		
		GPIO_WriteBit(LTC2440_SCK, LTC2440_Pin_SCK, Bit_SET);
		delay();
		
		tmp<<=1;
		if(GPIO_ReadInputDataBit(LTC2440_SDO, LTC2440_Pin_SDO))
		{
			tmp|=1;
		}
		GPIO_WriteBit(LTC2440_SCK, LTC2440_Pin_SCK, Bit_RESET);
		delay();
	}
	GPIO_WriteBit(LTC2440_nCS, LTC2440_Pin_nCS, Bit_SET);
	return tmp;
}