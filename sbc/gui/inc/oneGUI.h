#ifndef __ONEGUI_H
#define __ONEGUI_H

#include "stm32f4xx.h"
#include "GUI.h"
#include "Icons.h"
#include "DIALOG.h"
#include "oneSpecializedSkin.h"
#include "oneConsole.h"
#include "WIDGET_keyboard.h"
#include "WIDGET_slidewin.h"
#include "FONT_yahei.h"

#define				__USE_SPECIALISED_SKIN								(1)
#define				__USE_CONSOLE													(1)
#define				__USE_FONT_LIB												(0)

#define				__USE_WIDGET_KEYBOARD									(1)
#define				__USE_WIDGET_SLIDEWIN									(1)

typedef struct {
	
	WIDGET_keyboardInfoStructTypedef 		*keyboard;
	WIDEGT_slidewinInfoStructTypedef 		*slidewin;
	
	void 																(*init)(void);		
}gui_type_struct;

extern gui_type_struct gui;

#endif
