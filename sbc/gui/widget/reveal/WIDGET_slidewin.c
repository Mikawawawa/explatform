#include "bsp.h"
#include "uiBuild.h"

#if (__USE_WIDGET_SLIDEWIN)

static WM_HWIN	createAt(unsigned int x0, unsigned int y0, unsigned int x_size, unsigned int y_size);
static void			install(WM_HWIN (*constructor)(), void (*destructor)(), unsigned int pos, unsigned page_id);
static void			uninstall(unsigned page_id);
static void 		open(void);
static void 		close(void);
static void 		moveTo(unsigned int axis_x, unsigned int axis_y);
static void 		go_to_priv(void);
static void 		go_to_next(void);
static void 		slide_event(void);

WIDEGT_slidewinInfoStructTypedef slidewin = {
	WIDGET_SLIDEWIN_DEFAULT_AXIS_X,
	WIDGET_SLIDEWIN_DEFAULT_AXIS_Y,
	WIDGET_SLIDEWIN_DEFAULT_SIZE_X,
	WIDGET_SLIDEWIN_DEFAULT_SIZE_Y,
	0,
	
	WIDGET_SLIDEWIN_DEFAULT_MOV_DIR,
	
	(WM_HWIN)0,
	
	NULL,
	NULL,
	
	createAt,
	install,
	uninstall,
	open,
	close,
	moveTo,
	go_to_priv,
	go_to_next,
	slide_event
};

static WIDEGT_slidePageInfoStructTypedef *traverse(WIDEGT_slidePageInfoStructTypedef *pRoot, unsigned int node_number)
{
	unsigned int i;
	WIDEGT_slidePageInfoStructTypedef *pIndex = pRoot;
	
	for(i=0; i<node_number; i++) {
		if(NULL == pIndex || NULL == pIndex->vNext) 
			return pIndex;
		else
			pIndex = pIndex->vNext;
	}
	
	return pIndex;
}

static WM_HWIN createAt(unsigned int x0, unsigned int y0, unsigned int x_size, unsigned int y_size)
{
	slidewin.axis_x = x0;
	slidewin.axis_y = y0;
	slidewin.size_x = x_size;
	slidewin.size_y = y_size;
	
	slidewin.hWin = SlidewinPageOnCreate();
	
	slidewin.page_root = (WIDEGT_slidePageInfoStructTypedef	*)calloc(sizeof(WIDEGT_slidePageInfoStructTypedef), 1);
	if(NULL == slidewin.page_root)
		return (WM_HWIN)0;
	
	slidewin.page_index = slidewin.page_root;
	slidewin.page_index->hWin = (WM_HWIN)0;
	slidewin.page_index->id = 0u;
	slidewin.page_index->vNext = NULL;
	slidewin.page_index->vPriv = NULL;
	
	return slidewin.hWin;
}

static void install(WM_HWIN (*constructor)(), void (*destructor)(), unsigned int pos, unsigned page_id)
{
	WIDEGT_slidePageInfoStructTypedef *pIndex;
	WIDEGT_slidePageInfoStructTypedef *pNode;
	
	pIndex = traverse(slidewin.page_root, pos - 1);
	
	if(NULL == pIndex)
		return;
	if(NULL == constructor || NULL == destructor)
		return;
	
	pNode = (WIDEGT_slidePageInfoStructTypedef	*)calloc(sizeof(WIDEGT_slidePageInfoStructTypedef), 1);
	pNode->constructor = constructor;
	pNode->destructor = destructor;
	pNode->hWin = pNode->constructor();
	WM_AttachWindow(pNode->hWin, slidewin.hWin);
	pNode->id = page_id;
	if(NULL == pIndex->vNext)
		pNode->vNext = NULL;
	else {
		pNode->vNext = pIndex->vNext;
		pNode->vNext->vPriv = pIndex;
	}
	pNode->vPriv = pIndex;
	pNode->vPriv->vNext = pNode;
	
	if(pIndex == slidewin.page_root)
		slidewin.page_index = pIndex->vNext;
	else {
		if(WIDGET_SLIDEWIN_DIR_X == slidewin.mov_dir)
			WM_MoveTo(pNode->hWin, slidewin.axis_x - slidewin.size_x, slidewin.axis_y);
		if(WIDGET_SLIDEWIN_DIR_Y == slidewin.mov_dir)
			WM_MoveTo(pNode->hWin, slidewin.axis_x, slidewin.size_y - slidewin.size_y);
		WM_HideWin(pNode->hWin);
	}
	
}

static void uninstall(unsigned page_id)
{
	
}

static void open()
{
	WM_ShowWin(slidewin.hWin);
}

static void close()
{
	WM_HideWin(slidewin.hWin);
}

static void moveTo(unsigned int axis_x, unsigned int axis_y)
{
	WM_MoveTo(slidewin.hWin, axis_x, axis_y);
}

static void go_to_priv()
{
	unsigned int i;
	
	if(NULL == slidewin.page_index || slidewin.page_root == slidewin.page_index->vPriv)
		return; 
		if(WIDGET_SLIDEWIN_DIR_X == slidewin.mov_dir) {
			WM_MoveTo(slidewin.page_index->vPriv->hWin, slidewin.axis_x - slidewin.size_x, slidewin.axis_y);
			WM_ShowWin(slidewin.page_index->vPriv->hWin);
			for(i=1; i<41; i++) {
				WM_MoveTo(slidewin.page_index->vPriv->hWin, slidewin.axis_x - slidewin.size_x + ((char)((float)slidewin.size_x / 40))*i, slidewin.axis_y);
				WM_MoveTo(slidewin.page_index->hWin, ((char)((float)slidewin.size_x / 40)) * i + slidewin.axis_x, slidewin.axis_y);
				GUI_Exec();
			}
		}
		
	else if(WIDGET_SLIDEWIN_DIR_Y == slidewin.mov_dir){
		WM_MoveTo(slidewin.page_index->vPriv->hWin, slidewin.axis_x, slidewin.axis_y - slidewin.size_y);
		WM_ShowWin(slidewin.page_index->vPriv->hWin);
		for(i=1; i<41; i++) {
			WM_MoveTo(slidewin.page_index->vPriv->hWin, slidewin.axis_x, slidewin.axis_y - slidewin.size_y + ((char)((float)slidewin.size_y / 40))*i);
			WM_MoveTo(slidewin.page_index->hWin, slidewin.axis_x, slidewin.axis_y + ((char)((float)slidewin.size_y / 40))*i);
			GUI_Exec();
		}
	}
	WM_HideWin(slidewin.page_index->hWin);
	slidewin.page_index = slidewin.page_index->vPriv;
	
}

static void go_to_next()
{
	unsigned int i;
	
	if(NULL == slidewin.page_index || NULL == slidewin.page_index->vNext)
		return; 
	if(WIDGET_SLIDEWIN_DIR_X == slidewin.mov_dir) {
		WM_MoveTo(slidewin.page_index->vNext->hWin, slidewin.axis_x + slidewin.size_x, slidewin.axis_y);
		WM_ShowWin(slidewin.page_index->vNext->hWin);
		for(i=1; i<41; i++) {
			WM_MoveTo(slidewin.page_index->vNext->hWin, slidewin.axis_x + slidewin.size_x - ((char)((float)slidewin.size_x / 40))*i, slidewin.axis_y);
			WM_MoveTo(slidewin.page_index->hWin, slidewin.axis_x - ((char)((float)slidewin.size_x / 40))*i  , slidewin.axis_y);
			GUI_Exec();
		}
	}
	
	else if(WIDGET_SLIDEWIN_DIR_Y == slidewin.mov_dir){
		WM_MoveTo(slidewin.page_index->vNext->hWin, slidewin.axis_x, slidewin.axis_y + slidewin.size_y);
		WM_ShowWin(slidewin.page_index->vNext->hWin);
		for(i=1; i<41; i++) {
			WM_MoveTo(slidewin.page_index->vNext->hWin, slidewin.axis_x, slidewin.axis_y + slidewin.size_y - ((char)((float)slidewin.size_y / 40))*i);
			WM_MoveTo(slidewin.page_index->hWin, slidewin.axis_x, slidewin.axis_y - ((char)((float)slidewin.size_y / 40))*i);
			GUI_Exec();
		}
	}
	
	WM_HideWin(slidewin.page_index->hWin);
	slidewin.page_index = slidewin.page_index->vNext;
}

static void slide_event()
{
	static int slide_x = 0;
	static int slide_y = 0;
	static int event_count = 0;
	static unsigned char dir = 0;
	
	if(touch.coordXY[0].x > slidewin.axis_x && touch.coordXY[0].x < slidewin.axis_x + slidewin.size_x && touch.coordXY[0].y > slidewin.axis_y && touch.coordXY[0].y < slidewin.axis_y + slidewin.size_y) {
		if(0 == dir) {
			dir = 1;
			return;
		}
		if(WIDGET_SLIDEWIN_DIR_X == slidewin.mov_dir) {
			if( 1 == dir) {
				if(touch.coordXY[0].x < slide_x - slidewin.size_x/40)
					dir = 2;
				else if(touch.coordXY[0].x > slide_x + slidewin.size_x/40)
					dir = 3;
				return;
			}
			
			if( 2 == dir) {	
				if(touch.coordXY[0].x < slide_x - slidewin.size_x/40)
					event_count ++;
				else {
					event_count = 0;
					dir = 0;
				}
				slide_x = touch.coordXY[0].x;
			}
			
			if(3 == dir) {
				if(touch.coordXY[0].x > slide_x + slidewin.size_x/40)
					event_count ++;
				else {
					event_count = 0;
					dir = 0;
				}
			}
		}
		
		else if(WIDGET_SLIDEWIN_DIR_Y == slidewin.mov_dir) {
			if( 1 == dir) {
				if(touch.coordXY[0].y < slide_y - slidewin.size_y/40)
					dir = 2;
				else if(touch.coordXY[0].y > slide_y + slidewin.size_y/40)
					dir = 3;
				return;
			}
			
			if( 2 == dir) {	
				if(touch.coordXY[0].y < slide_y - slidewin.size_y/40)
					event_count ++;
				else {
					event_count = 0;
					dir = 0;
				}
				slide_y = touch.coordXY[0].y;
			}
			
			if(3 == dir) {
				if(touch.coordXY[0].y > slide_y + slidewin.size_y/40)
					event_count ++;
				else {
					event_count = 0;
					dir = 0;
				}
			}
		}
		
		if(event_count > 3) {
			event_count = 0;
			if(2 == dir) go_to_next();
			if(3 == dir) go_to_priv();
			
			dir = 0;
		}
		slide_x = touch.coordXY[0].x;
		slide_y = touch.coordXY[0].y;
	}
	else {
		dir = 0;
		event_count = 0;
		slide_x = 0;
		slide_y = 0;
	}
	
}

#endif
