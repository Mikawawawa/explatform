/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��
*	�ļ����� : bsp.h
*	˵    �� : ���ǵײ�����ģ�����е�h�ļ��Ļ����ļ��� Ӧ�ó���ֻ�� #include bsp.h ���ɣ�
*			  ����Ҫ#include ÿ��ģ��� h �ļ�
*
*	�޸ļ�¼ :
*		�汾��  ����         ����                  ˵��
*		V1.0    2018-01-28   HDU-Microchip_Lab.    ��ʽ����
*
*	Copyright (C), 2015-2020
*
*********************************************************************************************************
*/

#ifndef __BSP_H
#define __BSP_H

#define		__USE_DRIVER_SYSTICK								(1)
#define		__USE_DRIVER_UART									(1)
#define		__USE_DRIVER_TIMER									(1)
#define		__USE_DRIVER_LCD									(1)
#define		__USE_DRIVER_TOUCH									(1)
#define     __USE_SPI_FLASH										(1)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "stm32f4xx.h"
#include "oop.h"
#include "error.h"
#include "handler.h"
#include "parse.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
#include "timers.h"

#include "ff.h"

#include "GUI.h"

#include "handler.h"

#include "bsp_systick.h"
#include "bsp_uart.h"
#include "bsp_timer.h"
#include "bsp_stmflash.h"
#include "bsp_lcd.h"
#include "bsp_gt9147.h"
#include "bsp_ctiic.h"
#include "bsp_touch.h"
#include "bsp_spi_flash.h"
#include "bsp_exti.h"
#include "bsp_lp_rcc.h"

typedef struct
{
	u16 touch_resume_per_sec;
	u16 count_down_per_sec;
	u16 standby_per_min;
}notify_type_struct;

extern notify_type_struct timer6_notify;

/* �ṩ������C�ļ����õĺ��� */
void bsp_Init(void);

#endif
