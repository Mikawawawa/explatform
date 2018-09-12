#include "bsp.h"

#if	(__USE_DRIVER_TOUCH)

void CT_Delay(void)
{
	bsp_delay_us(2);
}

void CT_IIC_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOF,ENABLE); //开启GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //PB1引脚设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //GPIOB1设置
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PF9引脚设置
	GPIO_Init(GPIOF,&GPIO_InitStructure); //GPIOF9设置
	
	IIC_SCL = 1;
	IIC_SDA_OUT = 1;
}

void CT_IIC_Start(void)
{
	SET_SDA_OUT();
	IIC_SDA_OUT = 1;  	  
	IIC_SCL = 1;
	bsp_delay_us(30);
	IIC_SDA_OUT = 0;
	CT_Delay();
	IIC_SCL = 0;
}	  

void CT_IIC_Stop(void)
{
	SET_SDA_OUT();
	IIC_SCL = 1;
	bsp_delay_us(30);
	IIC_SDA_OUT = 0;
	CT_Delay();
	IIC_SDA_OUT = 1;
}

uint8_t CT_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SET_SDA_IN();
	IIC_SDA_OUT = 1;
	IIC_SCL = 1;
	CT_Delay();
	while(IIC_SDA_IN)
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			CT_IIC_Stop();
			return 1;
		}
		CT_Delay();
	}
	IIC_SCL = 0;
	return 0;  
}

void CT_IIC_Ack(void)
{
	IIC_SCL = 0;
	SET_SDA_OUT();
	CT_Delay();
	IIC_SDA_OUT = 0;
	CT_Delay();
	IIC_SCL = 1;
	CT_Delay();
	IIC_SCL = 0;
}

void CT_IIC_NAck(void)
{
	IIC_SCL = 0;
	SET_SDA_OUT();
	CT_Delay();
	IIC_SDA_OUT = 1;
	CT_Delay();
	IIC_SCL = 1;
	CT_Delay();
	IIC_SCL = 0;
}					 				     

void CT_IIC_Send_Byte(uint8_t byte)
{                        
	uint8_t bit_ctrl;
	SET_SDA_OUT(); 	    
	IIC_SCL = 0;
	CT_Delay();
	for(bit_ctrl = 0; bit_ctrl < 8; bit_ctrl++) {
		IIC_SDA_OUT = (byte & 0x80) >> 7;
		byte <<= 1;
		IIC_SCL = 1;
		CT_Delay();
		IIC_SCL = 0;
		CT_Delay();
	}
}

u8 CT_IIC_Read_Byte(uint8_t ack)
{
	uint8_t bit_ctrl, byte = 0;
	
 	SET_SDA_IN();
	bsp_delay_us(30);
	for(bit_ctrl = 0; bit_ctrl < 8; bit_ctrl++) {
		IIC_SCL = 0;
		CT_Delay();
		IIC_SCL = 1;
		byte <<= 1;
		if(IIC_SDA_IN)
			byte++;
	}
	if (!ack)
		CT_IIC_NAck();
	else CT_IIC_Ack();
		
 	return byte;
	
}

#endif
