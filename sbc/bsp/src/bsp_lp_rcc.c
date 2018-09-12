#include "bsp.h"

void init(void);

lowPower_rcc_typdef lp_rcc_setting = {
	init
};

void init()
{
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOA,DISABLE);
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOB,DISABLE);
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOC,DISABLE);
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOD,DISABLE);
	
	RCC_APB1PeriphClockLPModeCmd(RCC_APB1Periph_USART3,DISABLE);
	RCC_APB1PeriphClockLPModeCmd(RCC_APB1Periph_UART4,DISABLE);
	RCC_APB1PeriphClockLPModeCmd(RCC_APB1Periph_UART5,DISABLE);
}







