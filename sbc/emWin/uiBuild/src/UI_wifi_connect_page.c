#include "uiBuild.h"

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:

    hItem = pMsg->hWin;
	FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	FRAMEWIN_SetFont(hItem,  &YaHei_24_Font);
	FRAMEWIN_SetText(hItem, "连接到无线网络 ");
    FRAMEWIN_SetTitleHeight(hItem, 14);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_WIFI_0);
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "WIFI名称: ");
  
  
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_WIFI_2);
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "加密方式: ");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_WIFI_4);
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "WIFI密码: ");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_WIFI_0);
	BUTTON_SetFont(hItem,  &YaHei_24_Font);
	BUTTON_SetText(hItem, "连接 ");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_WIFI_1);
	BUTTON_SetFont(hItem,  &YaHei_24_Font);
	BUTTON_SetText(hItem, "取消 ");
	
	//hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_WIFI_0);
    break;
	
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_WIFI_0: 
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
		  ui_state.wifi_connectwin_state = STATE_WIFI_CONNECTWIN_SHOW_KEYBOARD;
		  break;
      }
      break;
	case ID_BUTTON_WIFI_0:                           			//连接WIFI键 切换状态
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
		  ui_state.wifi_connectwin_state = STATE_WIFI_CONNECTWIN_CONNECT;
		  break;
	  }
      break;
	case ID_BUTTON_WIFI_1: 										//取消键
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
		  ui_state.wifi_connectwin_state = STATE_WIFI_CONNECTWIN_CANCEL;
		  break;
	  }
        break;
   
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       createFramewin
*/
WM_HWIN WifiConnectPageOnCreate(void);
WM_HWIN WifiConnectPageOnCreate(void) {
	
  WM_HWIN hWin;
	
  GUI_WIDGET_CREATE_INFO _aDialogcreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_WIFI_0, 275, 50, 300, 150, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_WIFI_0, 5, 5, 110, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_WIFI_1, 100, 5, 110, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_WIFI_2, 5, 35, 80, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_WIFI_3, 100, 35, 110, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_WIFI_4, 5, 65, 110, 30, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_WIFI_0, 100, 65, 130, 20, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_WIFI_0, 20, 95, 80, 25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_WIFI_1, 185, 95, 80, 25, 0, 0x0, 0 },
};
	
  hWin = GUI_CreateDialogBox(_aDialogcreate, GUI_COUNTOF(_aDialogcreate), _cbDialog, WM_HBKWIN, 0, 0);

  return hWin;
}



// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
