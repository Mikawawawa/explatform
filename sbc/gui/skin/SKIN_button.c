#include <string.h>
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
 
static int SKIN_button(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo, unsigned char C)
{
	
	int contentLength = 0;
	int pxContentHead = 0;
	SpecializedSkinTypedef *button;
 
	GUI_SetFont(GUI_FONT_16B_ASCII);
	GUI_SetBkColor(0xEEEEEE);
	GUI_SetColor(GUI_BLACK);
	
   switch (pDrawItemInfo->Cmd) { 
		 
		case WIDGET_ITEM_Create:
			break;
		case WIDGET_ITEM_DRAW_BITMAP:
      break;
	
   case WIDGET_ITEM_DRAW_BACKGROUND:
		 
      WM_GetUserData(pDrawItemInfo->hWin, &button, sizeof(button));
	 
      if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_ENABLED) {
				GUI_DrawBitmap(button->normal, 0, 0);
				contentLength = strlen((const char *)button->content);
				pxContentHead = (button->size_x >> 1) - (4 * contentLength);
				GUI_DispStringAt((const char *)button->content,pxContentHead, 6);
			}
			
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_PRESSED) {
        GUI_DrawBitmap(button->mark, 0, 5);
				contentLength = strlen((const char *)button->content);
				pxContentHead = (button->size_x >> 1) - (4 * contentLength);
				GUI_DispStringAt((const char *)button->content,pxContentHead, 11);
			}
			
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_FOCUSSED) {
        GUI_DrawBitmap(button->normal, 0, 0);
				contentLength = strlen((const char *)button->content);
				pxContentHead = (button->size_x >> 1) - (4 * contentLength);
				GUI_DispStringAt((const char *)button->content,pxContentHead, 6);
			}
			
      else if(pDrawItemInfo->ItemIndex == BUTTON_SKINFLEX_PI_DISABLED) {
        GUI_DrawBitmap(button->normal, 0, 0);
				contentLength = strlen((const char *)button->content);
				pxContentHead = (button->size_x >> 1) - (4 * contentLength);
				GUI_DispStringAt((const char *)button->content,pxContentHead, 6);
			}
      else BUTTON_DrawSkinFlex(pDrawItemInfo);
      break;
			
		 case WIDGET_ITEM_DRAW_TEXT:
			 return BUTTON_DrawSkinFlex(pDrawItemInfo);
	 
	  default: return BUTTON_DrawSkinFlex(pDrawItemInfo);
   }
   return 0;
}
 

int SKIN_button2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
   return SKIN_button(pDrawItemInfo, 2);
}

int SKIN_button3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
   return SKIN_button(pDrawItemInfo, 3);
}

int SKIN_button4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
   return SKIN_button(pDrawItemInfo, 4);
}

int SKIN_button5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo){
   return SKIN_button(pDrawItemInfo, 5);
}

#endif

