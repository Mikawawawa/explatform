#ifndef __WIDEGT_SLIDEWIN
#define __WIDEGT_SLIDEWIN

#include "WM.h"
#include "GUI.h"

#define			WIDGET_SLIDEWIN_DIR_X											(0)
#define			WIDGET_SLIDEWIN_DIR_Y											(1)

#define			WIDGET_SLIDEWIN_DEFAULT_MOV_DIR						WIDGET_SLIDEWIN_DIR_Y			

#define			WIDGET_SLIDEWIN_DEFAULT_AXIS_X						0
#define			WIDGET_SLIDEWIN_DEFAULT_AXIS_Y						0

#define			WIDGET_SLIDEWIN_DEFAULT_SIZE_X						800
#define			WIDGET_SLIDEWIN_DEFAULT_SIZE_Y						480

typedef struct WIDEGT_slide_page {
	WM_HWIN											hWin;
	unsigned int								id;
	WM_HWIN											(*constructor)(void);
	void												(*destructor)(void);
	
	struct WIDEGT_slide_page		*vNext;
	struct WIDEGT_slide_page  	*vPriv;
	
}WIDEGT_slidePageInfoStructTypedef;


typedef struct WIDEGT_slide{
	int 																axis_x;
	int 																axis_y;
	unsigned int												size_x;
	unsigned int												size_y;
	unsigned int												num;
	
	unsigned int												mov_dir;
	
	WM_HWIN															hWin;
	
	WIDEGT_slidePageInfoStructTypedef		*page_root;
	WIDEGT_slidePageInfoStructTypedef		*page_index;
	
	WM_HWIN															(*createAt)(unsigned int x0, unsigned int y0, unsigned int x_size, unsigned int y_size);
	void																(*install)(WM_HWIN (*constructor)(), void (*destructor)(), unsigned int pos, unsigned page_id);
	void																(*uninstall)(unsigned page_id);
	void																(*open)(void);
	void																(*close)(void);
	void																(*moveTo)(unsigned int axis_x, unsigned int axis_y);
	void 																(*go_to_priv)(void);
	void 																(*go_to_next)(void);
	void 																(*slide_event)(void);
	
}WIDEGT_slidewinInfoStructTypedef;

extern WIDEGT_slidewinInfoStructTypedef slidewin;

WM_HWIN SlidewinPageOnCreate(void);

#endif
