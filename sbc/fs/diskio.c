/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"						/* FatFs lower layer API */
#include "bsp_spi_flash.h"		/* SPI FLASH lower layer API */

/* Definitions of physical drive number for each drive */
#define SPI_FLASH		0		/* Example: Map SPI_FLASH harddisk to physical drive 0 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
  BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
  BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	switch (pdrv)
	{
	case SPI_FLASH :
		SPI_FLASH_Init();
		if(SPI_FLASH_ReadID() == sFLASH_ID)
		{
			return 0;
		}
		break;
	}
	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
  BYTE pdrv,		/* Physical drive nmuber to identify the drive */
  BYTE *buff,		/* Data buffer to store read data */
  DWORD sector,	/* Sector address in LBA */
  UINT count		/* Number of sectors to read */
)
{
	switch (pdrv)
	{
	case SPI_FLASH :
		sector += FLASH_SECTOR_OFFSET;
		while(count--)
		{
			SPI_FLASH_BufferRead(buff, sector * FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE);
			buff += FLASH_SECTOR_SIZE;
			sector++;
		}
		return RES_OK;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
  BYTE pdrv,			/* Physical drive nmuber to identify the drive */
  const BYTE *buff,	/* Data to be written */
  DWORD sector,		/* Sector address in LBA */
  UINT count			/* Number of sectors to write */
)
{
	switch (pdrv)
	{
	case SPI_FLASH :
		sector += FLASH_SECTOR_OFFSET;
		while(count--)
		{
			SPI_FLASH_BufferWrite((uint8_t *)buff, sector * FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE);
			buff += FLASH_SECTOR_SIZE;
			sector++;
		}
		return RES_OK;
	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
  BYTE pdrv,		/* Physical drive nmuber (0..) */
  BYTE cmd,		/* Control code */
  void *buff		/* Buffer to send/receive control data */
)
{
	switch (pdrv)
	{
	case SPI_FLASH :
		switch(cmd)
		{
		case CTRL_SYNC:
			break;
		case GET_SECTOR_COUNT:
			*(DWORD *)buff = FLASH_SECTOR_COUNT;
			break;
		case GET_SECTOR_SIZE:
			*(DWORD *)buff = FLASH_SECTOR_SIZE;
			break;
		case GET_BLOCK_SIZE:
			break;
		default:
			return RES_PARERR;
		}
		return RES_OK;

	}

	return RES_PARERR;
}
#endif

DWORD get_fattime (void)
{
	return 0;
}
