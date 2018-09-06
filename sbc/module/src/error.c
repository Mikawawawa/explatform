#include "bsp.h"
#include "error.h"

volatile unsigned char 		error_periph[10];
volatile signed char			Err;


void __errno(unsigned long periph)
{
	switch (periph) {
		
	case INIT :
			strcpy((char *)error_periph, "INIT");
			break;
	
	case HANDLER :
			strcpy((char *)error_periph, "HANDLER");
			break;
	
	case SYSTICK :
			strcpy((char *)error_periph, "SYSTICK");
			break;
	
	case PARSE :
			strcpy((char *)error_periph, "PARSE");
			break;
		
	case PERIPH_UART :
			strcpy((char *)error_periph, "UART");
			break;
	
	case PERIPH_TIMER :
			strcpy((char *)error_periph, "TIMER");
			break;
	
	case USART1_BASE :
			strcpy((char *)error_periph, "USART1");
			break;
	
	case USART2_BASE :
			strcpy((char *)error_periph, "USART2");
			break;
	
	case USART3_BASE :
			strcpy((char *)error_periph, "USART3");
			break;
	
	case UART4_BASE :
			strcpy((char *)error_periph, "USART4");
			break;
	
	case UART5_BASE :
			strcpy((char *)error_periph, "USART1");
			break;
	
	case USART6_BASE :
			strcpy((char *)error_periph, "USART6");
			break;
	
	default :
			break;
	}
	
}

int __pError(error_type err, unsigned long periph, char name[])
{

/*warning level 0 -无报错*/	
#if (0 == WARNING_LEVEL)
	return 0;
#endif

/*warning level 1-报错，无挂起*/	
#if (0 != WARNING_LEVEL)	
	if(UART_STA_UNINITIALIZED == uart.uart_status || UART_STA_UNINITIALIZED == uart.uart_1->status) {
		Err = UNINITIALIZED_FAULT;
		goto hangup;
	}
	
	Err = err;
	__errno(periph);
	
	switch(err) {
		
	case SEG_FAULT :
		uart.oop(uart.uart_1).write_line("Error:SEG_FAULT @ %s FUNCTION %s", error_periph, name);
		break;
	
	case UNKNOWN_PERIPH :
		uart.oop(uart.uart_1).write_line("Error:KNOWN_PERIPH @ %s FUNCTION %s", error_periph, name);
		break;
	
	case UNINITIALIZED_FAULT :
		uart.oop(uart.uart_1).write_line("Error:UNINITIALIZED_PERIPH @ %s FUNCTION %s", error_periph, name);
		break;
	
	case OVERFLOW_FAULT :
		uart.oop(uart.uart_1).write_line("Error:OVERFLOW @ %s FUNCTION %s", error_periph, name);
		break;
		
	default :
			break;
	
	}

	hangup:
/*warning level 2 -报错并挂起*/		
#if(2 == WARNING_LEVEL)
	__soft_hangup();
	/*should never reach here*/
	return err;
#else
	return err;
#endif
	
#endif
	
}

void __soft_hangup()
{
	
	if(UART_STA_INITIALIZED == uart.uart_status && UART_STA_INITIALIZED == uart.uart_1->status) {
			uart.oop(uart.uart_1).write_line("Irrecovreable Failure");
			uart.oop(uart.uart_1).write_line("Enter Software Hang Up");
	}
	__disable_irq();
	
	while(1) {
	}
	
}



