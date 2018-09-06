#include "oneConsole.h"

#if (__USE_CONSOLE)

static int init(void);
static void write(const char *str);
static void write_line(const char *s);
static void clear(void);
static int print(char *fmt, ...);

GUI_RECT consoleRect;
static char consoleText[2048];

consoleInfoTypedef console = 
{
	init,
	write,
	write_line,
	print,
	clear,
};

static unsigned int get_total_line(void)
{
	return GUI_GetScreenSizeY() / GUI_GetFontSizeY();
}

static int init(void)
{
	consoleRect.x0 = 0;
	consoleRect.y0 = 0;
	consoleRect.x1 = GUI_GetScreenSizeX();
	consoleRect.y1 = GUI_GetScreenSizeY();
	
	GUI_SetFont(GUI_FONT_24_ASCII);
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	clear();
	
	write_line("Driver Template With FreeRTOS & STemwin [Version 1.0]");
	write_line("Copyright (c) 2018 - 2023 Hdu-Microchip-Lab. All rights reserved.");
	write_line("");
	return 0;
}

static void write(const char *s)
{
	int demandLines;
	
	demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	if (demandLines >= get_total_line())
		clear();
	
	strcat(consoleText, s);
	demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	
	while (demandLines > get_total_line()) {
		strcpy(consoleText, strchr(consoleText, '\n') + 1);
		demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	}
	
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringInRectWrap(consoleText, &consoleRect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);
}

static void write_line(const char *s)
{
	int demandLines;
	
	demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	if (demandLines >= get_total_line())
		clear();

	
	strcat(consoleText, s);
	strcat(consoleText, "\n");
	demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	
	while (demandLines > get_total_line()){
		strcpy(consoleText, strchr(consoleText, '\n') + 1);
		demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	}
	
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringInRectWrap(consoleText, &consoleRect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);
}

static int print(char *fmt, ...)
{
	va_list argptr;
	char *pConsoleText = consoleText;
	int cnt;
	int demandLines;
	
	pConsoleText = strchr(consoleText, '\0');
	va_start(argptr, fmt);
	cnt = vsprintf(pConsoleText, fmt, argptr);
	va_end(argptr);
	
	demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	if (demandLines >= get_total_line())
		clear();

	demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	while (demandLines > get_total_line()){
		strcpy(consoleText, strchr(consoleText, '\n') + 1);
		demandLines = GUI_WrapGetNumLines(consoleText, consoleRect.x1 - consoleRect.x0, GUI_WRAPMODE_CHAR);
	}
	
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringInRectWrap(consoleText, &consoleRect, GUI_TA_LEFT, GUI_WRAPMODE_CHAR);
	return cnt;
}

static void clear(void)
{
	consoleText[0] = '\0';
	GUI_SetColor(GUI_BLACK);
	GUI_FillRectEx(&consoleRect);
}

#endif
