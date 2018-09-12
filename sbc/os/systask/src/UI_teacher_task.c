#include "systask.h"

static WM_HWIN create(void);
static void close(void);
static void teacherwin_task(void);

UI_teacherwinInfoStructTypedef teacherwin = {
	(WM_HWIN)0,
	
	create,
	close,
	teacherwin_task
};

static WM_HWIN create(void)
{
	ui.teacherwin->hwin = TeacherPageOnCreate();
	
	return ui.teacherwin->hwin;
}

static void close()
{
	WM_HideWin(ui.teacherwin->hwin);
}

static void teacher_event(void)
{
	u8 dropDownValue = 0;
	switch(ui_state.teacherwin_state)
	{
		case STATE_TEACHER_SWITCH_TO_STUDENTWIN:
			ui.switchover(ui.teacherwin->hwin,ui.studentwin->hwin);
			ui_state.teacherwin_state = STATE_TEACHER_WAITING;
		break;
		
		case STATE_TEACHER_SWITCH_TO_SETTINGWIN:
			ui.switchover(ui.teacherwin->hwin,ui.settingwin->hwin);
			ui_state.teacherwin_state = STATE_TEACHER_WAITING;
		break;
		
		case STATE_TEACHER_START_HTTP:
			
			switch(running_state)
			{
				case STATE_RUNNING_STUDENT:
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"尚未开始实验 ");
					break;
				
				case STATE_RUNNING_TEACHER_IDENTIFY:
					
					xTaskNotify(xHandleTaskQRScanner,
								bitQRScannerOn,
								eSetBits);
					break;
				
				case STATE_RUNNING_TEACHER_MARK:
					
					if(dropDownValue)
					{
						xTaskNotify(xHandleTaskWifi,
									bitWifiHttpRequesting,
									eSetBits);
					}
					else
						TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"请对本次实验进行打分 ");
					break;
				
				default:
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"无线网络连接失败 ");
					break;
				
			}

			ui_state.teacherwin_state = STATE_TEACHER_WAITING;
		break;
		
		case STATE_TEACHER_START_MARK:
			
			dropDownValue=DROPDOWN_GetSel(WM_GetDialogItem(ui.teacherwin->hwin, ID_DROPDOWN_TEACHER_0));
		
			switch (dropDownValue)
			{
				case 0:
					studentMark[0] = '0';
					break;
				case 1 :
					studentMark[0] = 'A';
					break;
				case 2 :
					studentMark[0] = 'B';
					break;
				case 3 :
					studentMark[0] = 'C';
					break;
				case 4 :
					studentMark[0] = 'D';
					break;
				default:
					break;
			}

			ui_state.teacherwin_state = STATE_TEACHER_WAITING;
		break;
		
		case STATE_TEACHER_WAITING:
		break;
		
		default:
		break;
	}
}

static void teacherwin_task(void)
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
				IMAGE_SetBitmap(WM_GetDialogItem(ui.teacherwin->hwin, ID_IMAGE_TEACHER_6),&bmwifi);
			}
			
			if((ulValue & bitWifiConnectError) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.teacherwin->hwin, ID_IMAGE_TEACHER_6),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"无线网络连接失败 ");
			}
			
			if((ulValue & bitWifiConnecting) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.teacherwin->hwin, ID_IMAGE_TEACHER_6),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"正在连接无线网络 ");
			}
			
			if((ulValue & bitQRScannerOn) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0),"请扫描您的二维码 ");
			}
			
			if((ulValue & bitQRScannerOnError) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"二维码扫描器开启失败 ");
			}
			
			if((ulValue & bitQRScannerScanError) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"二维码识别失败 ");
			}
			
			if((ulValue & bitQRScannerScanOvertime) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"扫描超时,请重试 ");
			}
			
			if((ulValue & bitQRScannerScanRight) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"二维码识别成功 ");
				
				xTaskNotify(xHandleTaskWifi,
								bitWifiHttpRequesting,
								eSetBits);
			}
			
			if((ulValue & bitWifiHttpRequesting) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"正在连接服务器 ");
			}
			
			if((ulValue & bitWifiHttpRequestRight) != 0)
			{
				if(running_state & STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI)
				{
					running_state &= ~STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI;		//教师验证状态结束 1101 1111
					running_state |= STATE_RUNNING_TEACHER_MARK_WITHOUT_WIFI;           //进入教师打分状态
					
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"身份验证成功 ");
				}
				
				if(running_state & STATE_RUNNING_TEACHER_MARK_WITHOUT_WIFI)
				{
					running_state &= ~STATE_RUNNING_TEACHER_MARK_WITHOUT_WIFI;			//教师打分状态结束 1110 1111
					running_state |= STATE_RUNNING_STUDENT_WITHOUT_WIFI;          	    //重新进入学生状态
					
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"成绩上传成功 ");
					EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_1),"");  //姓名
					EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_2),"");  //学号
					EDIT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_EDIT_TEACHER_0),"");  //姓名
					EDIT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_EDIT_TEACHER_1),"");  //学号
					EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_3)," ");
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0)," ");
					TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0)," ");
					DROPDOWN_SetSel(WM_GetDialogItem(ui.teacherwin->hwin, ID_DROPDOWN_TEACHER_0),0);
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"本次实验到此结束 ");
					bsp_delay_ms(1000);
					WM_HideWindow(ui.teacherwin->hwin);
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0)," ");
					WM_ShowWindow(ui.studentwin->hwin);
					WM_ShowWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_BUTTON_STUDENT_2));
					WM_HideWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_4));
					WM_HideWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_4));
				}
			}
			
			if((ulValue & bitWifiHttpRequestWrong) != 0)
			{
				if(running_state & STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI)
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"身份验证失败 ");
				
				if(running_state & STATE_RUNNING_TEACHER_MARK_WITHOUT_WIFI)
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"成绩上传失败 ");
			}
			
			if((ulValue & bitWifiHttpRequestError) != 0)
			{
				if(running_state & STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI)
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"身份验证超时 ");
				
				if(running_state & STATE_RUNNING_TEACHER_MARK_WITHOUT_WIFI)
					TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"成绩上传超时 ");
			}
		}
		teacher_event();
		vTaskDelay(10);
	}
}


