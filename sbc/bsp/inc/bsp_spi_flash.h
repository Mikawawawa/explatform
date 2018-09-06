#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
#define W25Q80					0XEF13 	
#define W25Q16					0XEF14
#define W25Q32					0XEF15
#define W25Q64					0XEF16
#define W25Q128					0XEF17

#define sFLASH_ID               W25Q128

#define FLASH_SECTOR_SIZE		512					/* 扇区大小：4096字节 */
#define	FLASH_BLOCK_SIZE		8					/* 每个Block拥有8个扇区 */
#define FLASH_SECTOR_COUNT	(8 * 1024 * 1024 / FLASH_SECTOR_SIZE)	/* 扇区数 */
#define FLASH_SECTOR_OFFSET	(8 * 1024 * 1024 / FLASH_SECTOR_SIZE)

//#define SPI_FLASH_PageSize            4096
#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

#define SPI_BAUD                        SPI_BaudRatePrescaler_2

/* Private define ------------------------------------------------------------*/
/*命令定义-开头*******************************/
#define W25X_WriteEnable		0x06
#define W25X_WriteDisable		0x04
#define W25X_ReadStatusReg		0x05
#define W25X_WriteStatusReg		0x01
#define W25X_ReadData			0x03
#define W25X_FastReadData		0x0B
#define W25X_FastReadDual		0x3B
#define W25X_PageProgram		0x02
#define W25X_BlockErase			0xD8
#define W25X_SectorErase		0x20
#define W25X_ChipErase			0xC7
#define W25X_PowerDown			0xB9
#define W25X_ReleasePowerDown	0xAB
#define W25X_DeviceID			0xAB
#define W25X_ManufactDeviceID	0x90
#define W25X_JedecDeviceID		0x9F

/*命令定义-结尾*******************************/


/*SPI接口定义-开头****************************/
#define FLASH_SPI                           SPI1
#define FLASH_SPI_CLK                       RCC_APB2Periph_SPI1
#define FLASH_SPI_CLK_INIT                  RCC_APB2PeriphClockCmd

#define FLASH_SPI_SCK_PIN                   GPIO_Pin_3
#define FLASH_SPI_SCK_GPIO_PORT             GPIOB
#define FLASH_SPI_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define FLASH_SPI_SCK_PINSOURCE             GPIO_PinSource3
#define FLASH_SPI_SCK_AF                    GPIO_AF_SPI1

#define FLASH_SPI_MISO_PIN                  GPIO_Pin_4
#define FLASH_SPI_MISO_GPIO_PORT            GPIOB
#define FLASH_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define FLASH_SPI_MISO_PINSOURCE            GPIO_PinSource4
#define FLASH_SPI_MISO_AF                   GPIO_AF_SPI1

#define FLASH_SPI_MOSI_PIN                  GPIO_Pin_5
#define FLASH_SPI_MOSI_GPIO_PORT            GPIOB
#define FLASH_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define FLASH_SPI_MOSI_PINSOURCE            GPIO_PinSource5
#define FLASH_SPI_MOSI_AF                   GPIO_AF_SPI1

#define FLASH_CS_PIN                        GPIO_Pin_14
#define FLASH_CS_GPIO_PORT                  GPIOB
#define FLASH_CS_GPIO_CLK                   RCC_AHB1Periph_GPIOB

#define SPI_FLASH_CS_LOW()      {FLASH_CS_GPIO_PORT->BSRRH=FLASH_CS_PIN;}
#define SPI_FLASH_CS_HIGH()     {FLASH_CS_GPIO_PORT->BSRRL=FLASH_CS_PIN;}
/*SPI接口定义-结尾****************************/

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/
#define FLASH_DEBUG_ON         1

#define FLASH_INFO(fmt,arg...)           printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)          do{\
                                          if(FLASH_DEBUG_ON)\
                                          printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)



void SPI_FLASH_Init(void);
uint16_t  SPI_FLASH_ReadID(void);  	    		//读取FLASH ID
uint8_t	 SPI_FLASH_ReadSR(void);        		//读取状态寄存器 
void SPI_FLASH_Write_SR(uint8_t sr);  			//写状态寄存器
void SPI_FLASH_Write_Enable(void);  		//写使能 
void SPI_FLASH_Write_Disable(void);		//写保护
void SPI_FLASH_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //读取flash
void SPI_FLASH_BufferWrite(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//写入flash
void SPI_FLASH_Erase_Chip(void);    	  	//整片擦除
void SPI_FLASH_SectorErase(uint32_t SectorAddr);	//扇区擦除
void SPI_FLASH_Wait_Busy(void);           	//等待空闲
void SPI_FLASH_PowerDown(void);        	//进入掉电模式
void SPI_FLASH_WAKEUP(void);				//唤醒

#endif /* __SPI_FLASH_H */

