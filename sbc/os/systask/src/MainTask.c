#include "systask.h"
 
static void switchover(WM_HWIN sourse,WM_HWIN destination);

ui_type_struct ui = {
	
	&teacherwin,
	&studentwin,
	&settingwin,
	&wifi_connectwin,
	switchover,
};

static void switchover(WM_HWIN sourse,WM_HWIN destination)
{
	WM_HideWindow(sourse);
	WM_ShowWindow(destination);
	//WM_BringToTop(destination);
	gui.keyboard->close();
	ui.wifi_connectwin->close();
}

 
void MainTask(void)
{	
	SpecializedSkinTypedef *winBMP;
	static SpecializedSkinTypedef BMP_WIN_main;
	BMP_WIN_main.thumbM = &bmsliderThumb; 
	BMP_WIN_main.thumbN = &bmsliderThumb;	
	winBMP = &BMP_WIN_main;
	
	
	ui.studentwin->create();
	ui.teacherwin->create();
	ui.settingwin->create();
	ui.wifi_connectwin->create();
	gui.keyboard->create();
	
	
	WM_SetUserData(ui.settingwin->hwin, &winBMP, sizeof(winBMP));
	ui.teacherwin->close();
	ui.settingwin->close();
	gui.keyboard->close();
	ui.wifi_connectwin->close();
	
	
	while (1)
	{
		GUI_Delay(50);
		//vTaskDelay(10);
	}
}


