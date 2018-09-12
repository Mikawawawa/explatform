#ifndef _BSP_lcd_H
#define _BSP_lcd_H

#include "stm32f4xx.h"

typedef struct
{
	 uint16_t REG;
	 uint16_t RAM;
} lcd_ram_type_struct;

typedef struct 
{
	uint16_t	write_gram;
	uint16_t	read_gram;
	uint16_t	set_x;
	uint16_t	set_y;
}lcd_command_type_struct;

#define LCD_BASE        ((uint32_t)(0x6C000000 | 0x0000007E))
#define LCD             ((lcd_ram_type_struct *) LCD_BASE)

#define	CMD_WRITE_GRAM	0x2C00

#define RGB(R,G,B)		(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	/* 将8位R,G,B转化为 16位RGB565格式 */
#define RGB565_R(x)  	((x >> 8) & 0xF8)
#define RGB565_G(x)  	((x >> 3) & 0xFC)
#define RGB565_B(x)  	((x << 3) & 0xF8)

/* LCD分辨率设置 */
#define LCD_HOR_RESOLUTION		800		/* LCD水平分辨率 */
#define LCD_VER_RESOLUTION		480		/* LCD垂直分辨率 */

/* LCD驱动参数设置 */
#define LCD_HOR_PULSE_WIDTH		1			/* 水平脉宽 */
#define LCD_HOR_BACK_PORCH		46		/* 水平前廊 */
#define LCD_HOR_FRONT_PORCH		210		/* 水平后廊 */

#define LCD_VER_PULSE_WIDTH		1			/* 垂直脉宽 */
#define LCD_VER_BACK_PORCH		23		/* 垂直前廊 */
#define LCD_VER_FRONT_PORCH		22		/* 垂直前廊 */

/* 如下几个参数，自动计算 */
#define LCD_HT	(LCD_HOR_RESOLUTION + LCD_HOR_BACK_PORCH + LCD_HOR_FRONT_PORCH)
#define LCD_HPS	(LCD_HOR_BACK_PORCH)
#define LCD_VT 	(LCD_VER_RESOLUTION + LCD_VER_BACK_PORCH + LCD_VER_FRONT_PORCH)
#define LCD_VPS (LCD_VER_BACK_PORCH)

enum
{
	CL_WHITE        = RGB(255, 255, 255),	/* 白色 */
	CL_BLACK        = RGB(  0,  0,  0),	/* 黑色 */
	CL_RED          = RGB(255,	0,  0),	/* 红色 */
	CL_GREEN        = RGB(  0, 255,  0),	/* 绿色 */
	CL_BLUE         = RGB(  0,	0, 255),	/* 蓝色 */
	CL_YELLOW       = RGB(255, 255,  0),	/* 黄色 */
	CL_CYAN         = RGB(  0, 255, 255),	/* 青色 */

	CL_TRANSPARENT	= 0x9999,		/* 仅用于背景透明 */
};

typedef enum
{
	GBK_12,		/* GBK字体 12点阵 */
	GBK_16,		/* GBK字体 16点阵 */
	GBK_24		/* GBK字体 24点阵 */
} FONT_CODE_E;

/* 字体属性结构, 用于lcd_DispStr() */
typedef struct
{
	FONT_CODE_E FontCode;		/* 字体代码 FONT_CODE_E  */
	uint16_t FrontColor;		/* 字体颜色 */
	uint16_t BackColor;			/* 文字背景颜色，透明 */
	uint16_t Space;					/* 文字间距，单位 = 像素 */
} FONT_T;

typedef struct lcd_type {
	uint16_t								id;
	lcd_command_type_struct command;
	
  void 										(*init)(void);
  void 										(*open)(void);
  void 										(*close)(void);
  void 										(*set_backlight)(uint8_t pwm);
  void 										(*set_cursor)(uint16_t _usX, uint16_t _usY);
  void 										(*set_window)(uint16_t _usX0, uint16_t _usY0, uint16_t _usX1, uint16_t _usY1);
  void 										(*clear)(uint16_t _usColor);
  void 										(*put_pixel)(uint16_t _usX, uint16_t _usY, uint16_t _usColor);
  void 										(*put_pixel_gui)(uint16_t _usX, uint16_t _usY, uint16_t _usColor);
  uint16_t					 			(*get_pixel)(uint16_t _usX, uint16_t _usY);
  uint16_t 								(*get_pixel_gui)(uint16_t _usX, uint16_t _usY);
  void 										(*draw_line)(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint16_t _usColor);
  void 										(*draw_H_colorLine)(uint16_t _usX , uint16_t _usY, uint16_t _usWidth, uint16_t *_pColor);
  void 										(*draw_H_line)(uint16_t _usX0 , uint16_t _usY , uint16_t _usX1 , uint16_t _usColor);
  void 										(*draw_V_line)(uint16_t _usX , uint16_t _usY0 , uint16_t _usY1 , uint16_t _usColor);
  void 										(*draw_circle)(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);
  void 										(*draw_rect)(uint16_t _usX, uint16_t _usY, uint8_t _ucHeight, uint16_t _usWidth, uint16_t _usColor);
  void 										(*fill_rect)(uint16_t _usX0, uint16_t _usY0, uint16_t _usX1, uint16_t _usY1, uint16_t _usColor);
}bsp_lcd_struct;

extern bsp_lcd_struct lcd;

#endif

