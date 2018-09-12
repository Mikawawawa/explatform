#ifndef __HANDLER_H
#define __HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define 		ARG_STACK_DEPTH									10

#define 		ARG_END													'\r'



typedef struct {
	void 	**base;
	void 	**head;
	int 	depth;
}param_stack_struct_type;

typedef struct handler_block{
	
	unsigned char							name[20];
	void											(*pHandler)(void *, ...);
	unsigned char							handler_number;
	unsigned int							time_ticks;
	volatile unsigned int			time_ticks_reamin;
	
	param_stack_struct_type		param_stack;
	struct handler_block			*next;
	
}handler_block_list;

extern handler_block_list *pHBL;

int hbl_init(void);
void hbl_param_push(handler_block_list *pNode, void * ptr_param);
handler_block_list *hbl_traverse(unsigned char number);
unsigned char hbl_traverse_v_name(unsigned char *name);
void hbl_insert(handler_block_list *pHandler, unsigned char number);
void hbl_delete(unsigned char number);
void hbl_install_handler(unsigned char *handler_name, void *pHandler, ...);
void hbl_uninstall_handler(unsigned char *handler_name);













#endif
