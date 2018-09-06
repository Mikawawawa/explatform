#ifndef __WIDGET_SETTING
#define __WIDGET_SETTING

#include "WM.h"
#include "GUI.h"

#define		STATE_SETTING_WAITING					0X00
#define		STATE_SETTING_SWITCH_TO_STUDENTWIN		0X01
#define		STATE_SETTING_SWITCH_TO_TEACHERWIN		0X02
#define		STATE_SETTING_WIFI_SCAN					0X03
#define		STATE_SETTING_WIFI_CONNECT				0X04
#define		STATE_SETTING_VOICE_SETTING				0X05
#define		STATE_SETTING_VOICE_SWITCH				0X06
#define		STATE_SETTING_VOICE_VOLUME				0X07
#define		STATE_SETTING_STANDBY					0X08
#define		STATE_SETTING_ENTER_PRIV				0X09


typedef struct {
	WM_HWIN				hwin;
	
	WM_HWIN				(*create)(void);
	void				(*close)(void);	
	void				(*task)(void);	
	
}UI_settingwinInfoStructTypedef;

extern UI_settingwinInfoStructTypedef settingwin;

#endif



