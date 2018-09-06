#ifndef __PUSHBUTTON_H
#define __PUSHBUTTON_H

#include "WM.h"

/* alpha混合背景色 */
#define PUSHBUTTON_BKCOLOR_UNSEL GUI_BLACK
#define PUSHBUTTON_BKCOLOR_SEL (0X007C7782)

extern void pushButtonInitSettingDialog(WM_HWIN hWin);
extern void pushButtonInitStudentDialog(WM_HWIN hWin);
extern void pushButtonInitTeacherDialog(WM_HWIN hWin);
extern void pushButtonInitVolumeSwitchDialog(WM_HWIN hWin);

//extern void backButtonMessageProcess(int NCode);
//extern void homepageButtonMessageProcess(int NCode);
//extern void menuMessageProcess(int NCode);


#endif


