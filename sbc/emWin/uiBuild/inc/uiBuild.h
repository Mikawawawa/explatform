#ifndef __UIBUILD_H
#define __UIBUILD_H

#include "oneGUI.h"
#include "UI_pushButton.h"
#include "UI_student.h"
#include "UI_setting.h"
#include "UI_teacher.h"
#include "UI_wifi_connect.h"

#define ID_FRAMEWIN_TEACHER_0    	(GUI_ID_USER + 0x00)
#define ID_IMAGE_TEACHER_0    		(GUI_ID_USER + 0x01)
#define ID_IMAGE_TEACHER_1    		(GUI_ID_USER + 0x02)
#define ID_IMAGE_TEACHER_2    		(GUI_ID_USER + 0x03)
#define ID_TEXT_TEACHER_0    		(GUI_ID_USER + 0x04)
#define ID_TEXT_TEACHER_1    		(GUI_ID_USER + 0x05)
#define ID_TEXT_TEACHER_2    		(GUI_ID_USER + 0x06)
#define ID_TEXT_TEACHER_3    		(GUI_ID_USER + 0x07)
#define ID_EDIT_TEACHER_0    		(GUI_ID_USER + 0x09)
#define ID_EDIT_TEACHER_1    		(GUI_ID_USER + 0x0A)
#define ID_DROPDOWN_TEACHER_0       (GUI_ID_USER + 0x0C)
#define ID_BUTTON_TEACHER_0   		(GUI_ID_USER + 0x0D)
#define ID_BUTTON_TEACHER_1   		(GUI_ID_USER + 0x0E)
#define ID_BUTTON_TEACHER_2    		(GUI_ID_USER + 0x0F)
#define ID_IMAGE_TEACHER_6			(GUI_ID_USER + 0x10)
#define ID_TEXT_TEACHER_4    		(GUI_ID_USER + 0x11)

#define ID_FRAMEWIN_STUDENT_0    	(GUI_ID_USER + 0x00)
#define ID_IMAGE_STUDENT_0    		(GUI_ID_USER + 0x01)
#define ID_IMAGE_STUDENT_1    		(GUI_ID_USER + 0x02)
#define ID_IMAGE_STUDENT_2    		(GUI_ID_USER + 0x03)
#define ID_TEXT_STUDENT_0    		(GUI_ID_USER + 0x04)
#define ID_TEXT_STUDENT_1    		(GUI_ID_USER + 0x05)
#define ID_TEXT_STUDENT_2    		(GUI_ID_USER + 0x06)
#define ID_TEXT_STUDENT_3   		(GUI_ID_USER + 0x07)
#define ID_EDIT_STUDENT_1    		(GUI_ID_USER + 0x08)
#define ID_EDIT_STUDENT_2    		(GUI_ID_USER + 0x09)
#define ID_EDIT_STUDENT_3    		(GUI_ID_USER + 0x0A)
#define ID_BUTTON_STUDENT_0    		(GUI_ID_USER + 0x0B)
#define ID_BUTTON_STUDENT_1    		(GUI_ID_USER + 0x0C)
#define ID_BUTTON_STUDENT_2			(GUI_ID_USER + 0x0D)
#define ID_IMAGE_STUDENT_6			(GUI_ID_USER + 0x0E)
#define ID_TEXT_STUDENT_4   		(GUI_ID_USER + 0x0F)
#define ID_EDIT_STUDENT_4    		(GUI_ID_USER + 0x10)

#define ID_FRAMEWIN_0    	(GUI_ID_USER + 0x00)
#define ID_TEXT_0    		(GUI_ID_USER + 0x01)
#define ID_TEXT_1    		(GUI_ID_USER + 0x02)
#define ID_TEXT_2    		(GUI_ID_USER + 0x03)
#define ID_EDIT_0    		(GUI_ID_USER + 0x04)
#define ID_EDIT_1    		(GUI_ID_USER + 0x05)
#define ID_EDIT_2    		(GUI_ID_USER + 0x06)
#define ID_TEXT_3    		(GUI_ID_USER + 0x07)
#define ID_BUTTON_0    		(GUI_ID_USER + 0x08)
#define ID_BUTTON_1    		(GUI_ID_USER + 0x09)
#define ID_BUTTON_2    		(GUI_ID_USER + 0x0a)
#define ID_BUTTON_3    		(GUI_ID_USER + 0x0b)
#define ID_BUTTON_4    		(GUI_ID_USER + 0x0c)
#define ID_BUTTON_5    		(GUI_ID_USER + 0x0d)
#define ID_IMAGE_0 			(GUI_ID_USER + 0x0e)
#define ID_IMAGE_1 			(GUI_ID_USER + 0x0f)
#define ID_IMAGE_2 			(GUI_ID_USER + 0x10)
#define ID_IMAGE_3 			(GUI_ID_USER + 0x11)
#define ID_IMAGE_4 			(GUI_ID_USER + 0x12)
#define ID_IMAGE_5 			(GUI_ID_USER + 0x13)
#define ID_IMAGE_6 			(GUI_ID_USER + 0x14)
#define ID_IMAGE_7 			(GUI_ID_USER + 0x15)
#define ID_IMAGE_8 			(GUI_ID_USER + 0x16)
#define ID_IMAGE_9 			(GUI_ID_USER + 0x17)
#define ID_IMAGE_A 			(GUI_ID_USER + 0x18)
#define ID_IMAGE_B 			(GUI_ID_USER + 0x19)
#define ID_IMAGE_C 			(GUI_ID_USER + 0x1a)
#define ID_LISTVIEW_0    	(GUI_ID_USER + 0x1b)
#define ID_IMAGE_D 			(GUI_ID_USER + 0x1c)
#define ID_IMAGE_E 			(GUI_ID_USER + 0x1d)
#define ID_BUTTON_6 		(GUI_ID_USER + 0x1f)
#define ID_SLIDER_0			(GUI_ID_USER + 0x20)

#define ID_FRAMEWIN_WIFI_0  (GUI_ID_USER + 0x20)
#define ID_TEXT_WIFI_0     	(GUI_ID_USER + 0x22)
#define ID_TEXT_WIFI_1      (GUI_ID_USER + 0x23)
#define ID_TEXT_WIFI_2      (GUI_ID_USER + 0x24)
#define ID_TEXT_WIFI_3      (GUI_ID_USER + 0x25)
#define ID_TEXT_WIFI_4      (GUI_ID_USER + 0x26)
#define ID_EDIT_WIFI_0      (GUI_ID_USER + 0x27)
#define ID_CHECKBOX_WIFI_0  (GUI_ID_USER + 0x28)
#define ID_BUTTON_WIFI_0    (GUI_ID_USER + 0x29)
#define ID_BUTTON_WIFI_1    (GUI_ID_USER + 0x2A)

typedef struct {
	
	UI_teacherwinInfoStructTypedef 		*teacherwin;
	UI_studentwinInfoStructTypedef 		*studentwin;
	UI_settingwinInfoStructTypedef 		*settingwin;
	UI_wifi_connectwinInfoStructTypedef *wifi_connectwin;
	
	void 								(*switchover)(WM_HWIN sourse,WM_HWIN destination);
		
}ui_type_struct;

typedef struct {

	u8							studentwin_state;
	u8							teacherwin_state;
	u8							settingwin_state;
	u8							wifi_connectwin_state;

}ui_state_type_struct;

extern ui_type_struct ui;
extern ui_state_type_struct ui_state;

WM_HWIN StudentPageOnCreate(void);
WM_HWIN TeacherPageOnCreate(void);
WM_HWIN SettingPageOnCreate(void);
WM_HWIN WifiConnectPageOnCreate(void);

#endif

