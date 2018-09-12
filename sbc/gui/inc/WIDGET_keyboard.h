#ifndef __WIDEGT_KEYBOARD
#define __WIDEGT_KEYBOARD

#include "WM.h"
#include "GUI.h"

#define			WIDGET_KEYBOARD_STA_NOT_INITIALISED				0
#define			WIDGET_KEYBOARD_STA_INITIALISED						1
#define			WIDGET_KEYBOARD_STA_LITTLE								2
#define			WIDGET_KEYBOARD_STA_CAPS									3
#define			WIDGET_KEYBOARD_STA_NUMBER								4

#define			WIDGET_KEYBOARD_MINIUM_SIZE_X							250
#define			WIDGET_KEYBOARD_MINIUM_SIZE_Y							125

#define			WIDGET_KEYBOARD_MAXIUM_SIZE_X							800
#define			WIDGET_KEYBOARD_MAXIUM_SIZE_Y							400

#define			WIDGET_KEYBOARD_DEFAULT_AXIS_X						175
#define			WIDGET_KEYBOARD_DEFAULT_AXIS_Y						230

#define			WIDGET_KEYBOARD_DEFAULT_SIZE_X						500
#define			WIDGET_KEYBOARD_DEFAULT_SIZE_Y						250

#define			WIDGET_KEYBOARD_TYPE_STANDARD_EN					1
#define			WIDGET_KEYBOARD_TYPE_STANDARD_CH					2
#define			WIDGET_KEYBOARD_TYPE_NUMBER								3
#define			WIDGET_KEYBOARD_TYPE_SYMBLE								4

#define			WIDGET_KEYBOARD_BUFFER_LEN								50

typedef struct {
	unsigned int 					axis_x;
	unsigned int 					axis_y;
	unsigned int					size_x;
	unsigned int					size_y;
	
	unsigned	int					key_size;
	unsigned	int					key_interval;
	
	unsigned char					type;
	unsigned char 				status;
	
	unsigned char 				*content;
	unsigned char 				*content_index;
	
	WM_HWIN								hWin;
	
	WM_HWIN								(*create)(void);
	void									(*open)(void);
	void									(*close)(void);
	void									(*moveTo)(unsigned int axis_x, unsigned int axis_y);
	
}WIDGET_keyboardInfoStructTypedef;

extern unsigned char _Keyboard_Data[45][3][6];
extern WM_HWIN hKeyboard;
extern WIDGET_keyboardInfoStructTypedef keyboard;

WM_HWIN keyboardPageOnCreate(void);


#endif
