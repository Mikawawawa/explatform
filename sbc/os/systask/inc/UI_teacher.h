#ifndef __WIDGET_TEACHER
#define __WIDGET_TEACHER

#include "WM.h"
#include "GUI.h"

#define		STATE_TEACHER_WAITING					0X00
#define		STATE_TEACHER_SWITCH_TO_STUDENTWIN		0X01
#define		STATE_TEACHER_SWITCH_TO_SETTINGWIN		0X02
#define		STATE_TEACHER_START_HTTP				0X03
#define		STATE_TEACHER_START_MARK				0X04

typedef struct {
	WM_HWIN				hwin;
	
	WM_HWIN				(*create)(void);
	void				(*close)(void);	
	void				(*task)(void);	
	
}UI_teacherwinInfoStructTypedef;

extern UI_teacherwinInfoStructTypedef teacherwin;

#endif



