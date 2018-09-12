#ifndef _ERROR_H
#define __ERROR_H

#define 		WARNING_LEVEL										2


#define 		NAMEOF(pThis)										(u32)(pThis->name)

#define			INIT														(unsigned long)0x00010000
#define			HANDLER													(unsigned long)0x00020000	
#define  		SYSTICK													(unsigned long)0x00030000	
#define  		PARSE														(unsigned long)0x00040000	
#define			PERIPH_UART											(unsigned long)0x00050000
#define 		PERIPH_TIMER										(unsigned long)0x00060000	

#define 		__pError_FAULT									1

#define 		SEG_FAULT												-1
#define			UNINITIALIZED_FAULT							-2
#define 		OVERFLOW_FAULT									-3
#define 		UNKNOWN_PERIPH									-4

typedef signed char error_type;
int __pError(error_type err, unsigned long periph, char name[]);
void __soft_hangup(void);

#endif

