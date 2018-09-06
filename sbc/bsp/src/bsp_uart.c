/**
  ******************************************************************************
  * @file    bsp_uart.c
  * @author  Hdu-Microchip-Lab
  * @version V1.0.0
  * @date    05-July-2018
  * @brief   UART driver for STM32F4xx devices
  *          该文件封装了STM32F4系列控制器中串口1-串口6的底层驱动，包括: 
	*
	*			 	- init(uart_number, bound): 	初始化串口uart_number，波特率为bound
	*				-	set_tx_len(len):						设置串口发送缓存长度(初始化前使用)
	*				-	set_rx_len(len):						设置串口接收缓存长度(初始化前使用)
  *      	- write(fmt, ...): 						向指定的串口发送缓存写入数据并发送
	*				- write_raw(raw_array,len):		向指定的串口发送缓冲区写入16进制数据并发送
	*				- write_line(fmt, ...): 			向指定的串口发送缓存写入数据并发送，添加换行符
	*				- read(buf): 									将串口接收缓存中的数据拷贝到buf中
	*       - clear():										清空串口收发缓存
	*******************************************************************************
**/



#include "bsp.h"

#if	(__USE_DRIVER_UART)

static uart_type_struct oop(uart_type_struct *uartObj);
static uart_type_struct *oop2(uart_type_struct *uartObj);
static int init(u8 uart_num, u32 bound);
static int set_rx_len(u16 len);
static int set_tx_len(u16 len);
static int write(char *fmt, ...);
static int write_raw(u8 raw_array[], int len);
static int write_line(char *fmt, ...);
static int read(u8 *pBuffer);
static int clear(void);

static void bsp_uart1_init(u32 bound);
static void bsp_uart2_init(u32 bound);
static void bsp_uart3_init(u32 bound);
static void bsp_uart4_init(u32 bound);
static void bsp_uart5_init(u32 bound);

/*********************************************************************
*
*       Param
*
**********************************************************************
*/

uart_type_struct uart_1 = {
	
	UART_DEFAULT_PTX,
	UART_DEFAULT_PRX,
	
	UART_STA_UNINITIALIZED,
	0u,
	UART_DEFAULT_RX_LEN,	
	UART_DEFAULT_TX_LEN,
	
	UART_DEFAULT_BOUND,
	USART1,

	write,
	write_raw,
	write_line,
	read,
	clear,
	set_rx_len,
	set_tx_len,
	NULL
	
};

uart_type_struct uart_2 = {
	
	UART_DEFAULT_PTX,
	UART_DEFAULT_PRX,
	
	UART_STA_UNINITIALIZED,
	0u,
	UART_DEFAULT_RX_LEN,	
	UART_DEFAULT_TX_LEN,
	
	UART_DEFAULT_BOUND,
	USART2,

	write,
	write_raw,
	write_line,
	read,
	clear,
	set_rx_len,
	set_tx_len,
	NULL
	
};

uart_type_struct uart_3 = {
	
	UART_DEFAULT_PTX,
	UART_DEFAULT_PRX,
	
	UART_STA_UNINITIALIZED,
	0u,
	UART_DEFAULT_RX_LEN,	
	UART_DEFAULT_TX_LEN,
	
	UART_DEFAULT_BOUND,
	USART3,

	write,
	write_raw,
	write_line,
	read,
	clear,
	set_rx_len,
	set_tx_len,
	NULL
	
};

uart_type_struct uart_4 = {
	
	UART_DEFAULT_PTX,
	UART_DEFAULT_PRX,
	
	UART_STA_UNINITIALIZED,
	0u,
	200u,	
	UART_DEFAULT_TX_LEN,
	
	UART_DEFAULT_BOUND,
	UART4,

	write,
	write_raw,
	write_line,
	read,
	clear,
	set_rx_len,
	set_tx_len,
	NULL
	
};

uart_type_struct uart_5 = {

	UART_DEFAULT_PTX,
	UART_DEFAULT_PRX,
	
	UART_STA_UNINITIALIZED,
	0u,
	200u,	
	UART_DEFAULT_TX_LEN,
	
	UART_DEFAULT_BOUND,
	UART5,

	write,
	write_raw,
	write_line,
	read,
	clear,
	set_rx_len,
	set_tx_len,
	NULL
	
};

uart_type_struct uart_6 = {

	UART_DEFAULT_PTX,
	UART_DEFAULT_PRX,
	
	UART_STA_UNINITIALIZED,
	0u,
	UART_DEFAULT_RX_LEN,	
	UART_DEFAULT_TX_LEN,
	
	UART_DEFAULT_BOUND,
	USART6,

	write,
	write_raw,
	write_line,
	read,
	clear,
	set_rx_len,
	set_tx_len,
	NULL
	
};

bsp_uart_struct uart = {
	
	(uart_type_struct*)&uart_1,
	(uart_type_struct*)&uart_2,
	(uart_type_struct*)&uart_3,
	(uart_type_struct*)&uart_4,
	(uart_type_struct*)&uart_5,
	(uart_type_struct*)&uart_6,
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
	* @参数：			uart_type_struct *uartObj
	* @返回值：		uart_type_struct  uartObj
	**********************************************
**/
static uart_type_struct oop(uart_type_struct *uartObj)
{
	if(NULL != uartObj)
		return *((uart_type_struct *)oo((void *)uartObj));
	else {
		__pError(SEG_FAULT, PERIPH_UART, "oop");
		__soft_hangup();
		return *uartObj;
	}
	
}

/**
	**********************************************
  * @函数名：		oop2
	*	@函数功能：	实现串口驱动的oop特性
	*							将对象存入ptrThis指针
	* @参数：			uart_type_struct *uartObj
	* @返回值：		uart_type_struct *uartObj
	**********************************************
**/
static uart_type_struct *oop2(uart_type_struct *uartObj)
{
	if(NULL != uartObj)
		return (uart_type_struct *)oo((void *)uartObj);
	else {
		__pError(SEG_FAULT, PERIPH_UART, "oop2");
		__soft_hangup();
		return uartObj;
	}
	
}

/**
	**********************************************
  * @函数名：		init
	*	@函数功能：	初始化串口驱动
	* @参数：			
	*							uart_num			-串口号
	*							bound					-波特率
	* @返回值：		NULL			
	**********************************************
**/
static int init(u8 uart_num, u32 bound)
{
	
	if(OO_STACK_UNINITIALIZED == oo_stack.sta) {
		__pError(SEG_FAULT, INIT, "init");
		__soft_hangup();
	}
	
	if(0x40 < uart_num)
		return __pError(UNKNOWN_PERIPH, PERIPH_UART, "init");
	
	if(uart_num & UART_1) {
		
		if(UART_STA_UNINITIALIZED == uart.uart_1->status) {
			bsp_uart1_init(bound);
			uart.uart_1->pTx_buffer = (u8 *)calloc((uart.uart_1->tx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_1->pTx_buffer)
					return __pError(SEG_FAULT, USART1_BASE, "init");
			uart.uart_1->pRx_buffer = (u8 *)calloc((uart.uart_1->rx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_1->pRx_buffer)
					return __pError(SEG_FAULT, USART1_BASE, "init");
			uart.uart_1->pThis = uart.uart_1;
			uart.uart_1->status = UART_STA_INITIALIZED;
		}
	}
	
	if(uart_num & UART_2) {
		
		if(UART_STA_UNINITIALIZED == uart.uart_2->status) {
			bsp_uart2_init(bound);
			uart.uart_2->pTx_buffer = (u8 *)calloc((uart.uart_2->tx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_2->pTx_buffer)
				return __pError(SEG_FAULT, USART2_BASE, "init");
			uart.uart_2->pRx_buffer = (u8 *)calloc((uart.uart_2->rx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_2->pRx_buffer)
				return __pError(SEG_FAULT, USART2_BASE, "init");
			uart.uart_2->pThis = uart.uart_2;
			uart.uart_2->status = UART_STA_INITIALIZED;
		}
	}
	
	if(uart_num & UART_3) {
		
		if(UART_STA_UNINITIALIZED == uart.uart_3->status) {
			bsp_uart3_init(bound);
			uart.uart_3->pTx_buffer = (u8 *)calloc((uart.uart_3->tx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_3->pTx_buffer)
				return __pError(SEG_FAULT, USART3_BASE, "init");
			uart.uart_3->pRx_buffer = (u8 *)calloc((uart.uart_3->rx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_3->pRx_buffer)
				return __pError(SEG_FAULT, USART3_BASE, "init");
			uart.uart_3->pThis = uart.uart_3;
			uart.uart_3->status = UART_STA_INITIALIZED;
		}
	}
	
	if(uart_num & UART_4) {
		
		if(UART_STA_UNINITIALIZED == uart.uart_4->status) {
			bsp_uart4_init(bound);
			uart.uart_4->pTx_buffer = (u8 *)calloc((uart.uart_4->tx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_4->pTx_buffer)
				return __pError(SEG_FAULT, UART4_BASE, "init");
			uart.uart_4->pRx_buffer = (u8 *)calloc((uart.uart_4->rx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_4->pRx_buffer)
				return __pError(SEG_FAULT, UART4_BASE, "init");
			uart.uart_4->pThis = uart.uart_4;
			uart.uart_4->status = UART_STA_INITIALIZED;
		}
	}
	
	if(uart_num & UART_5) {

		if(UART_STA_UNINITIALIZED == uart.uart_5->status) {
			bsp_uart5_init(bound);
			uart.uart_5->pTx_buffer = (u8 *)calloc((uart.uart_5->tx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_5->pTx_buffer)
				return __pError(SEG_FAULT, UART5_BASE, "init");
			uart.uart_5->pRx_buffer = (u8 *)calloc((uart.uart_5->rx_buffer_len), sizeof(u8 *));
			if(NULL == uart.uart_5->pRx_buffer)
				return __pError(SEG_FAULT, UART5_BASE, "init");
			uart.uart_5->pThis = uart.uart_5;
			uart.uart_5->status = UART_STA_INITIALIZED;
		}
	}
	
	if(UART_STA_UNINITIALIZED == uart.uart_status)
		uart.uart_status = 	UART_STA_INITIALIZED;
	else;
	
	return 0;
//	if(uart_num & UART_6)
//	{
//		bsp_uart6_init(bound);
//		uart.uart_6 = &uart_6;
//		uart.uart_6->status = UART_STA_INITIALIZED;
//	}

}

/**	
	*********************************************
  * @函数名：		set_tx_len
	*	@函数功能：	设置串口发送方缓存长度
	* @参数：			u16 len
	* @返回值：		
	*							缓存长度		@设置成功
	*							错误代码		@设置失败
	*********************************************
**/
static int set_tx_len(u16 len)
{
	uart_type_struct *pThis = (uart_type_struct *)oop_pop();
	
	/*修改缓存大小后，必须重新初始化*/
	if(UART_STA_INITIALIZED == pThis->status)													
		pThis->status = UART_STA_UNINITIALIZED;
	
	/*潜在的越界危险*/
	if(UART_MAX_TX_LEN < len)
		return __pError(SEG_FAULT, NAMEOF(pThis), "set_tx_len");
	else 
		pThis->tx_buffer_len = len;
	
	return len;
	
}

/**	
	*********************************************
  * @函数名：		set_rx_len
	*	@函数功能：	设置串口接收缓存长度
	* @参数：			u16 len
	* @返回值：		
	*							缓存长度		@设置成功
	*							错误代码		@设置失败
	*********************************************
**/
static int set_rx_len(u16 len)
{
	uart_type_struct *pThis = (uart_type_struct *)oop_pop();
	
	if(UART_STA_INITIALIZED == pThis->status)
		pThis->status = UART_STA_UNINITIALIZED;
	
	if(UART_MAX_RX_LEN < len)
		return __pError(SEG_FAULT, NAMEOF(pThis), "set_rx_len");
	else 
		pThis->rx_buffer_len = len;
	
	return len;
	
}

/**	
	*********************************************
  * @函数名：		write
	*	@函数功能：	通过串口发送数据
	* @参数：			char *fmt, ...
	* @返回值：		
	*							写入字节数	@发送成功
	*							错误代码		@发送失败
	*********************************************
**/
static int write(char *fmt, ...)
{
	u16 i,j;
	uart_type_struct *pThis = (uart_type_struct *)oop_pop();
	
	/*未初始化的串口*/
	if(NULL == pThis || UART_STA_UNINITIALIZED == pThis->status)
		return __pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "write");
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)pThis->pTx_buffer,fmt,ap);
	va_end(ap);
	i=strlen((const char*)pThis->pTx_buffer);
	
	/*内存溢出*/
	if(pThis->tx_buffer_len < i)
		__pError(OVERFLOW_FAULT, NAMEOF(pThis), "write");
	
	for (j=0; j<i; j++){
		while(USART_GetFlagStatus(pThis->name,USART_FLAG_TC)==RESET);   
		USART_SendData(pThis->name,(u16)(pThis->pTx_buffer[j]));  
	}
	
	return i;
	
}

/**
	**********************************************
  * @函数名：		write
	*	@函数功能：	通过串口发送数据，添加换行符
	* @参数：			char *fmt, ...
	* @返回值：		
	*							0						@发送成功
	*							错误代码		@发送失败
	**********************************************
**/
static int write_line(char *fmt, ...)
{
	u16 i,j;
	uart_type_struct *pThis = (uart_type_struct *)oop_pop();

	if(NULL == pThis || UART_STA_UNINITIALIZED == pThis->status)
		return __pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "write_line");
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)pThis->pTx_buffer,fmt,ap);
	va_end(ap);
	i=strlen((const char*)pThis->pTx_buffer);
	if(pThis->tx_buffer_len < i)
		__pError(OVERFLOW_FAULT, NAMEOF(pThis), "write_line");
	
	for (j=0; j<i; j++) {
		while (USART_GetFlagStatus(pThis->name,USART_FLAG_TC)==RESET);   
		USART_SendData(pThis->name,(u16)(pThis->pTx_buffer[j]));  
	}
	
	while (USART_GetFlagStatus(pThis->name,USART_FLAG_TC)==RESET);   
	USART_SendData(pThis->name,(u16)'\r'); 
	while (USART_GetFlagStatus(pThis->name,USART_FLAG_TC)==RESET);   
	USART_SendData(pThis->name,(u16)'\n'); 
	
	return (i+2);
	
}

/**	
	*********************************************
  * @函数名：		write
	*	@函数功能：	通过串口发送数据
	* @参数：			char *fmt, ...
	* @返回值：		
	*							写入字节数	@发送成功
	*							错误代码		@发送失败
	*********************************************
**/
static int write_raw(u8 raw_array[], int len)
{
	u16 j;
	uart_type_struct *pThis = (uart_type_struct *)oop_pop();
	
	/*未初始化的串口*/
	if(NULL == pThis || UART_STA_UNINITIALIZED == pThis->status)
		return __pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "write");
	/*内存溢出*/
	if(pThis->tx_buffer_len < len)
		__pError(OVERFLOW_FAULT, NAMEOF(pThis), "write");
	
	for (j=0; j<len; j++){
		while(USART_GetFlagStatus(pThis->name,USART_FLAG_TC)==RESET);   
		USART_SendData(pThis->name,(u16)(raw_array[j]));  
	}
	
	return j;
	
}

/**
	********************************************
  * @函数名：		read
	*	@函数功能：	读取串口缓存接收到的数据
	* @参数：			char *fmt, ...
	* @返回值：		
	*							0						@读取成功
	*							错误代码		@读取失败
	********************************************
**/
static int read(u8 *pBuffer)
{
	uart_type_struct *pThis = (uart_type_struct *)oop_pop();
	
	if(NULL == pThis || UART_STA_UNINITIALIZED == pThis->status)
		return __pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "read");
	
	/*内存错误*/
	if(NULL == pBuffer)
		return __pError(SEG_FAULT, NAMEOF(pThis), "read");
	
	if (strlen((const char *)pThis->pRx_buffer) > sizeof(pBuffer))
		return __pError(OVERFLOW_FAULT, NAMEOF(pThis), "read");
	
	strcpy((char *)pBuffer, (const char *)pThis->pRx_buffer);
	
	return 0;

}

/**
	*****************************************
  * @函数名：		write
	*	@函数功能：	清串口缓存
	* @参数：			NULL
	* @返回值：		
	*							0						@清除成功
	*							错误代码		@清除失败
	*****************************************
**/
static int clear()
{
	uart_type_struct *pThis = (uart_type_struct *)oop_pop();
	
	if(NULL == pThis || UART_STA_UNINITIALIZED == pThis->status)
		return __pError(UNINITIALIZED_FAULT, NAMEOF(pThis), "clear");

	if(NULL == pThis->pRx_buffer)
		return __pError(SEG_FAULT, NAMEOF(pThis), "clear");
	
	if(strlen(((const char *)pThis->pRx_buffer)) > 0u) {
		memset(pThis->pRx_buffer, 0, strlen(((const char *)pThis->pRx_buffer)));
	}
	else;
	
	return 0;

}

/************************************************HAL Level***********************************************/

static void bsp_uart1_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(USART1, &USART_InitStructure); 
	
	USART_Cmd(USART1, ENABLE);  
	USART_ClearFlag(USART1, USART_FLAG_TC);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);	

}

static void bsp_uart2_init(u32 bound)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

 	USART_DeInit(USART2);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  
	USART_Init(USART2, &USART_InitStructure);
 
	USART_Cmd(USART2, ENABLE);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);	
//	TIM7_Int_Init(100-1,8400-1);
//	USART2_RX_STA=0;
//	TIM_Cmd(TIM7, DISABLE);

}

static void bsp_uart3_init(u32 bound)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 
	USART_DeInit(USART3);  
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);  
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure); 
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		
	USART_Cmd(USART3, ENABLE);                
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);	
	
}

static void bsp_uart4_init(u32 bound)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

 	USART_DeInit(UART4);  
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  
	USART_Init(UART4, &USART_InitStructure); 
 
	USART_Cmd(UART4, ENABLE);             
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

}

static void bsp_uart5_init(u32 bound)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);	

 	USART_DeInit(UART5); 
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_Init(GPIOD,&GPIO_InitStructure); 
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  
	USART_Init(UART5, &USART_InitStructure); 
 
	USART_Cmd(UART5, ENABLE);               
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);	 
	
}

void USART1_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {	 
		res =USART_ReceiveData(USART1);		
		if(0 == (uart.uart_1->rx_status&(1<<15))) { 
			if(times < uart.uart_1->rx_buffer_len) {
				TIM_SetCounter(TIM7,0);		 
				if(uart.uart_1->rx_status==0) {
					uart.uart_1->rx_status|=1<<14; 
					times=0;
					TIM_Cmd(TIM7, ENABLE); 
				}
				uart.uart_1->pRx_buffer[times++]=res;		
				uart.uart_1->rx_status ++;			
			}
			else {
				__pError(OVERFLOW_FAULT, USART1_BASE, "IRQHandler"); 
				uart.uart_1->rx_status|=1<<15;	
			}
		}  	
	}										 
}  

void USART2_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {	 
		res =USART_ReceiveData(USART2);		
		if(0 == (uart.uart_2->rx_status&(1<<15))) { 
			if(times < uart.uart_2->rx_buffer_len) {
				TIM_SetCounter(TIM7,0);		 
				if(uart.uart_2->rx_status==0) {
					uart.uart_2->rx_status|=1<<14; 
					times=0;
					TIM_Cmd(TIM7, ENABLE); 
				}
				uart.uart_2->pRx_buffer[times++]=res;		
				uart.uart_2->rx_status++;			
			}
			else {
				__pError(OVERFLOW_FAULT, USART2_BASE, "IRQHandler");
				uart.uart_2->rx_status|=1<<15;	
			}
		}  	
	}										 
}  

void USART3_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {	 
		res =USART_ReceiveData(USART3);		
		if(0 == (uart.uart_3->rx_status&(1<<15))) { 
			if(times < uart.uart_3->rx_buffer_len) {
				TIM_SetCounter(TIM7,0);		 
				if(uart.uart_3->rx_status==0) {
					uart.uart_3->rx_status|=1<<14; 
					times=0;
					TIM_Cmd(TIM7, ENABLE); 
				}
				uart.uart_3->pRx_buffer[times++]=res;		
				uart.uart_3->rx_status++;			
			}
			else {
				__pError(OVERFLOW_FAULT, USART3_BASE, "IRQHandler");
				uart.uart_3->rx_status|=1<<15;	
			}
		}  	
	}										 
}  

void UART4_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) {	 
		res =USART_ReceiveData(UART4);		
		if(0 == (uart.uart_4->rx_status&(1<<15))) { 
			if(times < uart.uart_4->rx_buffer_len) {
				TIM_SetCounter(TIM7,0);		 
				if(uart.uart_4->rx_status==0) {
					uart.uart_4->rx_status|=1<<14; 
					times=0;
					TIM_Cmd(TIM7, ENABLE); 
				}
				uart.uart_4->pRx_buffer[times++]=res;		
				uart.uart_4->rx_status++;			
			}
			else  {
				__pError(OVERFLOW_FAULT, UART4_BASE, "IRQHandler");
				uart.uart_4->rx_status|=1<<15;	
			}
		}  	
	}										 
}  

void UART5_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {	 
		res =USART_ReceiveData(UART5);		
		if(0 == (uart.uart_5->rx_status&(1<<15))) { 
			if(times < uart.uart_5->rx_buffer_len) {
				TIM_SetCounter(TIM7,0);		 
				if(uart.uart_5->rx_status==0) {
					uart.uart_5->rx_status|=1<<14; 
					times=0;
					TIM_Cmd(TIM7, ENABLE); 
				}
				uart.uart_5->pRx_buffer[times++]=res;		
				uart.uart_5->rx_status++;			
			}
			else {
				__pError(OVERFLOW_FAULT, UART5_BASE, "IRQHandler");
				uart.uart_5->rx_status|=1<<15;	
			}
		}  	
	}										 
}  

#endif

/************************************************end of file***********************************************/

