#include "uiBuild.h"

//extern GUI_CONST_STORAGE GUI_BITMAP bmslider_thumb0;  
//extern GUI_CONST_STORAGE GUI_BITMAP bmslider_thumb2;  
  

static WM_HWIN WM_GetParent1C(WM_HWIN hChild) {return hChild;}  
static WM_HWIN WM_GetParent2C(WM_HWIN hChild) {return WM_GetParent(hChild);}  
static WM_HWIN WM_GetParent3C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(hChild));}  
static WM_HWIN WM_GetParent4C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(hChild)));}  
static WM_HWIN WM_GetParent5C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild))));}  
static WM_HWIN WM_GetParent6C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild)))));}  
static WM_HWIN WM_GetParent7C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild))))));}  
static WM_HWIN WM_GetParent8C(WM_HWIN hChild) {return WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(WM_GetParent(hChild)))))));}  
static WM_HWIN (*WM_GET_PARENT[])(WM_HWIN) = {WM_GetParent1C,WM_GetParent2C,WM_GetParent3C,WM_GetParent4C,WM_GetParent5C,WM_GetParent6C,WM_GetParent7C,WM_GetParent8C};  

static int SKIN_slider(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo, unsigned char C)  
{  
    SpecializedSkinTypedef *winBMP;  
  
    switch (pDrawItemInfo->Cmd)  
    {  
    case WIDGET_ITEM_Create:  
			break;
  
    case WIDGET_ITEM_DRAW_TICKS:  
        break;  
		case WIDGET_ITEM_DRAW_FOCUS:  
        break;  
    default: return SLIDER_DrawSkinFlex(pDrawItemInfo);
  
    case WIDGET_ITEM_DRAW_SHAFT:  
			SLIDER_DrawSkinFlex(pDrawItemInfo);
        break;  
    case WIDGET_ITEM_DRAW_THUMB:  
        WM_GetUserData(ui.settingwin->hwin, &winBMP, sizeof(winBMP));  
        if(((SLIDER_SKINFLEX_INFO *)(pDrawItemInfo->p))->IsPressed != 1)  
            GUI_DrawBitmap(winBMP->thumbN, pDrawItemInfo->x0, pDrawItemInfo->y0+5);  
        else  
				{
					GUI_DrawBitmap(winBMP->thumbM, pDrawItemInfo->x0, pDrawItemInfo->y0+5);  
				}
        break;  
  
    }  
    return 0;  
}  
  

int SKIN_slider2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){  
    return SKIN_slider(pDrawItemInfo, 2);  
}  
  
int SKIN_slider3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){  
    return SKIN_slider(pDrawItemInfo, 3);  
}  

int SKIN_slider4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){  
    return SKIN_slider(pDrawItemInfo, 4);  
}  

int SKIN_slider5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){  
    return SKIN_slider(pDrawItemInfo, 5);  
}  

