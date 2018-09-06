#include "oneGUI.h"

static void init(void);
static void switchover(WM_HWIN sourse,WM_HWIN destination);

gui_type_struct gui = {
	&keyboard,
	&slidewin,
	init,
};

static void init()
{
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);  
	
#if GUI_WINSUPPORT
	WM_SetCreateFlags(WM_CF_MEMDEV);
#endif
	GUI_Init();
	GUI_EnableAlpha(1);
#if GUI_WINSUPPORT
	WM_MULTIBUF_Enable(1);
#endif

	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	
	GUI_SetXBF();
	GUI_UC_SetEncodeUTF8();
	
	console.init();
	
		
}


