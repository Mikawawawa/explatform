#include "oneGUI.h"

#if (__USE_WIDGET_SLIDEWIN)

#define ID_WINDOW_SLIDEWIN   (GUI_ID_USER + 0x00)

static void _cbDialog(WM_MESSAGE * pMsg) {

  switch (pMsg->MsgId) {
 
		default:
			WM_DefaultProc(pMsg);
			break;
  }
}


WM_HWIN SlidewinPageOnCreate(void);

WM_HWIN SlidewinPageOnCreate(void) {
	
	const GUI_WIDGET_CREATE_INFO _aDialogcreate[] = {
		{ WINDOW_CreateIndirect, "Window", ID_WINDOW_SLIDEWIN, slidewin.axis_x, slidewin.axis_y, slidewin.size_x, slidewin.size_y, 0, 0x0, 0 },
	};
	
  WM_HWIN hWin;
	
  hWin = GUI_CreateDialogBox(_aDialogcreate, GUI_COUNTOF(_aDialogcreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

#endif
