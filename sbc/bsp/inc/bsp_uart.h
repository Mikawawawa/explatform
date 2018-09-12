#ifndef __BSP_UART_H

#include "stm32f4xx.h"

#define UART_DEFAULT_BOUND										115200u
#define UART_DEFAULT_RX_LEN										1500u
#define UART_DEFAULT_TX_LEN										1000u
#define	UART_DEFAULT_PTX											(u8*)0
#define	UART_DEFAULT_PRX											(u8*)0

#define	UART_MAX_RX_LEN												4096u
#define	UART_MAX_TX_LEN												4096u

#define	UART_1																0x01
#define UART_2																0x02
#define	UART_3																0x04
#define	UART_4																0x08
#define	UART_5																0x10
#define	UART_6																0x20

#define UART_STA_GET_DATA											2u
#define UART_STA_INITIALIZED									1u
#define UART_STA_UNINITIALIZED								0u


typedef struct uart_type{
	
	u8 													*pTx_buffer;
	u8 													*pRx_buffer;
	u16					 								status;
	u16													rx_status;
	u16													rx_buffer_len;
	u16 												tx_buffer_len;
	u32 												bound_rate;
	USART_TypeDef 							*name;
	int 												(*write)( char *fmt, ...);
	int													(*write_raw)(u8 raw_array[], int len);
	int 												(*write_line)(char *fmt, ...);
	int 												(*read)(u8 *);
	int 												(*clear)();
	int													(*set_tx_len)(u16);
	int													(*set_rx_len)(u16);
	struct uart_type 						*pThis;
	
}uart_type_struct;

typedef struct {
	
	uart_type_struct 						*uart_1;
	uart_type_struct 						*uart_2;
	uart_type_struct 						*uart_3;
	uart_type_struct 						*uart_4;
	uart_type_struct 						*uart_5;
	uart_type_struct 						*uart_6;
	
	u8 													uart_status;
	
	int (*init)									(u8 uart_num, u32 bound);
	uart_type_struct	 					(*oop)(uart_type_struct *);
	uart_type_struct	 					*(*oop2)(uart_type_struct *);
	
}bsp_uart_struct;


	
extern bsp_uart_struct uart;

#endif /* __BSP_UART_H */

