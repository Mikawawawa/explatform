#ifndef __UI_wifi_CONNECT
#define __UI_wifi_CONNECT

#include "WM.h"
#include "GUI.h"

#define STATE_WIFI_CONNECTWIN_WAIT				0x00
#define STATE_WIFI_CONNECTWIN_CONNECT			0x01
#define STATE_WIFI_CONNECTWIN_CANCEL			0x02
#define STATE_WIFI_CONNECTWIN_SHOW_KEYBOARD		0x03

typedef struct {
	WM_HWIN				hwin;
	
	WM_HWIN				(*create)(void);
	void				(*close)(void);	
	void				(*task)(void);	
	
}UI_wifi_connectwinInfoStructTypedef;

extern UI_wifi_connectwinInfoStructTypedef wifi_connectwin;

#endif



