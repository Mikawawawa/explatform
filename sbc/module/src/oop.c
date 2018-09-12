#include "oop.h"
#include "error.h"

volatile ooStack_type_struct 	oo_stack;
volatile int									semaphore;

void *oo(void *hObj)	
{
	
	if(0 != hObj) 
		oop_push(hObj);
	
	return hObj;
	
}

void oop_init()
{
	if(OO_STACK_INITIALIZED == oo_stack.sta) 
		return;
	
	oo_stack.base = calloc(sizeof(void **), OO_STACK_DEPTH);
	if(NULL == oo_stack.base) {
		__pError(SEG_FAULT, INIT, "init");
		__soft_hangup();
	}
	
	oo_stack.head = oo_stack.base;
	oo_stack.depth = 0;
	oo_stack.sta = OO_STACK_INITIALIZED;
	
}

void oop_push(void *pThis)
{
	
	__LOCK();
	if(OO_STACK_UNINITIALIZED == oo_stack.sta) {
		__pError(SEG_FAULT, INIT, "init");
		__soft_hangup();
	}
	
	if(OO_STACK_DEPTH <= oo_stack.depth) {
		__pError(SEG_FAULT, INIT, "init");
		__soft_hangup();
	}
	
	oo_stack.head  += 1;
	*(oo_stack.head) = pThis;
	oo_stack.depth += 1;
	__UNLOCK();
	
}

void *oop_pop()
{
	
	void *pThis;
	
	__LOCK();
	if(OO_STACK_UNINITIALIZED == oo_stack.sta) {
		__pError(SEG_FAULT, INIT, "init");
		__soft_hangup();
	}
	
	if(0 == oo_stack.depth) {
		__pError(SEG_FAULT, INIT, "init");
		__soft_hangup();
	}
	
	pThis = *(oo_stack.head);
	oo_stack.depth -= 1;
	oo_stack.head  -= 1;
	__UNLOCK();	
	
	return pThis;
	
}










	
	
	
	
	
	
	
	
	
