#include "oneGUI.h"

GUI_XBF_DATA YaHei_24_Data;
GUI_FONT     YaHei_24_Font;
u32			 YaHei_24_Offset = 0x00000000;

GUI_XBF_DATA YaHei_36_Data;
GUI_FONT     YaHei_36_Font;
u32			 YaHei_36_Offset = 0x000D38A2;

GUI_XBF_DATA YaHei_40_Data;
GUI_FONT     YaHei_40_Font;
u32			 YaHei_40_Offset = 0x0027BCAD;

static int _cbGet_24_Data(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer, YaHei_24_Offset+Off, NumBytes);
	return 0;
}

static int _cbGet_36_Data(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer, YaHei_36_Offset+Off, NumBytes);
	return 0;
}

static int _cbGet_40_Data(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer, YaHei_40_Offset+Off, NumBytes);
	return 0;
}

void GUI_SetXBF(void) 
{
	GUI_XBF_CreateFont(&YaHei_24_Font,        
					 &YaHei_24_Data,        
					 GUI_XBF_TYPE_PROP_AA4_EXT,   
					 _cbGet_24_Data,        
					 (void *)0);          
	
	GUI_XBF_CreateFont(&YaHei_36_Font,        
					 &YaHei_36_Data,        
					 GUI_XBF_TYPE_PROP_AA4_EXT,   
					 _cbGet_36_Data,        
					 (void *)0);  
	
	GUI_XBF_CreateFont(&YaHei_40_Font,        
					 &YaHei_40_Data,        
					 GUI_XBF_TYPE_PROP_AA4_EXT,   
					 _cbGet_40_Data,        
					 (void *)0);  
}
