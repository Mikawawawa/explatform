#include "oneGUI.h"

#if	(__USE_SPECIALISED_SKIN)
 
static WM_HWIN WM_GetParent1C(WM_HWIN hChild) {return hChild;}
static WM_HWIN WM_GetParent2C(WM_HWIN hChild) {return WM_GetParent(hChild);}
static WM_HWIN WM_GetParent3C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(hChild));}
static WM_HWIN WM_GetParent4C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(hChild)));}
static WM_HWIN WM_GetParent5C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild))));}
static WM_HWIN WM_GetParent6C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild)))));}
static WM_HWIN WM_GetParent7C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild))))));}
static WM_HWIN WM_GetParent8C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild)))))));}
static WM_HWIN (*WM_GET_PARENT[])(WM_HWIN) = {WM_GetParent1C,WM_GetParent2C,WM_GetParent3C,WM_GetParent4C,WM_GetParent5C,WM_GetParent6C,WM_GetParent7C,WM_GetParent8C};
 
static int SKIN_framewin(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo, unsigned char C)
{
	WM_HWIN hWin;
	int x0, y0;
	SpecializedSkinTypedef *winBMP;
 
	switch (pDrawItemInfo->Cmd) {
		
		case WIDGET_ITEM_Create:
			break;
		
		case WIDGET_ITEM_DRAW_FRAME:
			break;
		
		case WIDGET_ITEM_DRAW_SEP:
			break;
		
		case WIDGET_ITEM_DRAW_TEXT:
			break;
		case WIDGET_ITEM_GET_BORDERSIZE_L:
			break;
		
		case WIDGET_ITEM_GET_BORDERSIZE_R:
			break;
		
		case WIDGET_ITEM_GET_BORDERSIZE_T:
			break;
		
		case WIDGET_ITEM_GET_BORDERSIZE_B:
			break;
		
		case WIDGET_ITEM_GET_RADIUS:
			break;
		
		case WIDGET_ITEM_DRAW_BACKGROUND:
//			hWin = (WM_GET_PARENT[C-1])(pDrawItemInfo->hWin);
//			WM_GetUserData(hWin, &winBMP, sizeof(winBMP));
//			x0 = WM_GetWindowOrgX(hWin) - WM_GetWindowOrgX(pDrawItemInfo->hWin);
//			y0 = WM_GetWindowOrgY(hWin) -WM_GetWindowOrgY(pDrawItemInfo->hWin);
//			GUI_DrawBitmap(winBMP->normal, x0, y0);
			FRAMEWIN_DrawSkinFlex(pDrawItemInfo);
			break;
		default: return FRAMEWIN_DrawSkinFlex(pDrawItemInfo);
	}
	return 0;
}
 
int SKIN_framewin1C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
	return SKIN_framewin(pDrawItemInfo, 1);
}
int SKIN_framewin2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
	return SKIN_framewin(pDrawItemInfo, 2);
}
int SKIN_framewin3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
	return SKIN_framewin(pDrawItemInfo, 3);
}
int SKIN_framewin4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
	return SKIN_framewin(pDrawItemInfo, 4);
}
int SKIN_framewin5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
	return SKIN_framewin(pDrawItemInfo, 5);
}
 
static int SKIN_framewin_paint(WM_HWIN hPage, unsigned char C)
{
	WM_HWIN hWin;
	int x0, y0;
	SpecializedSkinTypedef *winBMP;
 
	hWin = (WM_GET_PARENT[C-1])(hPage);
	WM_GetUserData(hWin, &winBMP, sizeof(winBMP));
	
	x0 = WM_GetWindowOrgX(hWin) - WM_GetWindowOrgX(hPage);
	y0 = WM_GetWindowOrgY(hWin) - WM_GetWindowOrgY(hPage);
	GUI_DrawBitmap(winBMP->normal, x0, y0);
	
	return 0;
}
 

int SKIN_framewin_paint1C(WM_HWIN hWin){
	return SKIN_framewin_paint(hWin, 1);
}

int SKIN_framewin_paint2C(WM_HWIN hWin){
	return SKIN_framewin_paint(hWin, 2);
}

int SKIN_framewin_paint3C(WM_HWIN hWin){
	return SKIN_framewin_paint(hWin, 3);
}

int SKIN_framewin_paint4C(WM_HWIN hWin){
	return SKIN_framewin_paint(hWin, 4);
}

int SKIN_framewin_paint5C(WM_HWIN hWin){
	return SKIN_framewin_paint(hWin, 5);
}

#endif

