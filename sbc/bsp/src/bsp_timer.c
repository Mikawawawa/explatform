#include "bsp.h"

#if	(__USE_DRIVER_TIMER)

static timer_type_struct oop(timer_type_struct *timerObj);
static timer_type_struct *oop2(timer_type_struct *timerObj);
static int init(u8 timer_num, u32 time);
static int install_handler(void (*handler_func)());
static int uninstall_handler(void);
static void open(void);
static void close(void);

static void bsp_timer1_init(u16 arr, u16 psc, u16 prio, u16 sub_prio);
static void bsp_timer2_init(u16 arr,u16 psc, u16 prio, u16 sub_prio);
static void bsp_timer3_init(u16 arr,u16 psc, u16 prio, u16 sub_prio);
static void bsp_timer4_init(u16 arr,u16 psc, u16 prio, u16 sub_prio);
static void bsp_timer5_init(u16 arr,u16 psc, u16 prio, u16 sub_prio);
static void bsp_timer6_init(u16 arr,u16 psc, u16 prio, u16 sub_prio);
static void bsp_timer7_init(u16 arr,u16 psc, u16 prio, u16 sub_prio);

timer_type_struct timer_1 = {
	
	TIMER_DEFAULT_MODE,
	TIMER_DEFAULT_PRIO,
	TIMER_DEFAULT_SUB_PRIO,
	TIMER_STA_UNINITIALIZED,
	US(0),
	TIM1,
	"timer1_handler",
	NULL,
	install_handler,
	uninstall_handler,
	open,
	close,
	NULL
	
};

timer_type_struct timer_2 = {
	
	TIMER_DEFAULT_MODE,
	TIMER_DEFAULT_PRIO,
	TIMER_DEFAULT_SUB_PRIO,
	TIMER_STA_UNINITIALIZED,
	US(0),
	TIM2,
	"timer2_handler",
	NULL,
	install_handler,
	uninstall_handler,
	open,
	close,
	NULL
	
};

timer_type_struct timer_3 = {
	
	TIMER_DEFAULT_MODE,
	TIMER_DEFAULT_PRIO,
	TIMER_DEFAULT_SUB_PRIO,
	TIMER_STA_UNINITIALIZED,
	US(0),
	TIM3,
	"timer3_handler",
	NULL,
	install_handler,
	uninstall_handler,
	open,
	close,
	NULL
	
};

timer_type_struct timer_4 = {
	
	TIMER_DEFAULT_MODE,
	TIMER_DEFAULT_PRIO,
	TIMER_DEFAULT_SUB_PRIO,
	TIMER_STA_UNINITIALIZED,
	US(0),
	TIM4,
	"timer4_handler",
	NULL,
	install_handler,
	uninstall_handler,
	open,
	close,
	NULL
	
};

timer_type_struct timer_5 = {
	
	TIMER_DEFAULT_MODE,
	TIMER_DEFAULT_PRIO,
	TIMER_DEFAULT_SUB_PRIO,
	TIMER_STA_UNINITIALIZED,
	US(0),
	TIM5,
	"timer5_handler",
	NULL,
	install_handler,
	uninstall_handler,
	open,
	close,
	NULL
	
};

timer_type_struct timer_6 = {
	
	TIMER_DEFAULT_MODE,
	2,
	0,
	TIMER_STA_UNINITIALIZED,
	US(0),
	TIM6,
	"timer6_handler",
	NULL,
	install_handler,
	uninstall_handler,
	open,
	close,
	NULL
	
};

timer_type_struct timer_7 = {
	
	TIMER_DEFAULT_MODE,
	3,
	0,
	TIMER_STA_UNINITIALIZED,
	US(0),
	TIM7,
	"timer7_handler",
	NULL,
	install_handler,
	uninstall_handler,
	open,
	close,
	NULL
	
};

bsp_timer_struct timer = {
	
	(timer_type_struct*)&timer_1,
	(timer_type_struct*)&timer_2,
	(timer_type_struct*)&timer_3,
	(timer_type_struct*)&timer_4,
	(timer_type_struct*)&timer_5,
	(timer_type_struct*)&timer_6,
	(timer_type_struct*)&timer_7,
	0,
	init,
	oop,
	oop2

};

/*********************************************************************
*
*       Function
*
**********************************************************************
*/

/**
	**********************************************
  * @函数名：		oop
	*	@函数功能：	实现串口驱动的oop特性
	*							将对象存入ptrThis指针
	* @参数：			timer_type_struct *timerObj
	* @返回值：		timer_type_struct  timerObj
	**********************************************
**/
static timer_type_struct oop(timer_type_struct *timerObj)
{
	if(NULL != timerObj)
		return *((timer_type_struct *)oo((void *)timerObj));
	else {
		__pError(SEG_FAULT, PERIPH_TIMER, "oop");
		__soft_hangup();
		return *timerObj;
	}
	
}

/**
	**********************************************
  * @函数名：		oop2
	*	@函数功能：	实现串口驱动的oop特性
	*							将对象存入ptrThis指针
	* @参数：			timer_type_struct *timerObj
	* @返回值：		timer_type_struct *timerObj
	**********************************************
**/
static timer_type_struct *oop2(timer_type_struct *timerObj)
{
	if(NULL != timerObj)
		return (timer_type_struct *)oo((void *)timerObj);
	else {
		__pError(SEG_FAULT, PERIPH_TIMER, "oop2");
		__soft_hangup();
		return timerObj;
	}
	
}

static int init(u8 timer_num, u32 time)
{
	
	u16 arr = 0, psc = 0;

	if(OO_STACK_UNINITIALIZED == oo_stack.sta) {
		__pError(SEG_FAULT, INIT, "init");
		__soft_hangup();
	}
	
	if(0x80 < timer_num)
		return __pError(UNKNOWN_PERIPH, PERIPH_TIMER, "init");
	
	if(time > TIMER_MAX_TIME)
		time = TIMER_MAX_TIME;
	
	if(time <= MS(10)) {
		arr = time - 1;
		psc = 83;
	}
	
	else if(time > MS(10)) {
		arr = 999 + (time % 4096)-1;
		psc = (time / (arr+1))*84;
	}
	
	
	if(timer_num & TIMER_1) {
		
		if(TIMER_STA_UNINITIALIZED == timer.timer_1->status) {
			bsp_timer1_init(arr, psc, timer.timer_1->preemption_priority, timer.timer_1->sub_priority);
			timer.timer_1->pThis = timer.timer_1;
			timer.timer_1->status = TIMER_STA_INITIALIZED;
		}
	}
	
	if(timer_num & TIMER_2) {
		
		if(TIMER_STA_UNINITIALIZED == timer.timer_2->status) {
			bsp_timer2_init(arr, psc, timer.timer_2->preemption_priority, timer.timer_2->sub_priority);
			timer.timer_2->pThis = timer.timer_2;
			timer.timer_2->status = TIMER_STA_INITIALIZED;
		}
	}
	
	if(timer_num & TIMER_3) {
		
		if(TIMER_STA_UNINITIALIZED == timer.timer_3->status) {
			bsp_timer3_init(arr, psc, timer.timer_3->preemption_priority, timer.timer_3->sub_priority);
			timer.timer_3->pThis = timer.timer_3;
			timer.timer_3->status = TIMER_STA_INITIALIZED;
		}
	}
	
	if(timer_num & TIMER_4) {
		
		if(TIMER_STA_UNINITIALIZED == timer.timer_4->status) {
			bsp_timer4_init(arr, psc, timer.timer_4->preemption_priority, timer.timer_4->sub_priority);
			timer.timer_4->pThis = timer.timer_4;
			timer.timer_4->status = TIMER_STA_INITIALIZED;
		}
	}
	
	if(timer_num & TIMER_5) {
		
		if(TIMER_STA_UNINITIALIZED == timer.timer_5->status) {
			bsp_timer5_init(arr, psc, timer.timer_5->preemption_priority, timer.timer_5->sub_priority);
			timer.timer_5->pThis = timer.timer_5;
			timer.timer_5->status = TIMER_STA_INITIALIZED;
		}
	}
	
	if(timer_num & TIMER_6) {
		
		if(TIMER_STA_UNINITIALIZED == timer.timer_6->status) {
			bsp_timer6_init(arr, psc, timer.timer_6->preemption_priority, timer.timer_6->sub_priority);
			timer.timer_6->pThis = timer.timer_6;
			timer.timer_6->status = TIMER_STA_INITIALIZED;
		}
	}
	
	if(timer_num & TIMER_7) {
		
		if(TIMER_STA_UNINITIALIZED == timer.timer_7->status) {
			bsp_timer7_init(arr, psc, timer.timer_7->preemption_priority, timer.timer_7->sub_priority);
			timer.timer_7->pThis = timer.timer_7;
			timer.timer_7->status = TIMER_STA_INITIALIZED;
		}
	}
	
	return 0;
}

static int install_handler(void (*handler_func)())
{
	timer_type_struct *pThis = (timer_type_struct *)oop_pop();
	
	if(NULL == handler_func) {
		__pError(SEG_FAULT, PERIPH_TIMER, "install_handler");
		__soft_hangup();
	}
	
	pThis->handler = handler_func;
	
	return 0;
	
}
	
static int uninstall_handler()
{
	timer_type_struct *pThis = (timer_type_struct *)oop_pop();
	
	if(TIMER_STA_UNINITIALIZED == pThis->status) 
		return __pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "uninstall_handler");
	
	pThis->handler = NULL;
	
	return 0;
	
}	

static void open()
{
	timer_type_struct *pThis = (timer_type_struct *)oop_pop();
	
	if(TIMER_STA_UNINITIALIZED == pThis->status)
		__pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "on");
	
	TIM_Cmd(pThis->name, ENABLE);
}

static void close()
{
	timer_type_struct *pThis = (timer_type_struct *)oop_pop();
	
	if(TIMER_STA_UNINITIALIZED == pThis->status)
		__pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "off");
	
	TIM_Cmd(pThis->name, DISABLE);
}

/************************************************HAL Level***********************************************/	
static void bsp_timer1_init(u16 arr, u16 psc, u16 prio, u16 sub_prio)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period=arr;   
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM1,DISABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_TIM10_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=prio; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=sub_prio; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}	

static void bsp_timer2_init(u16 arr,u16 psc, u16 prio, u16 sub_prio)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period=arr;   
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM2,DISABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=prio; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=sub_prio; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}	

static void bsp_timer3_init(u16 arr,u16 psc, u16 prio, u16 sub_prio)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period=arr;   
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM3,DISABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=prio; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=sub_prio; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}	

static void bsp_timer4_init(u16 arr,u16 psc, u16 prio, u16 sub_prio)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period=arr;   
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM4,DISABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=prio; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=sub_prio; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}	

static void bsp_timer5_init(u16 arr,u16 psc, u16 prio, u16 sub_prio)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period=arr;   
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM5,DISABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=prio; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=sub_prio; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}	

static void bsp_timer6_init(u16 arr,u16 psc, u16 prio, u16 sub_prio)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period=arr;   
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM6,ENABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=prio; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=sub_prio; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}	

static void bsp_timer7_init(u16 arr,u16 psc, u16 prio, u16 sub_prio)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 
	

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); 
	
	TIM_Cmd(TIM7,DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=prio; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=sub_prio; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//TIM_Cmd(TIM7, DISABLE); 
}	

/************************************************IRQ Server Func***********************************************/

void TIM1_IRQHandler(void)
{
	if(SET == TIM_GetITStatus(TIM1,TIM_IT_Update)) {
		if(NULL == timer.timer_1->handler) 
			__pError(SEG_FAULT, TIM1_BASE, "TIM1_IRQHandler");
		else
			timer.timer_1->handler();
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update); 
}	

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) {
		if(NULL == timer.timer_2->handler) 
			__pError(SEG_FAULT, TIM2_BASE, "TIM2_IRQHandler");
		else
			timer.timer_2->handler();
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
}	

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) {
		if(NULL == timer.timer_3->handler) 
			__pError(SEG_FAULT, TIM3_BASE, "TIM3_IRQHandler");
		else
			timer.timer_3->handler();
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); 
}	

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) {
		if(NULL == timer.timer_4->handler) 
			__pError(SEG_FAULT, TIM4_BASE, "TIM4_IRQHandler");
		else
			timer.timer_4->handler();
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update); 
}	

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) {
		if(NULL == timer.timer_5->handler) 
			__pError(SEG_FAULT, TIM5_BASE, "TIM5_IRQHandler");
		else
			timer.timer_5->handler();
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update); 
}	

void TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) {
		if(NULL == timer.timer_6->handler) 
			__pError(SEG_FAULT, TIM6_BASE, "TIM6_IRQHandler");
		else
			timer.timer_6->handler();
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 
}	

void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//是更新中断
	{	 			
		if(uart.uart_5->rx_status&0x4000)
		{
			uart.uart_5->rx_status|=1<<15;	//标记接收完成
		}
		if(uart.uart_4->rx_status&0x4000)
		{
			uart.uart_4->rx_status|=1<<15;	//标记接收完成
		}
		if(uart.uart_3->rx_status&0x4000)
		{
			uart.uart_3->rx_status|=1<<15;	//标记接收完成
		}
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIM7更新中断标志    
		TIM_Cmd(TIM7, DISABLE);  //关闭TIM7 
	}
}	
	
#endif	
	
	



