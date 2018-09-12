#include "bsp.h"

#if	(__USE_SPI_FLASH)

uint16_t SPI_FLASH_TYPE = W25Q128;

static void SPI_FLASH_WaitBusy(void);
static void SPI_FLASH_SectorErase(uint32_t Dst_Addr);

static uint8_t SPI_FLASH_BUFFER[4096];


/**
 * 4KbytesΪһ��Sector
 * 16������Ϊ1��Block
 * W25Q128
 * ����Ϊ16M�ֽ�,����128��Block,4096��Sector
 */

/**
 * @brief  ʹ��SPI����һ���ֽڵ�����
 * @param  byte��Ҫ���͵�����
 * @retval ���ؽ��յ�������
 */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{

    /* �ȴ����ͻ�����Ϊ�գ�TXE�¼� */
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

    /* д�����ݼĴ�������Ҫд�������д�뷢�ͻ����� */
    SPI_I2S_SendData(FLASH_SPI, byte);

    /* �ȴ����ջ������ǿգ�RXNE�¼� */
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

    /* ��ȡ���ݼĴ�������ȡ���ջ��������� */
    return SPI_I2S_ReceiveData(FLASH_SPI);
}

/**
 * @brief  SPI_FLASH��ʼ��
 * @param  ��
 * @retval ��
 */
void SPI_FLASH_Init(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* ʹ�� FLASH_SPI ��GPIO ʱ�� */
    /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO,
         SPI_FLASH_SPI_MISO_GPIO,SPI_FLASH_SPI_SCK_GPIO ʱ��ʹ�� */
    RCC_AHB1PeriphClockCmd (FLASH_SPI_SCK_GPIO_CLK | FLASH_SPI_MISO_GPIO_CLK | FLASH_SPI_MOSI_GPIO_CLK | FLASH_CS_GPIO_CLK, ENABLE);

    /*!< SPI_FLASH_SPI ʱ��ʹ�� */
    FLASH_SPI_CLK_INIT(FLASH_SPI_CLK, ENABLE);

    //�������Ÿ���
    GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT, FLASH_SPI_SCK_PINSOURCE, FLASH_SPI_SCK_AF);
    GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT, FLASH_SPI_MISO_PINSOURCE, FLASH_SPI_MISO_AF);
    GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT, FLASH_SPI_MOSI_PINSOURCE, FLASH_SPI_MOSI_AF);

    /*!< ���� SPI_FLASH_SPI ����: SCK */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /*!< ���� SPI_FLASH_SPI ����: MISO */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
    GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /*!< ���� SPI_FLASH_SPI ����: MOSI */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
    GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /*!< ���� SPI_FLASH_SPI ����: CS */
    GPIO_InitStructure.GPIO_Pin = FLASH_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStructure);

    /* ֹͣ�ź� FLASH: CS���Ÿߵ�ƽ*/
    SPI_FLASH_CS_HIGH();

    /* FLASH_SPI ģʽ���� */
    // FLASHоƬ ֧��SPIģʽ0��ģʽ3���ݴ�����CPOL CPHA
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(FLASH_SPI, &SPI_InitStructure);

    /* ʹ�� FLASH_SPI  */
    SPI_Cmd(FLASH_SPI, ENABLE);

}

/**
 * ��ȡW25QXX��״̬�Ĵ���
 * BIT7  6   5   4   3   2   1   0
 * SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 * SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
 * TB,BP2,BP1,BP0:FLASH����д��������
 * WEL:дʹ������
 * BUSY:æ���λ(1��æ;	0������)
 * Ĭ��:0x00
 */
uint8_t SPI_FLASH_ReadSR(void)
{
    uint8_t byte = 0;
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ReadStatusReg);
    byte = SPI_FLASH_SendByte(0xFF);
    SPI_FLASH_CS_HIGH();
    return byte;
}

/**
 * дW25QXX״̬�Ĵ���
 * ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
 */
void SPI_FLASH_Write_SR(uint8_t sr)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_WriteStatusReg);
    SPI_FLASH_SendByte(sr);
    SPI_FLASH_CS_HIGH();
}
/**
 * W25QXXдʹ��
 * ��WEL��λ
 */
void SPI_FLASH_Write_Enable(void)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_WriteEnable);
    SPI_FLASH_CS_HIGH();
}
/**
 * W25QXXд��ֹ
 * ��WEL����
 */
void SPI_FLASH_Write_Disable(void)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_WriteDisable);
    SPI_FLASH_CS_HIGH();
}
/**
 * ��ȡоƬID
 * ����ֵ����:
 * 0XEF13,��ʾоƬ�ͺ�ΪW25Q80
 * 0XEF14,��ʾоƬ�ͺ�ΪW25Q16
 * 0XEF15,��ʾоƬ�ͺ�ΪW25Q32
 * 0XEF16,��ʾоƬ�ͺ�ΪW25Q64
 * 0XEF17,��ʾоƬ�ͺ�ΪW25Q128
 */
uint16_t SPI_FLASH_ReadID(void)
{
    uint16_t Temp = 0;
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(0x90);
    SPI_FLASH_SendByte(0x00);
    SPI_FLASH_SendByte(0x00);
    SPI_FLASH_SendByte(0x00);
    Temp |= SPI_FLASH_SendByte(0xFF) << 8;
    Temp |= SPI_FLASH_SendByte(0xFF);
    SPI_FLASH_CS_HIGH();
    return Temp;
}
/**
 * ��ȡSPI FLASH
 * ��ָ����ַ��ʼ��ȡָ�����ȵ�����
 * pBuffer:���ݴ洢��
 * ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
 * NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
 */
void SPI_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint16_t i;

    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ReadData);
    SPI_FLASH_SendByte((uint8_t)((ReadAddr) >> 16));
    SPI_FLASH_SendByte((uint8_t)((ReadAddr) >> 8));
    SPI_FLASH_SendByte((uint8_t)ReadAddr);
    for(i = 0; i < NumByteToRead; i++)
    {
        pBuffer[i] = SPI_FLASH_SendByte(0xFF);
			//printf("%d ",pBuffer[i]);
    }
    SPI_FLASH_CS_HIGH();

}
/**
 * SPI��һҳ(0~65535)��д������256���ֽڵ�����
 * ��ָ����ַ��ʼд�����256�ֽڵ�����
 * pBuffer:���ݴ洢��
 * WriteAddr:��ʼд��ĵ�ַ(24bit)
 *NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
 */
void SPI_FLASH_Write_Page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t i;
    SPI_FLASH_Write_Enable();
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_PageProgram);
    SPI_FLASH_SendByte((uint8_t)((WriteAddr) >> 16));
    SPI_FLASH_SendByte((uint8_t)((WriteAddr) >> 8));
    SPI_FLASH_SendByte((uint8_t)WriteAddr);
    for(i = 0; i < NumByteToWrite; i++)SPI_FLASH_SendByte(pBuffer[i]);
    SPI_FLASH_CS_HIGH();
    SPI_FLASH_WaitBusy();
}
/**
 * �޼���дSPI FLASH
 * ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0xFF,�����ڷ�0xFF��д������ݽ�ʧ��!
 * �����Զ���ҳ����
 * ��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
 * pBuffer:���ݴ洢��
 * WriteAddr:��ʼд��ĵ�ַ(24bit)
 * NumByteToWrite:Ҫд����ֽ���(���65535)
 */
void SPI_FLASH_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pageremain;
    pageremain = 256 - WriteAddr % 256;
    if(NumByteToWrite <= pageremain)pageremain = NumByteToWrite;
    while(1)
    {
        SPI_FLASH_Write_Page(pBuffer, WriteAddr, pageremain);
        if(NumByteToWrite == pageremain)break;
        else
        {
            pBuffer += pageremain;
            WriteAddr += pageremain;

            NumByteToWrite -= pageremain;
            if(NumByteToWrite > 256)pageremain = 256;
            else pageremain = NumByteToWrite;
        }
    };
}
/**
 * дSPI FLASH
 * ��ָ����ַ��ʼд��ָ�����ȵ�����
 * �ú�������������!
 * pBuffer:���ݴ洢��
 * WriteAddr:��ʼд��ĵ�ַ(24bit)
 * NumByteToWrite:Ҫд����ֽ���(���65535)
*/

void SPI_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *SPI_FLASH_BUF = SPI_FLASH_BUFFER;

    secpos = WriteAddr / 4096;
    secoff = WriteAddr % 4096;
    secremain = 4096 - secoff;
    if(NumByteToWrite <= secremain)secremain = NumByteToWrite;

    while(1)
    {
        SPI_FLASH_BufferRead(SPI_FLASH_BUF, secpos * 4096, 4096);
        for(i = 0; i < secremain; i++)
        {
            if(SPI_FLASH_BUF[secoff + i] != 0xFF)break;
        }
        if(i < secremain)
        {
            SPI_FLASH_SectorErase(secpos);
            for(i = 0; i < secremain; i++)
            {
                SPI_FLASH_BUF[i + secoff] = pBuffer[i];
            }
            SPI_FLASH_Write_NoCheck(SPI_FLASH_BUF, secpos * 4096, 4096);

        }
        else SPI_FLASH_Write_NoCheck(pBuffer, WriteAddr, secremain);
        if(NumByteToWrite == secremain)break;
        else
        {
            secpos++;
            secoff = 0;

            pBuffer += secremain;
            WriteAddr += secremain;
            NumByteToWrite -= secremain;
            if(NumByteToWrite > 4096)secremain = 4096;
            else secremain = NumByteToWrite;
        }
    }

}
/**
 * ��������оƬ
 * �ȴ�ʱ�䳬��...
 */
void SPI_FLASH_Erase_Chip(void)
{
    SPI_FLASH_Write_Enable();
    SPI_FLASH_WaitBusy();
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ChipErase);
    SPI_FLASH_CS_HIGH();
    SPI_FLASH_WaitBusy();
}
/**
 * ����һ������
 * Dst_Addr:������ַ ����ʵ����������
 * ����һ������������ʱ��:150ms
 */
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
    SectorAddr *= 4096;
    SPI_FLASH_Write_Enable();
    SPI_FLASH_WaitBusy();
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_SectorErase);
    SPI_FLASH_SendByte((uint8_t)((SectorAddr) >> 16));
    SPI_FLASH_SendByte((uint8_t)((SectorAddr) >> 8));
    SPI_FLASH_SendByte((uint8_t)SectorAddr);
    SPI_FLASH_CS_HIGH();
    SPI_FLASH_WaitBusy();
}

/* �������ģʽ */
void SPI_FLASH_PowerDown(void)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_PowerDown);
    SPI_FLASH_CS_HIGH();
    bsp_delay_us(3);
}

/* ���� */
void SPI_FLASH_WAKEUP(void)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ReleasePowerDown);
    SPI_FLASH_CS_HIGH();
    bsp_delay_us(3);
}

/* �ȴ����� */
static void SPI_FLASH_WaitBusy(void)
{
    while((SPI_FLASH_ReadSR() & 0x01) == 0x01);
}

#endif

