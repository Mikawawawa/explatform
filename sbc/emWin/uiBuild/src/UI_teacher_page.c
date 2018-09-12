#include "uiBuild.h"

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN      hItem;
  int          NCode;
  int          Id;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
	
	BUTTON_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_TEACHER_0), 0);  
    BUTTON_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_TEACHER_1), 0);  
    BUTTON_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_TEACHER_2), 0);  
  	EDIT_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_EDIT_TEACHER_0), 0);  
	EDIT_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_EDIT_TEACHER_1), 0);    
	
	hItem = pMsg->hWin;
	FRAMEWIN_SetTitleHeight(hItem, 1);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_TEACHER_0);
	IMAGE_SetBitmap(hItem ,&bmplatform);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_TEACHER_1);
	IMAGE_SetBitmap(hItem ,&bmhduText);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_TEACHER_2);
	IMAGE_SetBitmap(hItem ,&bmhdu);
  
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_TEACHER_6);
	IMAGE_SetBitmap(hItem,&bmwifi_off);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TEACHER_0);
	TEXT_SetFont(hItem, &YaHei_24_Font);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	TEXT_SetText(hItem,"请点击屏幕右方按钮，进行身份验证 ");
 
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TEACHER_3);
	TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_36_Font);
	TEXT_SetText(hItem,"学生姓名 ");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TEACHER_2);
	TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_36_Font);
	TEXT_SetText(hItem,"学生学号 ");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TEACHER_1);
	TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_36_Font);
	TEXT_SetText(hItem,"学生成绩 ");
 
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_TEACHER_0);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(hItem, &YaHei_36_Font);
    EDIT_SetText(hItem, "");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_TEACHER_1);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(hItem,  &YaHei_36_Font);
    EDIT_SetText(hItem, "");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TEACHER_0);
	DROPDOWN_SetFont(hItem, GUI_FONT_32B_ASCII);
    DROPDOWN_SetListHeight(hItem, 170);
    DROPDOWN_AddString(hItem, "");
    DROPDOWN_AddString(hItem, "A");
    DROPDOWN_AddString(hItem, "B");
    DROPDOWN_AddString(hItem, "C");
    DROPDOWN_AddString(hItem, "D");
	WM_SetFocus(hItem);
	
	pushButtonInitTeacherDialog(pMsg->hWin);
    break;
	
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_DROPDOWN_TEACHER_0: 
		hItem = WM_GetFocussedWindow();
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
		  ui_state.teacherwin_state = STATE_TEACHER_START_MARK;
        break;
      }
      break;
    case ID_BUTTON_TEACHER_0: // 切换状态
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:	
		 ui_state.teacherwin_state = STATE_TEACHER_START_HTTP;
        break;
      }
      break;
    
	case ID_BUTTON_TEACHER_1: 
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
		  ui_state.teacherwin_state = STATE_TEACHER_SWITCH_TO_STUDENTWIN;
        break;
      }
      break;
	  
	case ID_BUTTON_TEACHER_2: 
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
		  ui_state.teacherwin_state = STATE_TEACHER_SWITCH_TO_SETTINGWIN;
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

WM_HWIN TeacherPageOnCreate(void);
WM_HWIN TeacherPageOnCreate(void) {
	
  GUI_WIDGET_CREATE_INFO _aDialogcreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_TEACHER_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_TEACHER_0, 200, 25, 450, 50, 0, 0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_TEACHER_1, 265, 390, 300, 45, 0, 0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_TEACHER_2, 120, 15, 70, 71, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_TEACHER_0, 255, 350, 300, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_TEACHER_1, 105, 272, 150, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_TEACHER_2, 105, 202, 150, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_TEACHER_3, 105, 130, 150, 30, 0, 0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_TEACHER_6, 5, 5, 30, 30, 0, 0, 0  },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_TEACHER_0, 300, 135, 170, 35, 0, 0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_TEACHER_1, 300, 205, 170, 35, 0, 0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_TEACHER_0, 300, 275, 170, 38, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_TEACHER_0, 540, 190, 80, 62, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_TEACHER_1, 710, 390, 60, 53, 0, 0x0, 0 },     //学生
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_TEACHER_2, 710, 20, 60, 60, 0, 0x0, 0 },		 //设置
};
	
  WM_HWIN hWin;
  hWin = GUI_CreateDialogBox(_aDialogcreate, GUI_COUNTOF(_aDialogcreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
