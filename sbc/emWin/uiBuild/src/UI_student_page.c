#include "uiBuild.h"

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN      hItem;
  int          NCode;
  int          Id;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
	  
	hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 1);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_STUDENT_0);
	IMAGE_SetBitmap(hItem ,&bmplatform);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_STUDENT_1);
	IMAGE_SetBitmap(hItem ,&bmhduText);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_STUDENT_2);
	IMAGE_SetBitmap(hItem ,&bmhdu);
  
	hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_STUDENT_6); 
	IMAGE_SetBitmap(hItem,&bmwifi_off);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_STUDENT_0);
	TEXT_SetFont(hItem, &YaHei_24_Font);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	TEXT_SetText(hItem,"欢迎使用智能物联电工电子实验台 ");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_STUDENT_1);
	TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_36_Font);
	TEXT_SetText(hItem,"预约人姓名 ");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_STUDENT_2);
	TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_36_Font);
	TEXT_SetText(hItem,"预约人学号 ");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_STUDENT_3);
	TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_36_Font);
	TEXT_SetText(hItem,"预约实验 ");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_STUDENT_4);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_36_Font);
	TEXT_SetText(hItem,"实验剩余时间 ");
	WM_HideWindow(hItem);
    
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_STUDENT_0);		//提示框
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_STUDENT_1);		//姓名
	EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(hItem,  &YaHei_36_Font);
	EDIT_SetText(hItem,"");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_STUDENT_2);		//学号
	EDIT_SetFont(hItem,  &YaHei_36_Font);
	EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetText(hItem,"");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_STUDENT_3);		//实验
	EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(hItem,  &YaHei_36_Font);
	EDIT_SetText(hItem,"");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_STUDENT_4);		//小时
	EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(hItem,  &YaHei_40_Font);
	EDIT_SetText(hItem,"");
	WM_HideWindow(hItem);
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_STUDENT_2);
	BUTTON_SetFocussable(hItem,1);
	
	pushButtonInitStudentDialog(pMsg->hWin);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_STUDENT_0: 
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
		  ui_state.studentwin_state = STATE_STUDENT_SWITCH_TO_TEACHERWIN;
        break;
      }
      break;
    case ID_BUTTON_STUDENT_1: 
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
		  ui_state.studentwin_state = STATE_STUDENT_SWITCH_TO_SETTINGWIN;
        break;
      }
      break;
    case ID_BUTTON_STUDENT_2:    // 切换状态
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
		  ui_state.studentwin_state = STATE_STUDENT_START_EXPERIMENT;
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

WM_HWIN StudentPageOnCreate(void);
WM_HWIN StudentPageOnCreate(void) {
	
  GUI_WIDGET_CREATE_INFO _aDialogcreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_STUDENT_0, 0, 0, 800, 480, 0, 0x64, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_STUDENT_0, 200, 25, 450, 50, 0, 0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_STUDENT_1, 265, 390, 300, 45, 0, 0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_STUDENT_2, 120, 15, 70, 71, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_STUDENT_0, 255, 350, 300, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_STUDENT_1, 105, 272, 150, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_STUDENT_2, 105, 202, 150, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_STUDENT_3, 105, 130, 150, 30, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_STUDENT_4, 540, 175, 200, 40, 0, 0, 0 },			 //剩余时间
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_STUDENT_6, 5, 5, 30, 30, 0, 0, 0  },
  { EDIT_CreateIndirect, "EDIT", ID_EDIT_STUDENT_1, 300, 275, 170, 35, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "EDIT", ID_EDIT_STUDENT_2, 300, 205, 170, 35, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "EDIT", ID_EDIT_STUDENT_3, 300, 135, 170, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_STUDENT_0, 710, 390, 60, 53, 0, 0x0, 0 },     //老师
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_STUDENT_1, 710, 20, 60, 60, 0, 0x0, 0 },		 //设置
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_STUDENT_2, 540, 190, 70, 92, 0, 0x0, 0 },	 //开始实验
  { EDIT_CreateIndirect, "EDIT", ID_EDIT_STUDENT_4, 540, 225, 200, 40, 0, 0x0, 0 },			 //倒计时
};
	
	WM_HWIN hWin;
	hWin = GUI_CreateDialogBox(_aDialogcreate, GUI_COUNTOF(_aDialogcreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

/*************************** End of file ****************************/
