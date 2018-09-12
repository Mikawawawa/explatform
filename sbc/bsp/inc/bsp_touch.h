#ifndef __BSP_TOUCH_H
#define	__BSP_TOUCH_H

#include "stm32f4xx.h"

#define				TP_NOT_PRESSED				0u
#define				TP_PRESSED						1u

typedef struct {
	uint16_t	x;
	uint16_t	y;
}coord_struct_type;

typedef struct {
	uint8_t							status;
	uint8_t							touch_number;
	coord_struct_type		coordXY[6];
	
	uint8_t							(*init)(void);
	uint8_t							(*scan)(void);
	
}bsp_touch_struct;

extern bsp_touch_struct touch;

#endif
