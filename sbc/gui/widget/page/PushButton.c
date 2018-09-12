#include "PushButton.h"
#include "main.h"
#include "FramewinDLG.h"
#include "app.h"

extern u8 VolumeButtonStatus;

static void _cbWifiButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmwifiText, 0, 0);
			GUI_SetAlpha(0x00);
		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmwifiText, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbVolumeButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmvoiceText, 0, 0);
			GUI_SetAlpha(0x00);
		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmvoiceText, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbStartExpButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmstartExpButton, 0, 0);
			GUI_SetAlpha(0x00);
		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmstartExpButton, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbUploadButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmuploadButton, 0, 0);
			GUI_SetAlpha(0x00);
		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmuploadButton, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbStandbyButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmstandbyText, 0, 0);
			GUI_SetAlpha(0x00);

		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmstandbyText, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbStudentButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmstudent, 0, 0);
			GUI_SetAlpha(0x00);

		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmstudent, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbTeacherButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmteacher, 0, 0);
			GUI_SetAlpha(0x00);

		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmteacher, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbSettingButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if (BUTTON_IsPressed(hButton))
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_SEL);
			GUI_Clear();
			GUI_SetAlpha(0x40);
			GUI_DrawBitmap(&bmsetting, 0, 0);
			GUI_SetAlpha(0x00);
			
		}
		else
		{
			GUI_SetBkColor(PUSHBUTTON_BKCOLOR_UNSEL);
			GUI_Clear();
			GUI_DrawBitmap(&bmsetting, 0, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbVolumeSwitchButton(WM_MESSAGE *pMsg)
{
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		if(VolumeButtonStatus == 1)
		{
			GUI_DrawBitmap(&bmswitchOn, 0, 0);
		}
		else
		{
			GUI_DrawBitmap(&bmswitchOff, 0, 0);
		}
		break;
			
	default:
		BUTTON_Callback(pMsg);
	}
}





void pushButtonInitStudentDialog(WM_HWIN hWin)
{
	WM_HWIN      hButton;

	//
	// Initialization of 'BACK'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_STUDENT_0);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbTeacherButton);
	//
	// Initialization of 'BACK'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_STUDENT_1);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbSettingButton);
	
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_STUDENT_2);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbStartExpButton);
}

void pushButtonInitTeacherDialog(WM_HWIN hWin)
{
	WM_HWIN      hButton;

	//
	// Initialization of 'BACK'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_TEACHER_1);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbStudentButton);
	//
	// Initialization of 'BACK'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_TEACHER_2);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbSettingButton);
	
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_TEACHER_0);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbUploadButton);
}

void pushButtonInitVolumeSwitchDialog(WM_HWIN hWin)
{
	WM_HWIN      hButton;

	hButton = WM_GetDialogItem(hWin, ID_BUTTON_5);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbVolumeSwitchButton);
	WM_HideWindow(hButton);
}

void pushButtonInitSettingDialog(WM_HWIN hWin)
{
	WM_HWIN      hButton;

	//
	// Initialization of 'BACK'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_0);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbStudentButton);
	//
	// Initialization of 'BACK'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_1);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbTeacherButton);
	//
	// Initialization of 'BACK'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_2);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbWifiButton);
	//
	// Initialization of 'HOMEPAGE'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_3);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbVolumeButton);
	//
	// Initialization of 'MENU'
	//
	hButton = WM_GetDialogItem(hWin, ID_BUTTON_4);
	BUTTON_SetText(hButton, "");
	WM_SetCallback(hButton, _cbStandbyButton);
}

//void backButtonMessageProcess(int NCode)
//{
//	switch (NCode)
//	{
//	case WM_NOTIFICATION_CLICKED:
//		break;
//	case WM_NOTIFICATION_RELEASED:
//		if (!TypewritingIsVisible())
//		{
//			menuBacktoPrecursor();
//		}
//		break;
//	default:
//		break;
//	}
//}

//void homepageButtonMessageProcess(int NCode)
//{
//	switch (NCode)
//	{
//	case WM_NOTIFICATION_CLICKED:
//		break;
//	case WM_NOTIFICATION_RELEASED:
//		if (!TypewritingIsVisible())
//		{
//			AddUserHideWindow();
//			SettingHideWindow();
//			UserListHideWindow();
//			CalendarHideWindow();
//			PressFingerprintHideWindow();
//			MenuHideWindow();
//			HomepageShowWindow();
//			menuSetCurrentIndex(INDEX_HOMEPAGE);
//		}
//		break;
//	default:
//		break;
//	}
//}

//void menuMessageProcess(int NCode)
//{
//	switch (NCode)
//	{
//	case WM_NOTIFICATION_CLICKED:
//		break;
//	case WM_NOTIFICATION_RELEASED:
//		if (!TypewritingIsVisible())
//		{
//			AddUserHideWindow();
//			SettingHideWindow();
//			UserListHideWindow();
//			CalendarHideWindow();
//			PressFingerprintHideWindow();
//			MenuShowWindow();
//			menuSetCurrentIndex(INDEX_MENU);
//		}
//		break;
//	default:
//		break;
//	}
//}
