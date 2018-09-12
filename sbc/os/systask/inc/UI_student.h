#ifndef __WIDGET_STUDENT
#define __WIDGET_STUDENT

#include "WM.h"
#include "GUI.h"

/*************************Ñ§ÉúUI×´Ì¬******************************/

#define		STATE_STUDENT_WAITING					0X00
#define		STATE_STUDENT_SWITCH_TO_TEACHERWIN		0X01
#define		STATE_STUDENT_SWITCH_TO_SETTINGWIN		0X02
#define		STATE_STUDENT_START_EXPERIMENT			0X03

typedef struct {
	WM_HWIN				hwin;
	
	WM_HWIN				(*create)(void);
	void				(*close)(void);	
	void				(*task)(void);	
	
}UI_studentwinInfoStructTypedef;

extern UI_studentwinInfoStructTypedef studentwin;

#endif



