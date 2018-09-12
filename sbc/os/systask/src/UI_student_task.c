#include "systask.h"

extern TaskHandle_t xHandleTaskStudentwin;

static WM_HWIN create(void);
static void close(void);
static void studentwin_task(void);

UI_studentwinInfoStructTypedef studentwin = {
	(WM_HWIN)0,
	
	create,
	close,
	studentwin_task
};

static WM_HWIN create(void)
{
	ui.studentwin->hwin = StudentPageOnCreate();
	
	return ui.studentwin->hwin;
}

static void close()
{
	WM_HideWin(ui.studentwin->hwin);
}

static void student_event(void)
{
	switch(ui_state.studentwin_state)
	{
		case STATE_STUDENT_SWITCH_TO_TEACHERWIN:
			ui.switchover(ui.studentwin->hwin,ui.teacherwin->hwin);
			ui_state.studentwin_state = STATE_STUDENT_WAITING;
		break;
		
		case STATE_STUDENT_SWITCH_TO_SETTINGWIN:
			ui.switchover(ui.studentwin->hwin,ui.settingwin->hwin);
			ui_state.studentwin_state = STATE_STUDENT_WAITING;
		break;
		
		case STATE_STUDENT_START_EXPERIMENT:
			
			if(running_state & STATE_RUNNING_STUDENT_WITHOUT_WIFI)
				xTaskNotify(xHandleTaskQRScanner,
							bitQRScannerOn,
							eSetBits);
			else
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"当前实验尚未结束 ");

			ui_state.studentwin_state = STATE_STUDENT_WAITING;
		break;
		
		case STATE_STUDENT_WAITING:
		break;
		
		default:
		break;
	}
}

static void studentwin_task(void)
{
	BaseType_t xResult;
	uint32_t ulValue;
	while(1)
	{
		xResult = xTaskNotifyWait(	(uint32_t)0x00,		
									(uint32_t)0xffffffffUL,
									&ulValue,
									(TickType_t)0	);
		
		if(xResult == pdPASS)
		{
			if((ulValue & bitWifiConnected) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.studentwin->hwin, ID_IMAGE_STUDENT_6),&bmwifi);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"无线网络连接成功 ");
			}
			
			if((ulValue & bitWifiConnectError) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.studentwin->hwin, ID_IMAGE_STUDENT_6),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"无线网络连接失败 ");
			}
			
			if((ulValue & bitWifiConnecting) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.studentwin->hwin, ID_IMAGE_STUDENT_6),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"正在连接无线网络 ");
			}
			
			if((ulValue & bitQRScannerOn) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"请扫描您的二维码 ");
			}
			
			if((ulValue & bitQRScannerOnError) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"二维码扫描器开启失败 ");
			}
			
			if((ulValue & bitQRScannerScanError) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"二维码识别失败 ");
			}
			
			if((ulValue & bitQRScannerScanOvertime) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"扫描超时,请重试 ");
			}
			
			if((ulValue & bitQRScannerScanRight) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"二维码识别成功 ");
				
				xTaskNotify(xHandleTaskWifi,
							bitWifiHttpRequesting,
							eSetBits);
			}
			
			if((ulValue & bitWifiHttpRequesting) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"正在连接服务器 ");
			}
			
			if((ulValue & bitWifiHttpRequestRight) != 0)
			{
				running_state &= ~STATE_RUNNING_STUDENT_WITHOUT_WIFI;					//学生状态结束 1011 1111
				running_state |= STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI;			//进入教师验证状态
				
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"签到成功 ");
				
				WM_HideWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_BUTTON_STUDENT_2));
				WM_ShowWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_4));
				WM_ShowWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_4));
				
				timer6_notify.count_down_per_sec = 0;
				TIM_SetCounter(TIM6,0);
			}
			
			if((ulValue & bitWifiHttpRequestWrong) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"签到失败 ");
			}
			
			if((ulValue & bitWifiHttpRequestError) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"签到上传超时 ");
			}
		}
		student_event();
		vTaskDelay(10);
	}
}


