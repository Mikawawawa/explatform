#include "bsp.h"

notify_type_struct timer6_notify = {0,0,0};

void timer6CallBack()
{
	timer6_notify.count_down_per_sec ++;
	timer6_notify.standby_per_min ++;
	timer6_notify.touch_resume_per_sec ++;
}

void bsp_Init()
{
//	DBGMCU_Config(DBGMCU_SLEEP, ENABLE);
	
	bsp_systick_init();
	oop_init();
	hbl_init();
	
	EXTIX_Init();
	SPI_FLASH_Init();
	
	lp_rcc_setting.init();
	uart.init(UART_4|UART_5, 9600);
	uart.init(UART_1|UART_3, 115200);
	timer.oop(timer.timer_6).install_handler(timer6CallBack);
	timer.init(TIMER_6|TIMER_7, MS(50));
	lcd.init();
	touch.init();
}


