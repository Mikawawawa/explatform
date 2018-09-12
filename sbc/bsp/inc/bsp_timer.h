#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "stm32f4xx.h"

#define US(x)																	x*1
#define	MS(x)																	US(x)*1000
#define	S(x)																	MS(x)*1000

#define TIMER_DEFAULT_MODE										1u
#define TIMER_DEFAULT_PRIO										1u
#define TIMER_DEFAULT_SUB_PRIO									0u

#define	TIMER_MAX_TIME												S(2)

#define	TIMER_1																0x01
#define TIMER_2																0x02
#define	TIMER_3																0x04
#define	TIMER_4																0x08
#define	TIMER_5																0x10
#define	TIMER_6																0x20
#define	TIMER_7																0x40

#define TIMER_STA_INITIALIZED									1u
#define TIMER_STA_UNINITIALIZED								0u
#define TIMER_STA_ON													2u
#define TIMER_STA_OFF													3u


typedef struct timer_type{
	
	u8 													mode;
	u8 													preemption_priority;
	u8													sub_priority;
	volatile unsigned int 			status;
	u32 												time;
	TIM_TypeDef 								*name;
	char												handler_name[20];
	void												(*handler)(void);
	int 												(*install_handler)(void (*handler_func)());
	int 												(*uninstall_handler)();
	void												(*open)();
	void												(*close)();
	struct timer_type 					*pThis;
	
}timer_type_struct;

typedef struct {
	
	timer_type_struct 						*timer_1;
	timer_type_struct 						*timer_2;
	timer_type_struct 						*timer_3;
	timer_type_struct 						*timer_4;
	timer_type_struct 						*timer_5;
	timer_type_struct 						*timer_6;
	timer_type_struct 						*timer_7;
	
	u8 														timer_status;
	
	int (*init)										(u8 timer_num, u32 time);
	timer_type_struct	 						(*oop)(timer_type_struct *);
	timer_type_struct	 						*(*oop2)(timer_type_struct *);
	
}bsp_timer_struct;

extern bsp_timer_struct timer;

#endif
