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

#define RGB(R,G,B)		(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	/* ��8λR,G,Bת��Ϊ 16λRGB565��ʽ */
#define RGB565_R(x)  	((x >> 8) & 0xF8)
#define RGB565_G(x)  	((x >> 3) & 0xFC)
#define RGB565_B(x)  	((x << 3) & 0xF8)

/* LCD�ֱ������� */
#define LCD_HOR_RESOLUTION		800		/* LCDˮƽ�ֱ��� */
#define LCD_VER_RESOLUTION		480		/* LCD��ֱ�ֱ��� */

/* LCD������������ */
#define LCD_HOR_PULSE_WIDTH		1			/* ˮƽ���� */
#define LCD_HOR_BACK_PORCH		46		/* ˮƽǰ�� */
#define LCD_HOR_FRONT_PORCH		210		/* ˮƽ���� */

#define LCD_VER_PULSE_WIDTH		1			/* ��ֱ���� */
#define LCD_VER_BACK_PORCH		23		/* ��ֱǰ�� */
#define LCD_VER_FRONT_PORCH		22		/* ��ֱǰ�� */

/* ���¼����������Զ����� */
#define LCD_HT	(LCD_HOR_RESOLUTION + LCD_HOR_BACK_PORCH + LCD_HOR_FRONT_PORCH)
#define LCD_HPS	(LCD_HOR_BACK_PORCH)
#define LCD_VT 	(LCD_VER_RESOLUTION + LCD_VER_BACK_PORCH + LCD_VER_FRONT_PORCH)
#define LCD_VPS (LCD_VER_BACK_PORCH)

enum
{
	CL_WHITE        = RGB(255, 255, 255),	/* ��ɫ */
	CL_BLACK        = RGB(  0,  0,  0),	/* ��ɫ */
	CL_RED          = RGB(255,	0,  0),	/* ��ɫ */
	CL_GREEN        = RGB(  0, 255,  0),	/* ��ɫ */
	CL_BLUE         = RGB(  0,	0, 255),	/* ��ɫ */
	CL_YELLOW       = RGB(255, 255,  0),	/* ��ɫ */
	CL_CYAN         = RGB(  0, 255, 255),	/* ��ɫ */

	CL_TRANSPARENT	= 0x9999,		/* �����ڱ���͸�� */
};

typedef enum
{
	GBK_12,		/* GBK���� 12���� */
	GBK_16,		/* GBK���� 16���� */
	GBK_24		/* GBK���� 24���� */
} FONT_CODE_E;

/* �������Խṹ, ����lcd_DispStr() */
typedef struct
{
	FONT_CODE_E FontCode;		/* ������� FONT_CODE_E  */
	uint16_t FrontColor;		/* ������ɫ */
	uint16_t BackColor;			/* ���ֱ�����ɫ��͸�� */
	uint16_t Space;					/* ���ּ�࣬��λ = ���� */
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

