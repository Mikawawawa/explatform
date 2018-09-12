#ifndef __BSP_LP_RCC_H
#define __BSP_LP_RCC_H

#include "stm32f4xx.h"

typedef struct
{
	void				(*init)(void);
	
}lowPower_rcc_typdef;

extern lowPower_rcc_typdef lp_rcc_setting;


#endif

