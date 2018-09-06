#include "systask.h"

static void _cbDialog(WM_MESSAGE * pMsg) {
	 
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 1);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_24_Font);
    TEXT_SetText(hItem,"");
  
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_24_Font);
    TEXT_SetText(hItem,"管理员模式 ");
  
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_5);
	IMAGE_SetBitmap(hItem ,&bmwifi);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_6);
	IMAGE_SetBitmap(hItem ,&bmvolume);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_7);
	IMAGE_SetBitmap(hItem ,&bmstandby);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_8);
	IMAGE_SetBitmap(hItem ,&bmhdu);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_9);
	IMAGE_SetBitmap(hItem ,&bmhduText);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_A);
	IMAGE_SetBitmap(hItem ,&bmplatform);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_B);
	IMAGE_SetBitmap(hItem ,&bmwifi_off);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_C);
	WM_HideWindow(hItem);
	IMAGE_SetBitmap(hItem ,&bmvolume);
	
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_D);
	WM_HideWindow(hItem);
	IMAGE_SetBitmap(hItem ,&bmswitchText);
	
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_E);
	WM_HideWindow(hItem);
	IMAGE_SetBitmap(hItem ,&bmvolumeText);
	
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
	WM_HideWindow(hItem);
	SLIDER_SetWidth(hItem, 30);
	SLIDER_SetRange(hItem, 10, 99);
	SLIDER_SetSkin(hItem, SKIN_slider2C);
	
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
	WM_HideWindow(hItem);
	LISTVIEW_SetFont(hItem,GUI_FONT_16B_ASCII);
	LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SELFOCUS,GUI_BLACK);
    LISTVIEW_AddColumn(hItem, 175, "WIFI", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 75, "STATE", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddColumn(hItem, 150, "WPA", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_SetGridVis(hItem, 1);
	
    
	pushButtonInitSettingDialog(pMsg->hWin);
	pushButtonInitVolumeSwitchDialog(pMsg->hWin);
	
    break;
	
  case WM_PAINT:
	GUI_SetColor(0x00ADADAD);
	GUI_DrawHLine(125,30,200);
	GUI_DrawHLine(165,30,200);
	GUI_DrawHLine(205,30,200);
	GUI_DrawVLine(230,85,385);
	GUI_DrawVLine(231,85,385);
   
	break;
	
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) 
	{
		case ID_LISTVIEW_0:
		  switch(NCode)
		  {
			  case WM_NOTIFICATION_RELEASED:
				ui_state.settingwin_state = STATE_SETTING_WIFI_CONNECT;
			  break;
		  }
		  break;
			
		case ID_SLIDER_0: 
		  switch(NCode) 
		  {
			  case WM_NOTIFICATION_VALUE_CHANGED:
				  ui_state.settingwin_state = STATE_SETTING_VOICE_VOLUME;
				break;
		  }
		  break;

		case ID_BUTTON_0: 
		  switch(NCode) 
		  {
			  case WM_NOTIFICATION_RELEASED:
				  ui_state.settingwin_state = STATE_SETTING_SWITCH_TO_STUDENTWIN;
				break;
			  
		  }
		  break;
		  
		case ID_BUTTON_1: 
		  switch(NCode)
		  {
			  case WM_NOTIFICATION_RELEASED:
				  ui_state.settingwin_state = STATE_SETTING_SWITCH_TO_TEACHERWIN;
				break;
		  }
		  break;
		  
		case ID_BUTTON_2: // 扫描WIFI按键
		  switch(NCode) 
		  {
			  case WM_NOTIFICATION_RELEASED:
				  ui_state.settingwin_state = STATE_SETTING_WIFI_SCAN;
				break;
			  
		  }
		  break;
		case ID_BUTTON_3:  //声音设置按键
		  switch(NCode) 
		  {
			  case WM_NOTIFICATION_RELEASED:
				  ui_state.settingwin_state = STATE_SETTING_VOICE_SETTING;
				break;
		  }
		  break;
		case ID_BUTTON_4:  // 休眠模式按键
		  switch(NCode) {
			  case WM_NOTIFICATION_RELEASED:
				  ui_state.settingwin_state = STATE_SETTING_STANDBY;
				break;
		  }
		  break;
		case ID_BUTTON_5:  //声音开关按键	即刻生效
		  switch(NCode) 
		  {
			  case WM_NOTIFICATION_RELEASED:
				  app_state.voice_state = ~app_state.voice_state;
				break;

		  }
		  break;
		case ID_BUTTON_6: //管理员模式按键
		  switch(NCode) 
		  {
			  case WM_NOTIFICATION_RELEASED:
				  ui_state.settingwin_state = STATE_SETTING_ENTER_PRIV;
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

WM_HWIN SettingPageOnCreate(void);
WM_HWIN SettingPageOnCreate(void) {
	
	GUI_WIDGET_CREATE_INFO _aDialogcreate[] = {
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 30, 380, 60, 53, 0, 0, 0 },				//student
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 155, 380, 60, 53, 0, 0, 0 },			//setting
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 70, 95, 80, 20, 0, 0, 0 },				//wifi
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 73, 135, 80, 20, 0, 0, 0 },				//volume
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 67, 175, 80, 20, 0, 0, 0 },				//standby
	{ BUTTON_CreateIndirect, "button", ID_BUTTON_5, 550, 150, 60, 60, 0, 0, 0 },			//volume switch
	{ BUTTON_CreateIndirect, "button", ID_BUTTON_6, 80, 240, 60, 60, 0, 0, 0 },				//manager mode
	{ LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 350, 100, 400, 250, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 415, 360, 250, 20, 0, 0x64, 0 },				//提示框
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 60, 310, 100, 24, 0, 0x64, 0 },				//管理员模式
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_5, 30, 90, 30, 30, 0, 0, 0  },				//WIFI
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_6, 30, 130, 30, 30, 0, 0, 0 },				//音量
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_7, 30, 170, 30, 30, 0, 0, 0 },				//休眠
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_8, 250, 15, 70, 71, 0, 0, 0 },				//杭电logo
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_9, 390, 390, 300, 45, 0, 0, 0 },				//杭州电子科技大学
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_A, 330, 30, 450, 50, 0, 0, 0 },				//实训平台
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_B, 5, 5, 30, 30, 0, 0, 0  },					//WIFI状态
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_C, 40, 5, 30, 30, 0, 0, 0 },					//音量状态
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_D, 280, 160, 120, 36, 0, 0, 0  },				//提示音开关文字
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_E, 280, 240, 120, 36, 0, 0, 0 },				//提示音音量文字
	{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 550, 245, 150, 30, 0, 0x0, 0 },			
	};
	
	WM_HWIN hWin;
	hWin = GUI_CreateDialogBox(_aDialogcreate, GUI_COUNTOF(_aDialogcreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

/*************************** End of file ****************************/
