#ifndef __SPECIALSKIN_H
#define __SPECIALSKIN_H

#include "GUI.h"
#include "WM.h"
#include "DIALOG.h"
#include "WIDGET.h"

typedef struct{
  const GUI_BITMAP *normal;
  const GUI_BITMAP *mark;
  const GUI_BITMAP *focus;
  const GUI_BITMAP *disable;
  const GUI_BITMAP *thumbN;
  const GUI_BITMAP *thumbM;
	unsigned int 			axis_x;
	unsigned int 			axis_y;
	unsigned int 			size_x;
	unsigned int			size_y;
	unsigned char* 		content;
} SpecializedSkinTypedef;


extern GUI_CONST_STORAGE GUI_BITMAP bmsliderShaft;
extern GUI_CONST_STORAGE GUI_BITMAP bmsliderThumb;

int SKIN_button2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_button3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_button4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_button5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_buttonSKB2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_buttonSKB3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_buttonSKB4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_buttonSKB5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_checkbox2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_checkbox3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_checkbox4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_checkbox5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_dropdown2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_dropdown3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_dropdown4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_dropdown5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_framewin1C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_framewin2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_framewin3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_framewin4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_framewin5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_framewin_paint1C(WM_HWIN hWin);
int SKIN_framewin_paint2C(WM_HWIN hWin);
int SKIN_framewin_paint3C(WM_HWIN hWin);
int SKIN_framewin_paint4C(WM_HWIN hWin);
int SKIN_framewin_paint5C(WM_HWIN hWin);
int SKIN_multipage2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_multipage3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_multipage4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_multipage5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_multipage_paint4C(WM_HWIN hPage);
int SKIN_multipage_paint5C(WM_HWIN hPage);
int SKIN_progbar2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_progbar3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_progbar4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_progbar5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_progbarmeter2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_progbarmeter3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_progbarmeter4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_progbarmeter5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_radio2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_radio3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_radio4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_radio5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_scrollbar5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_slider2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_slider3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_slider4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_slider5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_spinbox2C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_spinbox3C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_spinbox4C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
int SKIN_spinbox5C(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);




#endif

