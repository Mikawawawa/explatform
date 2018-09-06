#ifndef __OOP_H
#define __OOP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define			OO_STACK_DEPTH									10

#define 		OO_STACK_INITIALIZED						1
#define			OO_STACK_UNINITIALIZED					0

			
#define 		__LOCK()												__disable_irq()
#define 		__UNLOCK()											__enable_irq()


typedef struct {
	
	void										**head;
	void 										**base;
	unsigned char						depth;
	unsigned char						sta;
	
}ooStack_type_struct;

extern volatile ooStack_type_struct oo_stack;

void oop_init(void);
void oop_push(void *pThis);
void *oop_pop(void);

void* oo(void *hObj);

#endif

