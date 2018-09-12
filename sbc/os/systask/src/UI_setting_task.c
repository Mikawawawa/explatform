#include "systask.h"

static WM_HWIN create(void);
static void close(void);
static void settingwin_task(void);

UI_settingwinInfoStructTypedef settingwin = {
	(WM_HWIN)0,
	
	create,
	close,
	settingwin_task
};

static WM_HWIN create(void)
{
	ui.settingwin->hwin = SettingPageOnCreate();
	
	return ui.settingwin->hwin;
}

static void close()
{
	WM_HideWin(ui.settingwin->hwin);
}

static void setting_event(void)
{
	u8 listNum;
	u16 slideValue = 0;
	u8 VolumeString[20];

	switch(ui_state.settingwin_state)
	{
		case STATE_SETTING_SWITCH_TO_STUDENTWIN:
			ui.switchover(ui.settingwin->hwin,ui.studentwin->hwin);
			ui_state.settingwin_state = STATE_TEACHER_WAITING;
		break;
		
		case STATE_SETTING_SWITCH_TO_TEACHERWIN:
			ui.switchover(ui.settingwin->hwin,ui.teacherwin->hwin);
			ui_state.settingwin_state = STATE_TEACHER_WAITING;
		break;
		
		case STATE_SETTING_WIFI_SCAN:
			
			if(WM_IsVisible(WM_GetDialogItem(ui.settingwin->hwin,ID_BUTTON_5)))
			{
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_IMAGE_D));
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_IMAGE_E));
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_SLIDER_0));
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_BUTTON_5));
			}
			if(!WM_IsVisible(WM_GetDialogItem(ui.settingwin->hwin,ID_LISTVIEW_0)))
			{
				WM_ShowWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_LISTVIEW_0));
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0), "无线网络扫描中 ");
				
				xTaskNotify(xHandleTaskWifi,
						bitWifiScan,
						eSetBits);
			}
			else
			{
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_LISTVIEW_0));
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0), " ");
			}
			
			ui_state.settingwin_state = STATE_SETTING_WAITING;
			
		break;
		
		case STATE_SETTING_WIFI_CONNECT:
			
			listNum=LISTVIEW_GetSel(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0));
			TEXT_SetFont(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_TEXT_WIFI_1), GUI_FONT_20B_ASCII);
			TEXT_SetFont(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_TEXT_WIFI_3), GUI_FONT_20B_ASCII);
			EDIT_SetFont(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_EDIT_WIFI_0), GUI_FONT_20_ASCII);
			TEXT_SetText(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_TEXT_WIFI_1), (const char *)&Wifi_List[listNum][1]);
		
			NowData.WifiSSID = &Wifi_List[listNum][1];		//获取点击的WIFI名称
			memset(gui.keyboard->content,0,50);
			gui.keyboard->content_index = gui.keyboard->content;
			switch(Wifi_List[listNum][0])
			{
				case '0' : 
					TEXT_SetText(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_TEXT_WIFI_3), "NONE");
					WM_HideWindow(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_EDIT_WIFI_0));
				
					NowData.WifiPassword = "NONE";				//无WIFI密码	
				break;
				
				case '1' : 
					if(!WM_IsVisible(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_EDIT_WIFI_0)))
						WM_ShowWindow(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_EDIT_WIFI_0));
					TEXT_SetText(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_TEXT_WIFI_3), "LOCKED");
				break;

					default:   
					break;
				}
				WM_BringToTop(ui.wifi_connectwin->hwin);
				WM_ShowWindow(ui.wifi_connectwin->hwin);
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0));
				
				ui_state.settingwin_state = STATE_SETTING_WAITING;
		break;
				
		case STATE_SETTING_VOICE_SETTING:
			
			if(WM_IsVisible(WM_GetDialogItem(ui.settingwin->hwin,ID_LISTVIEW_0)))
			{
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_LISTVIEW_0));
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_TEXT_0));
			}
			if(!WM_IsVisible(WM_GetDialogItem(ui.settingwin->hwin,ID_BUTTON_5)))
			{
				WM_ShowWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_IMAGE_D));
				WM_ShowWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_IMAGE_E));
				WM_ShowWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_SLIDER_0));
				WM_ShowWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_BUTTON_5));
			}
			else
			{
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_IMAGE_D));
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_IMAGE_E));
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_SLIDER_0));
				WM_HideWindow(WM_GetDialogItem(ui.settingwin->hwin,ID_BUTTON_5));
			}
			
			ui_state.settingwin_state = STATE_SETTING_WAITING;
		break;
		
		case STATE_SETTING_VOICE_VOLUME:
			
			slideValue = SLIDER_GetValue(WM_GetDialogItem(ui.settingwin->hwin, ID_SLIDER_0));
			NowData.VolumeLevel = slideValue/10;
			sprintf((char*)VolumeString,"[v%c]",NowData.VolumeLevel+'0');
			voiceDispString(VolumeString);
		
			if(WM_IsVisible(WM_GetDialogItem(ui.settingwin->hwin, ID_SLIDER_0)))	
			{
				voiceDispString("sound102");
			}
			
			ui_state.settingwin_state = STATE_SETTING_WAITING;
		break;
		
		case STATE_SETTING_STANDBY:
			
			if( app_state.standby_state != STATE_STANDBY_ON) 
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_0);
				app_state.standby_state = STATE_STANDBY_ON;
				vTaskSuspend(xHandleTaskMain);
				vTaskSuspend(xHandleTaskSettingwin);
				vTaskSuspend(xHandleTaskStudentwin);
				vTaskSuspend(xHandleTaskTeacherwin);
				vTaskSuspend(xHandleTaskWifiConnectwin);
				vTaskSuspend(xHandleTaskWifi);
				vTaskSuspend(xHandleTaskQRScanner);
				
				timer6_notify.touch_resume_per_sec = 0;	
			}
			
			ui_state.settingwin_state = STATE_SETTING_WAITING;
		break;
		
		case STATE_SETTING_ENTER_PRIV:
			
			xTaskNotify(xHandleTaskQRScanner,
								bitQRScannerOn,
								eSetBits);
		
			ui_state.settingwin_state = STATE_SETTING_WAITING;
		break;
			
		case STATE_SETTING_WAITING:
			if(WM_IsVisible(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_EDIT_WIFI_0)))	
			{
				EDIT_SetText(WM_GetDialogItem(ui.wifi_connectwin->hwin, ID_EDIT_WIFI_0),(const char *)gui.keyboard->content);
				NowData.WifiPassword = gui.keyboard->content;
			}
		break;
		
		default:
		break;
	}
}

static void settingwin_task(void)
{
	u8 i;
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
			if((ulValue & bitWifiScan) != 0)
			{
				for(i=0; i<13 && Wifi_List[i][0]; i++)
				{
					LISTVIEW_SetItemText(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0), 0, i, (const char *)&(Wifi_List[i][1]));
					switch(Wifi_List[i][0])
					{
						case '0' : 
							LISTVIEW_SetItemText(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0), 1, i, "PUBIC"); 	
							LISTVIEW_SetItemText(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0), 2, i, "OPEN"); 				
						break;
						
						case '1' : 
							LISTVIEW_SetItemText(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0), 1, i, "PRIVATE");	
							LISTVIEW_SetItemText(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0), 2, i, "LOCKED"); 			
						break;
						
						default:   
						break;
					}
				}
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0), "无线网络扫描完毕 ");
			}
			
			if((ulValue & bitWifiConnected) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.settingwin->hwin, ID_IMAGE_B),&bmwifi);
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0), "无线网络连接成功 ");
			}
			
			if((ulValue & bitWifiConnectError) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.settingwin->hwin, ID_IMAGE_B),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0), "无线网络连接超时 ");
			}
			
			if((ulValue & bitWifiConnecting) != 0)
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.settingwin->hwin, ID_IMAGE_B),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0), "正在连接无线网络 ");
			}
			
			if((ulValue & bitQRScannerOn) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0),"请扫描您的二维码 ");
			}
			
			if((ulValue & bitQRScannerOnError) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0),"二维码扫描器开启失败 ");
			}
			
			if((ulValue & bitQRScannerScanError) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0),"二维码识别失败 ");
			}
			
			if((ulValue & bitQRScannerScanOvertime) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0),"扫描超时,请重试 ");
			}
			
			if((ulValue & bitQRScannerScanRight) != 0)
			{
				TEXT_SetText(WM_GetDialogItem(ui.settingwin->hwin, ID_TEXT_0),"二维码识别成功 ");
				
				xTaskNotify(xHandleTaskWifi,
								bitWifiHttpRequesting,
								eSetBits);
			}
			
		}
		setting_event();
		vTaskDelay(10);
	}
}

//static void privliged_event(void)
//{
//	
//}


