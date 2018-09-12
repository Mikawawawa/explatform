#include "bsp.h"
#include "uiBuild.h"

#if (__USE_WIDGET_KEYBOARD)

SpecializedSkinTypedef _button_info[45];

static WM_HWIN create(void);
static void open(void);
static void close(void);
static void moveTo(unsigned int axis_x, unsigned int axis_y);

WIDGET_keyboardInfoStructTypedef keyboard = {
	WIDGET_KEYBOARD_DEFAULT_AXIS_X,
	WIDGET_KEYBOARD_DEFAULT_AXIS_Y,
	WIDGET_KEYBOARD_DEFAULT_SIZE_X,
	WIDGET_KEYBOARD_DEFAULT_SIZE_Y,
	
	0,
	0,
	
	WIDGET_KEYBOARD_TYPE_STANDARD_EN,
	WIDGET_KEYBOARD_STA_NOT_INITIALISED,
	
	NULL,
	NULL,
	
	(WM_HWIN)0,
	
	create,
	open,
	close,
	moveTo
	
};

unsigned char _keyboard_Data[45][3][6] = 
	{
		{"q","Q",""},{"w","W",""},{"e","E",""},{"r","R",""},{"t","T",""},{"y","Y",""},{"u","U",""},{"i","I",""},{"o","O",""},{"p","P",""},
			{"a","A",""},{"s","S",""},{"d","D",""},{"f","F",""},{"g","G",""},{"h","H",""},{"j","J",""},{"k","K",""},{"l","L",""},
				{"z","Z",""},{"x","X",""},{"c","C",""},{"v","V",""},{"b","B",""},{"n","N",""},{"m","M",""},
					{"caps","CAPS",""},{"Del","Del",""},{"123","123","ABC"},{",./",",./","ABC"},{",",",",""},{"SPACE","SPACE",""},{".",".",""},{"EN","EN","CH"},{"OK","OK","RET"},
						{"0","0",""},{"1","1",""},{"2","2",""},{"3","3",""},{"4","4",""},{"5","5",""},{"6","6",""},{"7","7",""},{"8","8",""},{"9","9",""}
	};

static WM_HWIN create()
{
	SpecializedSkinTypedef *button;
	unsigned char i;
	
	keyboard.key_interval = 5;
	keyboard.key_size = keyboard.size_x / 10 - keyboard.key_interval * 2;
	
	keyboard.content = (unsigned char *)calloc(sizeof(char), WIDGET_KEYBOARD_BUFFER_LEN);
	if(NULL == keyboard.content)
		return (WM_HWIN)0;
	
	keyboard.content_index = keyboard.content;
	keyboard.type = WIDGET_KEYBOARD_TYPE_STANDARD_EN;
	keyboard.status = WIDGET_KEYBOARD_STA_LITTLE;
	keyboard.hWin = keyboardPageOnCreate();	
	
	for(i=0; i<45; i++) {
		
		/*CAPS, DEL, NUM, SYM, SPACE, C/E, ENTER*/
		if(0x1A == i || 0x1B == i ||0x1C == i || 0x1D == i || 0x1F == i || 0x21 == i || 0x22 == i) {
			_button_info[i].normal = &bmkeyType2Up;
			_button_info[i].mark = &bmkeyType2Down;
			_button_info[i].size_x = 60;
			_button_info[i].size_y = 40;
		}
		else {
			_button_info[i].normal = &bmunikeyUp;
			_button_info[i].mark = &bmunikeyDown;
			_button_info[i].size_x = 40;
			_button_info[i].size_y = 40;
		}
		_button_info[i].content = _keyboard_Data[i][0];
		button = &_button_info[i];
		WM_SetUserData(WM_GetDialogItem(keyboard.hWin, (GUI_ID_USER + i + 1)), (const void *)&button, sizeof(button));
	}
	
	return keyboard.hWin;
	
}

static void open()
{
	
	WM_ShowWin(keyboard.hWin);
}

static void close()
{
	WM_HideWin(keyboard.hWin);
}

static void moveTo(unsigned int axis_x, unsigned int axis_y)
{
	WM_MoveTo(keyboard.hWin, axis_x, axis_y);
}

#endif



