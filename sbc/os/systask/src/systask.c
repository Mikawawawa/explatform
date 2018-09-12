#include "systask.h"

TaskHandle_t xHandleTaskMain;
TaskHandle_t xHandleTaskWifi;
TaskHandle_t xHandleTaskSettingwin;
TaskHandle_t xHandleTaskQRScanner;
TaskHandle_t xHandleTaskStudentwin;
TaskHandle_t xHandleTaskTeacherwin;
TaskHandle_t xHandleTaskWifiConnectwin;
TaskHandle_t xHandleTaskTimer;
TaskHandle_t xHandleTaskConsole;
TaskHandle_t xHandleTaskInit;

static void init0(void);
static void touch_task(void);
static void wifi_task(void);
static void scanner_task(void);
static void timer_task(void);
static void console_task(void);
static void init_task(void);

u8 studentMark[2];		 //学生成绩
u8 studentIDNum[30];     //学生ID
u8 teacherIDNum[30]; 	 //教师ID

RUNNING_STATE running_state = STATE_RUNNING_STUDENT_WITHOUT_WIFI;			//running_state初始化为学生状态

app_state_type_struct app_state = {
	
	STATE_VOICE_ON,
	STATE_STANDBY_OFF,
	{STATE_QR_SCANNER_WAIT,
	STATE_QR_SCANNER_WAIT},
	{STATE_WIFI_WAIT,
	STATE_WIFI_WAIT},
	
};

ui_state_type_struct ui_state = {
	
	0,
	0,
	0,
	0
};

system_struct_type os = {
	init0
	
};


static void init0()
{
	gui.init();

							
	xTaskcreate(	(TaskFunction_t)init_task, 
							(const char *)"TASK_INIT", 
							256, 
							NULL, 
							tskIDLE_PRIORITY + 9, 
							&xHandleTaskInit);
							
	xTaskcreate(	(TaskFunction_t)console_task, 
							(const char *)"TASK_CONSOLE", 
							512, 
							NULL, 
							tskIDLE_PRIORITY + 8, 
							&xHandleTaskConsole);
							
	vTaskStartScheduler();
								
}

static void init_task()
{
	BaseType_t xResult;
	uint32_t ulValue;
	u8 volumeLevel = 5;
	u8 volumeString[20];
	u8 font_detect_buffer[10];
	
	while(1)
	{
		xResult = xTaskNotifyWait(	(uint32_t)0x00,		
									(uint32_t)0xffffffffUL,
									&ulValue,
									(TickType_t)portMAX_DELAY	);
		
		if(xResult == pdPASS)
		{
			if((ulValue & bitFlashReadID) != 0)
			{
				if(SPI_FLASH_ReadID() == sFLASH_ID)
					ulValue |= 0x80000000;
				else
					ulValue &= ~(0x80000000);
				
				xTaskNotify(xHandleTaskConsole,
							ulValue,
							eSetValueWithOverwrite);
			}
			
			if((ulValue & bitFlashReadFont) != 0)
			{
				SPI_FLASH_BufferRead(font_detect_buffer, 0, 10);
				if(strstr((const char *)font_detect_buffer, "GUIX"))
					ulValue |= 0x80000000;
				else
					ulValue &= ~(0x80000000);
				
				xTaskNotify(xHandleTaskConsole,
							ulValue,
							eSetValueWithOverwrite);
					
			}
			
			if((ulValue & bitWifiInit) != 0)
			{
				if(usr_c322_init())
					ulValue |= 0x80000000;
				else
					ulValue &= ~(0x80000000);
				
				xTaskNotify(xHandleTaskConsole,
							ulValue,
							eSetValueWithOverwrite);
				
			}
			
			if((ulValue & bitFatfsInit) != 0)
			{
				if(local_db.init())
					ulValue |= 0x80000000;
				else
					ulValue &= ~(0x80000000);
				
				xTaskNotify(xHandleTaskConsole,
							ulValue,
							eSetValueWithOverwrite);
			}
			
			if((ulValue & bitVoiceInit) != 0)
			{
				sprintf((char *)volumeString,"[v%c][m3][s6]",volumeLevel+'0');
				
				if(voiceDispString(volumeString))
					ulValue |= 0x80000000;
				else
					ulValue &= ~(0x80000000);
				
				xTaskNotify(xHandleTaskConsole,
							ulValue,
							eSetValueWithOverwrite);
			}
			
			if((ulValue & bitCompeletlyInit) != 0)
			{
				xTaskNotify(xHandleTaskConsole,
							ulValue,
							eSetValueWithOverwrite);
				break;
			}
			
		}
		vTaskDelay(10);
	}
	
	xTaskcreate(	(TaskFunction_t)ui.wifi_connectwin->task, 
							(const char *)"TASK_WIFI_CONNECTWIN", 
							256, 
							NULL, 
							tskIDLE_PRIORITY + 6, 
							&xHandleTaskWifiConnectwin);

	xTaskcreate(	(TaskFunction_t)ui.teacherwin->task, 
								(const char *)"TASK_TEACHERWIN", 
								512, 
								NULL, 
								tskIDLE_PRIORITY + 6, 
								&xHandleTaskTeacherwin);
	
	xTaskcreate(	(TaskFunction_t)ui.studentwin->task, 
								(const char *)"TASK_STUDENTWIN", 
								512, 
								NULL, 
								tskIDLE_PRIORITY + 6, 
								&xHandleTaskStudentwin);
	
	xTaskcreate(	(TaskFunction_t)ui.settingwin->task, 
								(const char *)"TASK_SETTINGWIN", 
								512, 
								NULL, 
								tskIDLE_PRIORITY + 6, 
								&xHandleTaskSettingwin);
	
	xTaskcreate(	(TaskFunction_t)wifi_task, 
								(const char *)"TASK_WIFI", 
								512, 
								NULL, 
								tskIDLE_PRIORITY + 5, 
								&xHandleTaskWifi);
								
	xTaskcreate(	(TaskFunction_t)scanner_task, 
								(const char *)"TASK_QR_SCANNER", 
								256, 
								NULL, 
								tskIDLE_PRIORITY + 5, 
								&xHandleTaskQRScanner);
								
	xTaskcreate(	(TaskFunction_t)MainTask, 
								(const char *)"TASK_EMWIN", 
								1024, 
								NULL, 
								tskIDLE_PRIORITY + 6, 
								&xHandleTaskMain);
								
	xTaskcreate(	(TaskFunction_t)touch_task, 
								(const char *)"TASK_TOUCH", 
								256, 
								NULL, 
								tskIDLE_PRIORITY + 7, 
								NULL);
								
						
	xTaskcreate(	(TaskFunction_t)timer_task, 
							(const char *)"TASK_TIMER", 
							256, 
							NULL, 
							tskIDLE_PRIORITY + 7, 
							&xHandleTaskTimer);
							
							
	vTaskDelete(NULL);						
							
}

static void console_task()
{
	BaseType_t xResult;
	uint32_t ulValue;
	
	u8 wifi_connect_count = 0;
	
	vTaskSuspendAll();
	
	bsp_delay_ms(500);
	bsp_delay_ms(500);
	xTaskResumeAll();
	
	xTaskNotify(xHandleTaskInit,
					bitFlashReadID,
					eSetValueWithOverwrite);
	while(1)
	{
		
		
		xResult = xTaskNotifyWait(	(uint32_t)0x00,		
									(uint32_t)0xffffffffUL,
									&ulValue,
									(TickType_t)portMAX_DELAY	);
		
		if(xResult == pdPASS)
		{
			if((ulValue & bitFlashReadID) != 0)
			{
				if(ulValue & 0x80000000)
				{
					console.write_line("> NAND flash detected.");
					vTaskDelay(500);
					xTaskNotify(xHandleTaskInit,
								bitFlashReadFont,
								eSetValueWithOverwrite);
				}
				
				else
					console.write_line("> NAND flash not detected.");
			}
			
			if((ulValue & bitFlashReadFont) != 0)
			{
				if(ulValue & 0x80000000)
				{
					console.write_line("> extern font detected.");
					vTaskDelay(500);
					xTaskNotify(xHandleTaskInit,
								bitVoiceInit,
								eSetValueWithOverwrite);
				}
				
				else
					console.write_line("> extern font not detected.");
			}
			
			if((ulValue & bitVoiceInit) != 0)
			{
				if(ulValue & 0x80000000)
				{
					console.write_line("> xfs5152ce detected.");
					vTaskDelay(500);
					xTaskNotify(xHandleTaskInit,
								bitWifiInit,
								eSetValueWithOverwrite);
				}
				else
					console.write_line("> xfs5152ce not detected.");
			}
			
			if((ulValue & bitWifiInit) != 0)
			{
				if(ulValue & 0x80000000)
				{
					
					console.write("> wifi detected, hardware MAC : ");
					console.write_line((const char *)macAddress);
					console.write("> wifi connecting...");
					while(wifi_connect_count <= 10)
					{
						if(0 == Nlink)
						{
							console.write_line("");
							console.write_line("> wifi connected.");
							break;
						}
						
						else
							console.write(".");
						
						vTaskDelay(1000);
						
						wifi_connect_count ++;
					}
					
					if(10 <= wifi_connect_count)
					{
						console.write_line("");
						console.write_line("> wifi disconnected.");
					}
					
					
					vTaskDelay(500);
					
					xTaskNotify(xHandleTaskInit,
							bitFatfsInit,
							eSetValueWithOverwrite);
					
					console.write_line("> init local database.");
							
				}
				else
					console.write_line("> wifi not detected.");
			}
			
				
			
			if((ulValue & bitFatfsInit) != 0)
			{
				if(ulValue & 0x80000000)
				{
					console.write("> local database inited : ");
					switch(local_db.info) {
						case fs_new : console.write_line("> new file system.");break;
						case fs_exist : console.write_line("> existed file system.");break;
						default :break;
					}
					vTaskDelay(1000);
					console.write_line("> welcome. ");
					vTaskDelay(1000);
					xTaskNotify(xHandleTaskInit,
								bitCompeletlyInit,
								eSetValueWithOverwrite);
				}
				else {
					console.write("> local database not inited : ");
					switch(local_db.info) {
						case fs_not_exist : console.write_line("> file system not exist.");break;
						case fs_crashed : console.write_line("> file system crashed.");break;
						default :break;
					}
				}	
			}
			
			if((ulValue & bitCompeletlyInit) != 0)
			{
				
				vTaskSuspend(xHandleTaskConsole);
			}
			
			
		}
		vTaskDelay(10);
	}
}

static void timer_task()
{
	static u16 exp_time = 2400;
	static u8 touch_state = 0;
	char exp_time_str[20];
	
	 
	while(1)
	{
		
		if(touch.status && touch_state == 0 && app_state.standby_state == STATE_STANDBY_ON)
		{
			touch_state = 1;
		}
		if(!touch.status  && touch_state == 1)
		{
			touch_state = 2;
		}
		
		if(touch.status  && touch_state == 2)
		{
			touch_state = 3;
		}
		
		if(!touch.status  && touch_state == 3)
		{
			touch_state = 0;
			app_state.standby_state = STATE_STANDBY_OFF;
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			vTaskResume(xHandleTaskMain);
			vTaskResume(xHandleTaskWifi);
			vTaskResume(xHandleTaskQRScanner);
			vTaskResume(xHandleTaskSettingwin);
			vTaskResume(xHandleTaskStudentwin);
			vTaskResume(xHandleTaskTeacherwin);
			vTaskResume(xHandleTaskWifiConnectwin);
		}
		
		if(20 <= timer6_notify.touch_resume_per_sec)
		{
			timer6_notify.touch_resume_per_sec = 0;
			if(app_state.standby_state == STATE_STANDBY_ON)
			{
				touch_state = 0;
			}
		}
		
		if(20 == timer6_notify.count_down_per_sec)
		{
			timer6_notify.count_down_per_sec = 0;
			exp_time --;
			sprintf(exp_time_str,"%d时%d分%d秒 ",exp_time / 3600, exp_time / 60, exp_time % 60);
			EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_4),exp_time_str);
		}
		vTaskDelay(10);
	}
}


static void touch_task()
{
	while(1) {
		touch.scan();
		vTaskDelay(20);
	}
}

static void wifi_task()
{
	char a[50];
//	u8 roomNum[]="202";
	u8 tabNum[]="001";
	u8 i,j,res,status = 0;
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
				app_state.wifi_state.next_state = STATE_WIFI_SCAN;
			}
			
			if((ulValue & bitWifiConnecting) != 0)
			{
				app_state.wifi_state.next_state = STATE_WIFI_CONNECTING;
			}
			
			if((ulValue & bitWifiHttpRequesting) != 0)
			{
				app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUESTING;
			}
		}
		
		switch(app_state.wifi_state.next_state)
		{
			case STATE_WIFI_SCAN:
				
				usr_c322_quit_trans();	
				usr_c322_send_cmd("AT+WSCAN\r\n","+OK",1000);
			
				for(i=0; i<13; i++)						//初始化WIFI列表
				{
					for(j=0; j<20; j++)
						Wifi_List[i][j] = 0;
				}
				usr_c322_wifista_parse();		
				
				xTaskNotify(xHandleTaskSettingwin,
							bitWifiScan,
							eSetBits);
				
				app_state.wifi_state.current_state = STATE_WIFI_SCAN;
				app_state.wifi_state.next_state = STATE_WIFI_WAIT;
				break;
				
			case STATE_WIFI_CONNECTING:
				
				xTaskNotify(xHandleTaskSettingwin,
							bitWifiConnecting,
							eSetBits);
			
				xTaskNotify(xHandleTaskStudentwin,
							bitWifiConnecting,
							eSetBits);
			
				xTaskNotify(xHandleTaskTeacherwin,
							bitWifiConnecting,
							eSetBits);
			
				res = usr_c322_wifista_connect(NowData.WifiSSID,NowData.WifiPassword);
				if(res)
				{
					app_state.wifi_state.current_state = STATE_WIFI_CONNECTING;
					app_state.wifi_state.next_state = STATE_WIFI_CONNECTED;
				}
				else
				{
					app_state.wifi_state.current_state = STATE_WIFI_CONNECTING;
					app_state.wifi_state.next_state = STATE_WIFI_ERROR_COUNTING;
				}
				break;
				
			case STATE_WIFI_CONNECTED:
				
				i = 0;
				running_state |= STATE_RUNNING_WIFI_CONNECTED;
			
				xTaskNotify(xHandleTaskSettingwin,
							bitWifiConnected,
							eSetBits);
			
				xTaskNotify(xHandleTaskStudentwin,
							bitWifiConnected,
							eSetBits);
			
				xTaskNotify(xHandleTaskTeacherwin,
							bitWifiConnected,
							eSetBits);
			
				app_state.wifi_state.current_state = STATE_WIFI_CONNECTED;
				app_state.wifi_state.next_state = STATE_WIFI_WAIT;
				break;
			
			case STATE_WIFI_CONNECT_ERROR:
				
				running_state &= ~STATE_RUNNING_WIFI_CONNECTED;
				
				xTaskNotify(xHandleTaskSettingwin,
							bitWifiConnectError,
							eSetBits);
			
				xTaskNotify(xHandleTaskStudentwin,
							bitWifiConnectError,
							eSetBits);
			
				xTaskNotify(xHandleTaskTeacherwin,
							bitWifiConnectError,
							eSetBits);
			
				app_state.wifi_state.current_state = STATE_WIFI_CONNECT_ERROR;
				app_state.wifi_state.next_state = STATE_WIFI_WAIT;
				break;
			
			case STATE_WIFI_HTTP_REQUESTING:
				switch(running_state)
				{		
					case STATE_RUNNING_STUDENT:
						
						xTaskNotify(xHandleTaskStudentwin,
									bitWifiHttpRequesting,
									eSetBits);
						
						sprintf(a,"table=%s&sid=%s&mac=%s",tabNum,studentIDNum,macAddress);
						status = usr_c322_wifista_HTTP_request("student_check",(u8*)a);
						if(status == 1)
						{
							app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
							app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_RIGHT;
						}
						else if(status == 2)
						{
							app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
							app_state.wifi_state.next_state = STATE_WIFI_ERROR_COUNTING;
						}
						else
						{
							app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
							app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_WRONG;
						}
						
						break;
					
					case STATE_RUNNING_TEACHER_IDENTIFY:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiHttpRequesting,
									eSetBits);
					
						sprintf(a,"tid=%s",teacherIDNum);
						status = usr_c322_wifista_HTTP_request("teacher_check",(u8*)a);
						if(status == 1)
						{
							app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
							app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_RIGHT;
						}
						else if(status == 2)
						{
							app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
							app_state.wifi_state.next_state = STATE_WIFI_ERROR_COUNTING;
						}
						else
						{
							app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
							app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_WRONG;
						}
						break;
					
					case STATE_RUNNING_TEACHER_MARK:
						
							xTaskNotify(xHandleTaskTeacherwin,
										bitWifiHttpRequesting,
										eSetBits);
							
							sprintf(a,"sid=%s&marks=%s",studentIDNum,studentMark);
							status=usr_c322_wifista_HTTP_request("marks_upload",(u8*)a);
							if(status == 1)
							{
								app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
								app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_RIGHT;
							}
							else if(status == 2)
							{
								app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
								app_state.wifi_state.next_state = STATE_WIFI_ERROR_COUNTING;
							}
							else
							{
								app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
								app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_WRONG;
							}
						break;
							
					case STATE_RUNNING_PRIVILIGED:
						
						xTaskNotify(xHandleTaskSettingwin,
										bitWifiHttpRequesting,
										eSetBits);
							
//							sprintf(a,"sid=%s&marks=%s",studentIDNum,studentMark);
//							status=usr_c322_wifista_HTTP_request("marks_upload",(u8*)a);
							if(status == 1)
							{
								app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
								app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_RIGHT;
							}
							else if(status == 2)
							{
								app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
								app_state.wifi_state.next_state = STATE_WIFI_ERROR_COUNTING;
							}
							else
							{
								app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUESTING;
								app_state.wifi_state.next_state = STATE_WIFI_HTTP_REQUEST_WRONG;
							}
						break;
					
					default:
						break;
				}
				break;
			
			case STATE_WIFI_HTTP_REQUEST_RIGHT:
				
				i = 0;
				switch(running_state)
				{
					case STATE_RUNNING_STUDENT:
					
						xTaskNotify(xHandleTaskStudentwin,
									bitWifiHttpRequestRight,
									eSetBits);
					
						voiceDispString(voiceSignInSuccess);
						break;
					
					case STATE_RUNNING_TEACHER_IDENTIFY:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiHttpRequestRight,
									eSetBits);
					
						voiceDispString(voiceIdentifySuccess);
						break;
					
					case STATE_RUNNING_TEACHER_MARK:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiHttpRequestRight,
									eSetBits);
					
						voiceDispString(voiceEndExp);
						break;
					
					case STATE_RUNNING_PRIVILIGED:
						
						xTaskNotify(xHandleTaskSettingwin,
									bitWifiHttpRequestRight,
									eSetBits);
					
//						voiceDispString(voiceEndExp);
						break;
					
					default:
						break;
				}
			
				app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUEST_RIGHT;
				app_state.wifi_state.next_state = STATE_WIFI_WAIT;
				break;
				
			case STATE_WIFI_HTTP_REQUEST_WRONG:
				
				i = 0;
				switch(running_state)
				{
					case STATE_RUNNING_STUDENT:
						
						xTaskNotify(xHandleTaskStudentwin,
									bitWifiHttpRequestWrong,
									eSetBits);
					
						voiceDispString(voiceSignInFail);
						break;
					
					case STATE_RUNNING_TEACHER_IDENTIFY:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiHttpRequestWrong,
									eSetBits);
					
						voiceDispString(voiceIdentifyFail);
						break;
					
					case STATE_RUNNING_TEACHER_MARK:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiHttpRequestWrong,
									eSetBits);
					
						voiceDispString(voiceMarkLoadFail);
						break;
					
					case STATE_RUNNING_PRIVILIGED:
						
						xTaskNotify(xHandleTaskSettingwin,
									bitWifiHttpRequestWrong,
									eSetBits);
					
//						voiceDispString(voiceMarkLoadFail);
						break;
					
					default:
						break;
				}
			
				app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUEST_WRONG;
				app_state.wifi_state.next_state = STATE_WIFI_WAIT;
				break;
			
			case STATE_WIFI_HTTP_REQUEST_ERROR:
			
				switch(running_state)
				{
					case STATE_RUNNING_STUDENT:
						
						xTaskNotify(xHandleTaskStudentwin,
									bitWifiHttpRequestError,
									eSetBits);
					
						voiceDispString(voiceSignInOverTime);
						break;
					
					case STATE_RUNNING_TEACHER_IDENTIFY:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiHttpRequestError,
									eSetBits);
					
						voiceDispString(voiceIdentifyOverTime);
						break;
					
					case STATE_RUNNING_TEACHER_MARK:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiHttpRequestError,
									eSetBits);
					
						voiceDispString(voiceMarkLoadOverTime);
						break;
					
					case STATE_RUNNING_PRIVILIGED:
						
						xTaskNotify(xHandleTaskSettingwin,
									bitWifiHttpRequestError,
									eSetBits);
					
//						voiceDispString(voiceMarkLoadOverTime);
						break;
					
					default:
						break;
				}
			
				app_state.wifi_state.current_state = STATE_WIFI_HTTP_REQUEST_ERROR;
				app_state.wifi_state.next_state = STATE_WIFI_WAIT;
				break;
				
			case STATE_WIFI_ERROR_COUNTING:
				
				app_state.wifi_state.next_state = app_state.wifi_state.current_state;
				i ++;
				if(i > 5)															//重发五次
				{
					app_state.wifi_state.current_state = STATE_WIFI_ERROR_COUNTING;
					app_state.wifi_state.next_state |= 0x80;						//标记错误
					i = 0;
				}
				break;
			
			case STATE_WIFI_WAIT:                                
				if(1 == Nlink && running_state & STATE_RUNNING_WIFI_CONNECTED)				 //检测WIFI状态
				{
					app_state.wifi_state.next_state = STATE_WIFI_CONNECT_ERROR;
				}
				if(0 == Nlink && !(running_state & STATE_RUNNING_WIFI_CONNECTED))
				{
					app_state.wifi_state.next_state = STATE_WIFI_CONNECTED;
				}
				break;
			
			default:
				break;
		}
		vTaskDelay(20);
	}
}

static void scanner_task()
{
	u8 i,res;
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
			if((ulValue & bitQRScannerOn) != 0)
			{
				app_state.scanner_state.next_state = STATE_QR_SCANNER_ON;
			}
		}
		
		switch(app_state.scanner_state.next_state)
		{
			case STATE_QR_SCANNER_ON:
				
				switch(running_state)		
				{
					case STATE_RUNNING_STUDENT_WITHOUT_WIFI:
						
						xTaskNotify(xHandleTaskStudentwin,
									bitWifiConnectError,
									eSetBits);
					
						app_state.scanner_state.current_state = STATE_QR_SCANNER_ON;
						app_state.scanner_state.next_state = STATE_QR_SCANNER_WAIT;
						break;
					
					case STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI:
						
						xTaskNotify(xHandleTaskTeacherwin,
									bitWifiConnectError,
									eSetBits);
					
						app_state.scanner_state.current_state = STATE_QR_SCANNER_ON;
						app_state.scanner_state.next_state = STATE_QR_SCANNER_WAIT;
						break;
					
					case STATE_RUNNING_PRIVILIGED_WITHOUT_WIFI:
						
						xTaskNotify(xHandleTaskSettingwin,
									bitWifiConnectError,
									eSetBits);
					
						app_state.scanner_state.current_state = STATE_QR_SCANNER_ON;
						app_state.scanner_state.next_state = STATE_QR_SCANNER_WAIT;
						break;
					
					default:
						if(QR_On())
						{
							app_state.scanner_state.current_state = STATE_QR_SCANNER_ON;
							app_state.scanner_state.next_state = STATE_QR_SCANNER_ERROR_COUNTING;
						}
						else
						{
							switch(running_state)
							{
								case STATE_RUNNING_STUDENT:
									
									xTaskNotify(xHandleTaskStudentwin,
												bitQRScannerOn,
												eSetBits);
								break;
								
								case STATE_RUNNING_TEACHER_IDENTIFY:
									
									xTaskNotify(xHandleTaskTeacherwin,
												bitQRScannerOn,
												eSetBits);
								break;
								
								case STATE_RUNNING_PRIVILIGED:
									
									xTaskNotify(xHandleTaskSettingwin,
												bitQRScannerOn,
												eSetBits);
								break;
								
								default:
								break;
							}
							
							app_state.scanner_state.current_state = STATE_QR_SCANNER_ON;
							app_state.scanner_state.next_state = STATE_QR_SCANNER_SCANNING;
						}
						break;
				}
				break;
			
			case STATE_QR_SCANNER_SCANNING:
				
				i = 0;
				voiceDispString(voiceShowQrCode);
				switch(running_state)
				{
					case STATE_RUNNING_STUDENT:
						
						memset(studentIDNum,0,sizeof(studentIDNum));
						res = QR_RX_Data(studentIDNum,"sid");
						switch(res)
						{
							case 0x00:									//扫描失败
								
								xTaskNotify(xHandleTaskStudentwin,
											bitQRScannerScanError,
											eSetBits);
							break;
							
							case 0x01:									//扫描成功
								
								xTaskNotify(xHandleTaskStudentwin,
											bitQRScannerScanRight,
											eSetBits);
								
								voiceDispString("sound120");
							break;
							
							case 0xff:									//扫描超时
								
								xTaskNotify(xHandleTaskStudentwin,
											bitQRScannerScanOvertime,
											eSetBits);
							break;
							
							default:
							break;
						}
						break;
						
						case STATE_RUNNING_TEACHER_IDENTIFY:
							
							memset(teacherIDNum,0,sizeof(teacherIDNum));
							res = QR_RX_Data(teacherIDNum,"tid");
							switch(res)
							{
								case 0x00:									//扫描失败
									
									xTaskNotify(xHandleTaskTeacherwin,
												bitQRScannerScanError,
												eSetBits);
								break;
								
								case 0x01:									//扫描成功
									
									xTaskNotify(xHandleTaskTeacherwin,
												bitQRScannerScanRight,
												eSetBits);
								
									voiceDispString("sound102");
								break;
								
								case 0xff:									//扫描超时
									
									xTaskNotify(xHandleTaskTeacherwin,
												bitQRScannerScanOvertime,
												eSetBits);
								break;
								
								default:
								break;
							}
							break;
							
						case STATE_RUNNING_PRIVILIGED:
							
//							memset(teacherIDNum,0,sizeof(teacherIDNum));
//							res = QR_RX_Data(teacherIDNum,"tid");
							switch(res)
							{
								case 0x00:									//扫描失败
									
									xTaskNotify(xHandleTaskSettingwin,
												bitQRScannerScanError,
												eSetBits);
								break;
								
								case 0x01:									//扫描成功
									
									xTaskNotify(xHandleTaskSettingwin,
												bitQRScannerScanRight,
												eSetBits);
								
									voiceDispString("sound102");
								break;
								
								case 0xff:									//扫描超时
									
									xTaskNotify(xHandleTaskSettingwin,
												bitQRScannerScanOvertime,
												eSetBits);
								break;
								
								default:
								break;
							}
							break;
						
						default:
							break;
				}
				app_state.scanner_state.current_state = STATE_QR_SCANNER_SCANNING;
				app_state.scanner_state.next_state = STATE_QR_SCANNER_WAIT;
				break;
				
			case STATE_QR_SCANNER_ERROR_COUNTING:
				
				app_state.scanner_state.next_state = app_state.scanner_state.current_state;
				i ++;
				if(i > 10)															//重发五次
				{
					app_state.scanner_state.current_state = STATE_QR_SCANNER_ON_ERROR;
					app_state.scanner_state.next_state |= 0x80;						//标记错误
					i = 0;
				}
				break;
						
			case STATE_QR_SCANNER_ON_ERROR:
				
				xTaskNotify(xHandleTaskStudentwin,
							bitQRScannerOnError,
							eSetBits);
			
				app_state.scanner_state.current_state = STATE_QR_SCANNER_ON_ERROR;
				app_state.scanner_state.next_state = STATE_QR_SCANNER_WAIT;
				break;
			
			case STATE_QR_SCANNER_WAIT:
				break;
			
			default:
				break;
		}
		vTaskDelay(20);
	}
}
