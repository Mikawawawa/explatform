#include "handler.h"
#include "error.h"

handler_block_list *pHBL;

int hbl_init()
{
	pHBL = (handler_block_list *)calloc(sizeof(handler_block_list), 1);
	if(NULL == pHBL) {
		__pError(SEG_FAULT, HANDLER, "hbl_init");
		__soft_hangup();
	}
	
	pHBL->param_stack.base = (void **)calloc(sizeof(void *), 10);
	if(NULL == pHBL->param_stack.base) {
		__pError(SEG_FAULT, HANDLER, "hbl_init");
		__soft_hangup();
	}
	pHBL->param_stack.head = pHBL->param_stack.base;
	
	strcpy((char *)pHBL->name, "root");
	pHBL->handler_number = 0u;
	pHBL->time_ticks = 0u;
	pHBL->time_ticks_reamin = 0u;
	pHBL->pHandler = NULL;
	pHBL->next = NULL;
	
	return 0;
	
}

void hbl_param_push(handler_block_list *pNode, void * ptr_param)
{
	
	if(NULL == pHBL->param_stack.base) {
		__pError(SEG_FAULT, HANDLER, "hbl_param_push");
		__soft_hangup();
	}
	
	if(ARG_STACK_DEPTH <= pHBL->param_stack.depth) {
		__pError(OVERFLOW_FAULT, HANDLER, "hbl_param_push");
		__soft_hangup();
	}
	
	
	*(pNode->param_stack.head) = ptr_param;
	pNode->param_stack.head ++;
	
}

void *hbl_param_pop()
{
	if(NULL == pHBL->param_stack.base) {
		__pError(SEG_FAULT, HANDLER, "hbl_param_pop");
		__soft_hangup();
	}
	
	if(0 == pHBL->param_stack.depth) {
		__pError(OVERFLOW_FAULT, HANDLER, "hbl_param_pop");
		__soft_hangup();
	}
	
	return *(pHBL->param_stack.head--);
}

handler_block_list *hbl_traverse(unsigned char number)
{
	unsigned char i;
	handler_block_list *pIndex = pHBL;
	
	if(pIndex->handler_number < number)
		__pError(OVERFLOW_FAULT, HANDLER, "hbl_traverse");
	
	for (i=0; i<number; i++){
		if(NULL == pIndex || NULL == pIndex->next) {
			__pError(SEG_FAULT, HANDLER, "hbl_traverse");
			__soft_hangup();
		}
		pIndex = pIndex->next;
	}
	
	return pIndex;
}

unsigned char hbl_traverse_v_name(unsigned char *name)
{
	unsigned char i;
	handler_block_list *pIndex = pHBL;
	
	if(NULL == name) {
		__pError(SEG_FAULT, HANDLER, "hbl_traverse_v_name");
		__soft_hangup();
	}
	
	for (i=0; i<pHBL->handler_number+2; i++) {
		if(NULL == pIndex)
			return 0;
		if(!strcmp((const char *)pIndex->name, (const char *)name))
			return i;
		pIndex = pIndex->next;
	}
	
	return 0;
}

void hbl_insert(handler_block_list *pNode, unsigned char number)
{
	handler_block_list *pIndex = pHBL;
	
	if(NULL == pHBL) {
		__pError(SEG_FAULT, HANDLER, "hbl_insert");
		__soft_hangup();
	}
	
	if(NULL == pNode) {
		__pError(SEG_FAULT, HANDLER, "hbl_insert");
		__soft_hangup();
	}
	
	if(number > 0)
		pIndex = hbl_traverse(number-1);
	else
		pIndex = hbl_traverse(number);
	
	if(NULL == pIndex->next) {
		pIndex->next = pNode;
		pNode->next = NULL;
		pIndex->handler_number += 1;
	}
	else {
		pNode->next = pIndex->next;
		pIndex->next = pNode;
		pIndex->handler_number += 1;
	}
	
}

void hbl_delete(unsigned char number)
{
	handler_block_list *pIndex = NULL;
	handler_block_list *pFree  = NULL;
	
	if(NULL == pHBL) {
		__pError(SEG_FAULT, HANDLER, "hbl_delete");
		__soft_hangup();
	}
	
	pIndex = hbl_traverse(number-1);
	if(NULL == pHBL->next) {
		__pError(SEG_FAULT, HANDLER, "hbl_delete");
		__soft_hangup();
	}
	
	pFree = pIndex->next;
	pIndex->next = pIndex->next->next;
	free(pFree);
	pIndex->handler_number -= 1;
	
}
	
void hbl_install_handler(unsigned char *handler_name, void *pHandler, ...)
{
	handler_block_list *pIndex = pHBL;
	handler_block_list *pNode = NULL;
	long ptr_param;
	va_list ap;
	
	if(NULL == pHBL || NULL == pHandler) {
		__pError(SEG_FAULT, PERIPH_TIMER, "install_handler");
		__soft_hangup();
	}
	
	pNode = (handler_block_list *)calloc(sizeof(handler_block_list), 1);
	if(NULL == pNode) {
		__pError(SEG_FAULT, PERIPH_TIMER, "install_handler");
		__soft_hangup();
	}
	
	pNode->handler_number = pHBL->handler_number+1;
	strcpy((char *)pNode->name, (const char *)handler_name);
	pNode->pHandler = pHandler;
	
	va_start(ap, pHandler);	
	
	ptr_param = va_arg(ap, long);
	while(ptr_param != 0) {
		hbl_param_push(pNode, (void *)ptr_param);
		ptr_param = va_arg(ap, long);
	}
	va_end(ap);

	hbl_insert(pNode, pHBL->handler_number);
	
}

void hbl_uninstall_handler(unsigned char *handler_name)
{
	unsigned char Index = 0;
	
	if(NULL == pHBL) {
		__pError(SEG_FAULT, PERIPH_TIMER, "install_handler");
		__soft_hangup();
	}
	
	Index = hbl_traverse_v_name(handler_name);
	if(0 == Index) {
		__pError(SEG_FAULT, PERIPH_TIMER, "uninstall_handler");
		return;
	}
		
	hbl_delete(Index);
	
}
		








