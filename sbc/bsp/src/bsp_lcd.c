/*
*********************************************************************************************************
*
*	模块名称 : TFT液晶显示器驱动模块
*	文件名称 : bsp_tft_lcd.c
*	版    本 : V3.4
*	说    明 :
*	修改记录 :
*		版本号  日期       作者    说明
*
*********************************************************************************************************
*/

#include "bsp.h"

#if	(__USE_DRIVER_LCD)

static uint16_t read_id(void);
static void init(void);
static void open(void);
static void close(void);
static void set_backlight(uint8_t pwm);
static void set_cursor(uint16_t _usX, uint16_t _usY);
static void set_window(uint16_t _usX0, uint16_t _usY0, uint16_t _usX1, uint16_t _usY1);
static void clear(uint16_t _usColor);
static void put_pixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor);
static void put_pixel_gui(uint16_t _usX, uint16_t _usY, uint16_t _usColor);
static uint16_t get_pixel(uint16_t _usX, uint16_t _usY);
static uint16_t get_pixel_gui(uint16_t _usX, uint16_t _usY);
static void draw_line(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint16_t _usColor);
static void draw_H_colorLine(uint16_t _usX , uint16_t _usY, uint16_t _usWidth, uint16_t *_pColor);
static void draw_H_line(uint16_t _usX0 , uint16_t _usY , uint16_t _usX1 , uint16_t _usColor);
static void draw_V_line(uint16_t _usX , uint16_t _usY0 , uint16_t _usY1 , uint16_t _usColor);
static void draw_circle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);
static void draw_rect(uint16_t _usX, uint16_t _usY, uint8_t _ucHeight, uint16_t _usWidth, uint16_t _usColor);
static void fill_rect(uint16_t _usX0, uint16_t _usY0, uint16_t _usX1, uint16_t _usY1, uint16_t _usColor);


bsp_lcd_struct lcd = {
	0u,
	{0u,0u,0u,0u},
	
	init,
	open,
	close,
  set_backlight,
  set_cursor,
  set_window,
  clear,
	put_pixel,
  put_pixel_gui,
	get_pixel,
  get_pixel_gui,
  draw_line,
  draw_H_colorLine,
  draw_H_line,
  draw_V_line,
	draw_circle,
  draw_rect,
  fill_rect
};

static void write_command(uint16_t cmd)
{
	cmd = cmd;
	LCD->REG = cmd;
}

static void write_ram(uint16_t ram)
{
	ram = ram;
	LCD->RAM = ram;
}

static uint16_t read_ram(void)
{
	__IO uint16_t ram = 0;
	ram = LCD->RAM;
	return ram;
}

static void write_reg(u16 reg, u16 value)
{	
	LCD->REG = reg;		//写入要写的寄存器序号	 
	LCD->RAM = value;//写入数据	    		 
}	   

static u16 read_reg(u16 reg)
{										   
	write_command(reg);		//写入要读的寄存器序号
	bsp_delay_us(5);		  
	return read_ram();		//返回读到的值
} 

/*
*********************************************************************************************************
*	函 数 名: control_lines_config
*	功能说明: 配置LCD控制口线，FMC管脚设置为复用功能
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void control_lines_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);
	
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);

	/* 配置FMC复用映射 */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FMC);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FMC);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_FMC);

	/* 配置FMC对应引脚为复用映射、推挽输出模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
	                              GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
	                              GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                              GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                              GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* 配置LCD背光控制引脚 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
*********************************************************************************************************
*	函 数 名: FMC_config
*	功能说明: 配置FMC并口访问时序
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void FMC_config(void)
{
	FMC_NORSRAMInitTypeDef  FMC_NORSRAMInitStructure;
	FMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FMC_NORSRAMTimingInitTypeDef  writeTiming;
	
//	FMC_NORSRAMStructInit(&FMC_NORSRAMInitStructure);


	readWriteTiming.FMC_AddressSetupTime = 0XF;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
	readWriteTiming.FMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
	readWriteTiming.FMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
	readWriteTiming.FMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FMC_CLKDivision = 0x00;
	readWriteTiming.FMC_DataLatency = 0x00;
	readWriteTiming.FMC_AccessMode = FMC_AccessMode_A;	 //模式A 
    

	writeTiming.FMC_AddressSetupTime =9;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
	writeTiming.FMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
	writeTiming.FMC_DataSetupTime = 8;		 //数据保存时间为6ns*9个HCLK=54ns
	writeTiming.FMC_BusTurnAroundDuration = 0x00;
	writeTiming.FMC_CLKDivision = 0x00;
	writeTiming.FMC_DataLatency = 0x00;
	writeTiming.FMC_AccessMode = FMC_AccessMode_A;	 //模式A 


	FMC_NORSRAMInitStructure.FMC_Bank = FMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
	FMC_NORSRAMInitStructure.FMC_DataAddressMux = FMC_DataAddressMux_Disable; // 不复用数据地址
	FMC_NORSRAMInitStructure.FMC_MemoryType =FMC_MemoryType_SRAM;// FMC_MemoryType_SRAM;  //SRAM   
	FMC_NORSRAMInitStructure.FMC_MemoryDataWidth = FMC_NORSRAM_MemoryDataWidth_16b;//存储器数据宽度为16bit   
	FMC_NORSRAMInitStructure.FMC_BurstAccessMode =FMC_BurstAccessMode_Disable;// FMC_BurstAccessMode_Disable; 
	FMC_NORSRAMInitStructure.FMC_WaitSignalPolarity = FMC_WaitSignalPolarity_Low;
	FMC_NORSRAMInitStructure.FMC_AsynchronousWait=FMC_AsynchronousWait_Disable; 
	FMC_NORSRAMInitStructure.FMC_WrapMode = FMC_WrapMode_Disable;   
	FMC_NORSRAMInitStructure.FMC_WaitSignalActive = FMC_WaitSignalActive_BeforeWaitState;  
	FMC_NORSRAMInitStructure.FMC_WriteOperation = FMC_WriteOperation_Enable;	//  存储器写使能
	FMC_NORSRAMInitStructure.FMC_WaitSignal = FMC_WaitSignal_Disable;   
	FMC_NORSRAMInitStructure.FMC_ExtendedMode = FMC_ExtendedMode_Enable; // 读写使用不同的时序
	FMC_NORSRAMInitStructure.FMC_WriteBurst = FMC_WriteBurst_Disable; 
	FMC_NORSRAMInitStructure.FMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
	FMC_NORSRAMInitStructure.FMC_WriteTimingStruct = &writeTiming;  //写时序

	FMC_NORSRAMInit(&FMC_NORSRAMInitStructure);  //初始化FMC配置

	FMC_NORSRAMCmd(FMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
}

static void init(void)
{

	/* 配置LCD控制口线GPIO */
	control_lines_config();

	/* 配置FMC接口，数据总线 */
	FMC_config();

	/* FMC重置后必须加延迟才能访问总线设备  */
	bsp_delay_ms(50);
	write_reg(0x0000,0x0001);
	bsp_delay_ms(50);

	/* 读取产品ID，若ID不符则结束初始化 */
	lcd.id = read_id();
		if(lcd.id<0XFF||lcd.id==0XFFFF||lcd.id==0X9300)//读到ID不正确,新增lcd.id==0X9300判断，因为9341在未被复位的情况下会被读成9300
	{	
 		//尝试9341 ID的读取		
		write_command(0XD3);				   
		lcd.id=read_ram();	//dummy read 	
 		lcd.id=read_ram();	//读到0X00
  		lcd.id=read_ram();   	//读取93								   
 		lcd.id<<=8;
		lcd.id|=read_ram();  	//读取41 	   			   
 		if(lcd.id!=0X9341)		//非9341,尝试是不是6804
		{	
 			write_command(0XBF);				   
			lcd.id=read_ram(); 	//dummy read 	 
	 		lcd.id=read_ram();   	//读回0X01			   
	 		lcd.id=read_ram(); 	//读回0XD0 			  	
	  		lcd.id=read_ram();	//这里读回0X68 
			lcd.id<<=8;
	  		lcd.id|=read_ram();	//这里读回0X04	  
			if(lcd.id!=0X6804)		//也不是6804,尝试看看是不是NT35310
			{ 
				write_command(0XD4);				   
				lcd.id=read_ram();//dummy read  
				lcd.id=read_ram();//读回0X01	 
				lcd.id=read_ram();//读回0X53	
				lcd.id<<=8;	 
				lcd.id|=read_ram();	//这里读回0X10	 
				if(lcd.id!=0X5310)		//也不是NT35310,尝试看看是不是NT35510
				{
					write_command(0XDA00);	
					lcd.id=read_ram();		//读回0X00	 
					write_command(0XDB00);	
					lcd.id=read_ram();		//读回0X80
					lcd.id<<=8;	
					write_command(0XDC00);	
					lcd.id|=read_ram();		//读回0X00		
					if(lcd.id==0x8000)lcd.id=0x5510;//NT35510读回的ID是8000H,为方便区分,我们强制设置为5510
					if(lcd.id!=0X5510)			//也不是NT5510,尝试看看是不是LCD1963
					{
						write_command(0XA1);
						lcd.id=read_ram();
						lcd.id=read_ram();	//读回0X57
						lcd.id<<=8;	 
						lcd.id|=read_ram();	//读回0X61	
						if(lcd.id==0X5761)lcd.id=0X1963;//LCD1963读回的ID是5761H,为方便区分,我们强制设置为1963
					}
				}
			}
 		}  	
	} 
	if(lcd.id==0X9341||lcd.id==0X5310||lcd.id==0X5510||lcd.id==0X1963)//如果是这几个IC,则设置WR时序为最快
	{
		//重新配置写时序控制寄存器的时序   	 							    
		FMC_Bank1E->BWTR[6]&=~(0XF<<0);//地址建立时间(ADDSET)清零 	 
		FMC_Bank1E->BWTR[6]&=~(0XF<<8);//数据保存时间清零
		FMC_Bank1E->BWTR[6]|=3<<0;		//地址建立时间(ADDSET)为3个HCLK =18ns  	 
		FMC_Bank1E->BWTR[6]|=2<<8; 	//数据保存时间(DATAST)为6ns*3个HCLK=18ns
	}else if(lcd.id==0X6804||lcd.id==0XC505)	//6804/C505速度上不去,得降低
	{
		//重新配置写时序控制寄存器的时序   	 							    
		FMC_Bank1E->BWTR[6]&=~(0XF<<0);//地址建立时间(ADDSET)清零 	 
		FMC_Bank1E->BWTR[6]&=~(0XF<<8);//数据保存时间清零
		FMC_Bank1E->BWTR[6]|=10<<0;	//地址建立时间(ADDSET)为10个HCLK =60ns  	 
		FMC_Bank1E->BWTR[6]|=12<<8; 	//数据保存时间(DATAST)为6ns*13个HCLK=78ns
	}
 
	if(lcd.id==0X9341)	//9341初始化
	{	 
		write_command(0xCF);  
		write_ram(0x00); 
		write_ram(0xC1); 
		write_ram(0X30); 
		write_command(0xED);  
		write_ram(0x64); 
		write_ram(0x03); 
		write_ram(0X12); 
		write_ram(0X81); 
		write_command(0xE8);  
		write_ram(0x85); 
		write_ram(0x10); 
		write_ram(0x7A); 
		write_command(0xCB);  
		write_ram(0x39); 
		write_ram(lcd.command.write_gram); 
		write_ram(0x00); 
		write_ram(0x34); 
		write_ram(0x02); 
		write_command(0xF7);  
		write_ram(0x20); 
		write_command(0xEA);  
		write_ram(0x00); 
		write_ram(0x00); 
		write_command(0xC0);    //Power control 
		write_ram(0x1B);   //VRH[5:0] 
		write_command(0xC1);    //Power control 
		write_ram(0x01);   //SAP[2:0];BT[3:0] 
		write_command(0xC5);    //VCM control 
		write_ram(0x30); 	 //3F
		write_ram(0x30); 	 //3C
		write_command(0xC7);    //VCM control2 
		write_ram(0XB7); 
		write_command(0x36);    // Memory Access Control 
		write_ram(0x48); 
		write_command(0x3A);   
		write_ram(0x55); 
		write_command(0xB1);   
		write_ram(0x00);   
		write_ram(0x1A); 
		write_command(0xB6);    // Display Function Control 
		write_ram(0x0A); 
		write_ram(0xA2); 
		write_command(0xF2);    // 3Gamma Function Disable 
		write_ram(0x00); 
		write_command(0x26);    //Gamma curve selected 
		write_ram(0x01); 
		write_command(0xE0);    //Set Gamma 
		write_ram(0x0F); 
		write_ram(0x2A); 
		write_ram(0x28); 
		write_ram(0x08); 
		write_ram(0x0E); 
		write_ram(0x08); 
		write_ram(0x54); 
		write_ram(0XA9); 
		write_ram(0x43); 
		write_ram(0x0A); 
		write_ram(0x0F); 
		write_ram(0x00); 
		write_ram(0x00); 
		write_ram(0x00); 
		write_ram(0x00); 		 
		write_command(0XE1);    //Set Gamma 
		write_ram(0x00); 
		write_ram(0x15); 
		write_ram(0x17); 
		write_ram(0x07); 
		write_ram(0x11); 
		write_ram(0x06); 
		write_ram(0x2B); 
		write_ram(0x56); 
		write_ram(0x3C); 
		write_ram(0x05); 
		write_ram(0x10); 
		write_ram(0x0F); 
		write_ram(0x3F); 
		write_ram(0x3F); 
		write_ram(0x0F); 
		write_command(0x2B); 
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x01);
		write_ram(0x3f);
		write_command(0x2A); 
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0xef);	 
		write_command(0x11); //Exit Sleep
		bsp_delay_ms(120);
		write_command(0x29); //display on	
	}else if(lcd.id==0x6804) //6804初始化
	{
		write_command(0X11);
		bsp_delay_ms(20);
		write_command(0XD0);//VCI1  VCL  VGH  VGL DDVDH VREG1OUT power amplitude setting
		write_ram(0X07); 
		write_ram(0X42); 
		write_ram(0X1D); 
		write_command(0XD1);//VCOMH VCOM_AC amplitude setting
		write_ram(0X00);
		write_ram(0X1a);
		write_ram(0X09); 
		write_command(0XD2);//Operational Amplifier Circuit Constant Current Adjust , charge pump frequency setting
		write_ram(0X01);
		write_ram(0X22);
		write_command(0XC0);//REV SM GS 
		write_ram(0X10);
		write_ram(0X3B);
		write_ram(0X00);
		write_ram(0X02);
		write_ram(0X11);
		
		write_command(0XC5);// Frame rate setting = 72HZ  when setting 0x03
		write_ram(0X03);
		
		write_command(0XC8);//Gamma setting
		write_ram(0X00);
		write_ram(0X25);
		write_ram(0X21);
		write_ram(0X05);
		write_ram(0X00);
		write_ram(0X0a);
		write_ram(0X65);
		write_ram(0X25);
		write_ram(0X77);
		write_ram(0X50);
		write_ram(0X0f);
		write_ram(0X00);	  
						  
   		write_command(0XF8);
		write_ram(0X01);	  

 		write_command(0XFE);
 		write_ram(0X00);
 		write_ram(0X02);
		
		write_command(0X20);//Exit invert mode

		write_command(0X36);
		write_ram(0X08);//原来是a
		
		write_command(0X3A);
		write_ram(0X55);//16位模式	  
		write_command(0X2B);
		write_ram(0X00);
		write_ram(0X00);
		write_ram(0X01);
		write_ram(0X3F);
		
		write_command(0X2A);
		write_ram(0X00);
		write_ram(0X00);
		write_ram(0X01);
		write_ram(0XDF);
		bsp_delay_ms(120);
		write_command(0X29); 	 
 	}else if(lcd.id==0x5310)
	{ 
		write_command(0xED);
		write_ram(0x01);
		write_ram(0xFE);

		write_command(0xEE);
		write_ram(0xDE);
		write_ram(0x21);

		write_command(0xF1);
		write_ram(0x01);
		write_command(0xDF);
		write_ram(0x10);

		//VCOMvoltage//
		write_command(0xC4);
		write_ram(0x8F);	  //5f

		write_command(0xC6);
		write_ram(0x00);
		write_ram(0xE2);
		write_ram(0xE2);
		write_ram(0xE2);
		write_command(0xBF);
		write_ram(0xAA);

		write_command(0xB0);
		write_ram(0x0D);
		write_ram(0x00);
		write_ram(0x0D);
		write_ram(0x00);
		write_ram(0x11);
		write_ram(0x00);
		write_ram(0x19);
		write_ram(0x00);
		write_ram(0x21);
		write_ram(0x00);
		write_ram(0x2D);
		write_ram(0x00);
		write_ram(0x3D);
		write_ram(0x00);
		write_ram(0x5D);
		write_ram(0x00);
		write_ram(0x5D);
		write_ram(0x00);

		write_command(0xB1);
		write_ram(0x80);
		write_ram(0x00);
		write_ram(0x8B);
		write_ram(0x00);
		write_ram(0x96);
		write_ram(0x00);

		write_command(0xB2);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x02);
		write_ram(0x00);
		write_ram(0x03);
		write_ram(0x00);

		write_command(0xB3);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xB4);
		write_ram(0x8B);
		write_ram(0x00);
		write_ram(0x96);
		write_ram(0x00);
		write_ram(0xA1);
		write_ram(0x00);

		write_command(0xB5);
		write_ram(0x02);
		write_ram(0x00);
		write_ram(0x03);
		write_ram(0x00);
		write_ram(0x04);
		write_ram(0x00);

		write_command(0xB6);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xB7);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x3F);
		write_ram(0x00);
		write_ram(0x5E);
		write_ram(0x00);
		write_ram(0x64);
		write_ram(0x00);
		write_ram(0x8C);
		write_ram(0x00);
		write_ram(0xAC);
		write_ram(0x00);
		write_ram(0xDC);
		write_ram(0x00);
		write_ram(0x70);
		write_ram(0x00);
		write_ram(0x90);
		write_ram(0x00);
		write_ram(0xEB);
		write_ram(0x00);
		write_ram(0xDC);
		write_ram(0x00);

		write_command(0xB8);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xBA);
		write_ram(0x24);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xC1);
		write_ram(0x20);
		write_ram(0x00);
		write_ram(0x54);
		write_ram(0x00);
		write_ram(0xFF);
		write_ram(0x00);

		write_command(0xC2);
		write_ram(0x0A);
		write_ram(0x00);
		write_ram(0x04);
		write_ram(0x00);

		write_command(0xC3);
		write_ram(0x3C);
		write_ram(0x00);
		write_ram(0x3A);
		write_ram(0x00);
		write_ram(0x39);
		write_ram(0x00);
		write_ram(0x37);
		write_ram(0x00);
		write_ram(0x3C);
		write_ram(0x00);
		write_ram(0x36);
		write_ram(0x00);
		write_ram(0x32);
		write_ram(0x00);
		write_ram(0x2F);
		write_ram(0x00);
		write_ram(lcd.command.write_gram);
		write_ram(0x00);
		write_ram(0x29);
		write_ram(0x00);
		write_ram(0x26);
		write_ram(0x00);
		write_ram(0x24);
		write_ram(0x00);
		write_ram(0x24);
		write_ram(0x00);
		write_ram(0x23);
		write_ram(0x00);
		write_ram(0x3C);
		write_ram(0x00);
		write_ram(0x36);
		write_ram(0x00);
		write_ram(0x32);
		write_ram(0x00);
		write_ram(0x2F);
		write_ram(0x00);
		write_ram(lcd.command.write_gram);
		write_ram(0x00);
		write_ram(0x29);
		write_ram(0x00);
		write_ram(0x26);
		write_ram(0x00);
		write_ram(0x24);
		write_ram(0x00);
		write_ram(0x24);
		write_ram(0x00);
		write_ram(0x23);
		write_ram(0x00);

		write_command(0xC4);
		write_ram(0x62);
		write_ram(0x00);
		write_ram(0x05);
		write_ram(0x00);
		write_ram(0x84);
		write_ram(0x00);
		write_ram(0xF0);
		write_ram(0x00);
		write_ram(0x18);
		write_ram(0x00);
		write_ram(0xA4);
		write_ram(0x00);
		write_ram(0x18);
		write_ram(0x00);
		write_ram(0x50);
		write_ram(0x00);
		write_ram(0x0C);
		write_ram(0x00);
		write_ram(0x17);
		write_ram(0x00);
		write_ram(0x95);
		write_ram(0x00);
		write_ram(0xF3);
		write_ram(0x00);
		write_ram(0xE6);
		write_ram(0x00);

		write_command(0xC5);
		write_ram(0x32);
		write_ram(0x00);
		write_ram(0x44);
		write_ram(0x00);
		write_ram(0x65);
		write_ram(0x00);
		write_ram(0x76);
		write_ram(0x00);
		write_ram(0x88);
		write_ram(0x00);

		write_command(0xC6);
		write_ram(0x20);
		write_ram(0x00);
		write_ram(0x17);
		write_ram(0x00);
		write_ram(0x01);
		write_ram(0x00);

		write_command(0xC7);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xC8);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xC9);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xE0);
		write_ram(0x16);
		write_ram(0x00);
		write_ram(0x1C);
		write_ram(0x00);
		write_ram(0x21);
		write_ram(0x00);
		write_ram(0x36);
		write_ram(0x00);
		write_ram(0x46);
		write_ram(0x00);
		write_ram(0x52);
		write_ram(0x00);
		write_ram(0x64);
		write_ram(0x00);
		write_ram(0x7A);
		write_ram(0x00);
		write_ram(0x8B);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0xA8);
		write_ram(0x00);
		write_ram(0xB9);
		write_ram(0x00);
		write_ram(0xC4);
		write_ram(0x00);
		write_ram(0xCA);
		write_ram(0x00);
		write_ram(0xD2);
		write_ram(0x00);
		write_ram(0xD9);
		write_ram(0x00);
		write_ram(0xE0);
		write_ram(0x00);
		write_ram(0xF3);
		write_ram(0x00);

		write_command(0xE1);
		write_ram(0x16);
		write_ram(0x00);
		write_ram(0x1C);
		write_ram(0x00);
		write_ram(0x22);
		write_ram(0x00);
		write_ram(0x36);
		write_ram(0x00);
		write_ram(0x45);
		write_ram(0x00);
		write_ram(0x52);
		write_ram(0x00);
		write_ram(0x64);
		write_ram(0x00);
		write_ram(0x7A);
		write_ram(0x00);
		write_ram(0x8B);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0xA8);
		write_ram(0x00);
		write_ram(0xB9);
		write_ram(0x00);
		write_ram(0xC4);
		write_ram(0x00);
		write_ram(0xCA);
		write_ram(0x00);
		write_ram(0xD2);
		write_ram(0x00);
		write_ram(0xD8);
		write_ram(0x00);
		write_ram(0xE0);
		write_ram(0x00);
		write_ram(0xF3);
		write_ram(0x00);

		write_command(0xE2);
		write_ram(0x05);
		write_ram(0x00);
		write_ram(0x0B);
		write_ram(0x00);
		write_ram(0x1B);
		write_ram(0x00);
		write_ram(0x34);
		write_ram(0x00);
		write_ram(0x44);
		write_ram(0x00);
		write_ram(0x4F);
		write_ram(0x00);
		write_ram(0x61);
		write_ram(0x00);
		write_ram(0x79);
		write_ram(0x00);
		write_ram(0x88);
		write_ram(0x00);
		write_ram(0x97);
		write_ram(0x00);
		write_ram(0xA6);
		write_ram(0x00);
		write_ram(0xB7);
		write_ram(0x00);
		write_ram(0xC2);
		write_ram(0x00);
		write_ram(0xC7);
		write_ram(0x00);
		write_ram(0xD1);
		write_ram(0x00);
		write_ram(0xD6);
		write_ram(0x00);
		write_ram(0xDD);
		write_ram(0x00);
		write_ram(0xF3);
		write_ram(0x00);
		write_command(0xE3);
		write_ram(0x05);
		write_ram(0x00);
		write_ram(0xA);
		write_ram(0x00);
		write_ram(0x1C);
		write_ram(0x00);
		write_ram(0x33);
		write_ram(0x00);
		write_ram(0x44);
		write_ram(0x00);
		write_ram(0x50);
		write_ram(0x00);
		write_ram(0x62);
		write_ram(0x00);
		write_ram(0x78);
		write_ram(0x00);
		write_ram(0x88);
		write_ram(0x00);
		write_ram(0x97);
		write_ram(0x00);
		write_ram(0xA6);
		write_ram(0x00);
		write_ram(0xB7);
		write_ram(0x00);
		write_ram(0xC2);
		write_ram(0x00);
		write_ram(0xC7);
		write_ram(0x00);
		write_ram(0xD1);
		write_ram(0x00);
		write_ram(0xD5);
		write_ram(0x00);
		write_ram(0xDD);
		write_ram(0x00);
		write_ram(0xF3);
		write_ram(0x00);

		write_command(0xE4);
		write_ram(0x01);
		write_ram(0x00);
		write_ram(0x01);
		write_ram(0x00);
		write_ram(0x02);
		write_ram(0x00);
		write_ram(0x2A);
		write_ram(0x00);
		write_ram(0x3C);
		write_ram(0x00);
		write_ram(0x4B);
		write_ram(0x00);
		write_ram(0x5D);
		write_ram(0x00);
		write_ram(0x74);
		write_ram(0x00);
		write_ram(0x84);
		write_ram(0x00);
		write_ram(0x93);
		write_ram(0x00);
		write_ram(0xA2);
		write_ram(0x00);
		write_ram(0xB3);
		write_ram(0x00);
		write_ram(0xBE);
		write_ram(0x00);
		write_ram(0xC4);
		write_ram(0x00);
		write_ram(0xCD);
		write_ram(0x00);
		write_ram(0xD3);
		write_ram(0x00);
		write_ram(0xDD);
		write_ram(0x00);
		write_ram(0xF3);
		write_ram(0x00);
		write_command(0xE5);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x02);
		write_ram(0x00);
		write_ram(0x29);
		write_ram(0x00);
		write_ram(0x3C);
		write_ram(0x00);
		write_ram(0x4B);
		write_ram(0x00);
		write_ram(0x5D);
		write_ram(0x00);
		write_ram(0x74);
		write_ram(0x00);
		write_ram(0x84);
		write_ram(0x00);
		write_ram(0x93);
		write_ram(0x00);
		write_ram(0xA2);
		write_ram(0x00);
		write_ram(0xB3);
		write_ram(0x00);
		write_ram(0xBE);
		write_ram(0x00);
		write_ram(0xC4);
		write_ram(0x00);
		write_ram(0xCD);
		write_ram(0x00);
		write_ram(0xD3);
		write_ram(0x00);
		write_ram(0xDC);
		write_ram(0x00);
		write_ram(0xF3);
		write_ram(0x00);

		write_command(0xE6);
		write_ram(0x11);
		write_ram(0x00);
		write_ram(0x34);
		write_ram(0x00);
		write_ram(0x56);
		write_ram(0x00);
		write_ram(0x76);
		write_ram(0x00);
		write_ram(0x77);
		write_ram(0x00);
		write_ram(0x66);
		write_ram(0x00);
		write_ram(0x88);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0xBB);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0x66);
		write_ram(0x00);
		write_ram(0x55);
		write_ram(0x00);
		write_ram(0x55);
		write_ram(0x00);
		write_ram(0x45);
		write_ram(0x00);
		write_ram(0x43);
		write_ram(0x00);
		write_ram(0x44);
		write_ram(0x00);

		write_command(0xE7);
		write_ram(0x32);
		write_ram(0x00);
		write_ram(0x55);
		write_ram(0x00);
		write_ram(0x76);
		write_ram(0x00);
		write_ram(0x66);
		write_ram(0x00);
		write_ram(0x67);
		write_ram(0x00);
		write_ram(0x67);
		write_ram(0x00);
		write_ram(0x87);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0xBB);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0x77);
		write_ram(0x00);
		write_ram(0x44);
		write_ram(0x00);
		write_ram(0x56);
		write_ram(0x00);
		write_ram(0x23); 
		write_ram(0x00);
		write_ram(0x33);
		write_ram(0x00);
		write_ram(0x45);
		write_ram(0x00);

		write_command(0xE8);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0x87);
		write_ram(0x00);
		write_ram(0x88);
		write_ram(0x00);
		write_ram(0x77);
		write_ram(0x00);
		write_ram(0x66);
		write_ram(0x00);
		write_ram(0x88);
		write_ram(0x00);
		write_ram(0xAA);
		write_ram(0x00);
		write_ram(0xBB);
		write_ram(0x00);
		write_ram(0x99);
		write_ram(0x00);
		write_ram(0x66);
		write_ram(0x00);
		write_ram(0x55);
		write_ram(0x00);
		write_ram(0x55);
		write_ram(0x00);
		write_ram(0x44);
		write_ram(0x00);
		write_ram(0x44);
		write_ram(0x00);
		write_ram(0x55);
		write_ram(0x00);

		write_command(0xE9);
		write_ram(0xAA);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0x00);
		write_ram(0xAA);

		write_command(0xCF);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xF0);
		write_ram(0x00);
		write_ram(0x50);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);

		write_command(0xF3);
		write_ram(0x00);

		write_command(0xF9);
		write_ram(0x06);
		write_ram(0x10);
		write_ram(0x29);
		write_ram(0x00);

		write_command(0x3A);
		write_ram(0x55);	//66

		write_command(0x11);
		bsp_delay_ms(100);
		write_command(0x29);
		write_command(0x35);
		write_ram(0x00);

		write_command(0x51);
		write_ram(0xFF);
		write_command(0x53);
		write_ram(lcd.command.write_gram);
		write_command(0x55);
		write_ram(0x82);
		write_command(lcd.command.write_gram);
	}else if(lcd.id==0x5510)
	{
		write_reg(0xF000,0x55);
		write_reg(0xF001,0xAA);
		write_reg(0xF002,0x52);
		write_reg(0xF003,0x08);
		write_reg(0xF004,0x01);
		//AVDD Set AVDD 5.2V
		write_reg(0xB000,0x0D);
		write_reg(0xB001,0x0D);
		write_reg(0xB002,0x0D);
		//AVDD ratio
		write_reg(0xB600,0x34);
		write_reg(0xB601,0x34);
		write_reg(0xB602,0x34);
		//AVEE -5.2V
		write_reg(0xB100,0x0D);
		write_reg(0xB101,0x0D);
		write_reg(0xB102,0x0D);
		//AVEE ratio
		write_reg(0xB700,0x34);
		write_reg(0xB701,0x34);
		write_reg(0xB702,0x34);
		//VCL -2.5V
		write_reg(0xB200,0x00);
		write_reg(0xB201,0x00);
		write_reg(0xB202,0x00);
		//VCL ratio
		write_reg(0xB800,0x24);
		write_reg(0xB801,0x24);
		write_reg(0xB802,0x24);
		//VGH 15V (Free pump)
		write_reg(0xBF00,0x01);
		write_reg(0xB300,0x0F);
		write_reg(0xB301,0x0F);
		write_reg(0xB302,0x0F);
		//VGH ratio
		write_reg(0xB900,0x34);
		write_reg(0xB901,0x34);
		write_reg(0xB902,0x34);
		//VGL_REG -10V
		write_reg(0xB500,0x08);
		write_reg(0xB501,0x08);
		write_reg(0xB502,0x08);
		write_reg(0xC200,0x03);
		//VGLX ratio
		write_reg(0xBA00,0x24);
		write_reg(0xBA01,0x24);
		write_reg(0xBA02,0x24);
		//VGMP/VGSP 4.5V/0V
		write_reg(0xBC00,0x00);
		write_reg(0xBC01,0x78);
		write_reg(0xBC02,0x00);
		//VGMN/VGSN -4.5V/0V
		write_reg(0xBD00,0x00);
		write_reg(0xBD01,0x78);
		write_reg(0xBD02,0x00);
		//VCOM
		write_reg(0xBE00,0x00);
		write_reg(0xBE01,0x64);
		//Gamma Setting
		write_reg(0xD100,0x00);
		write_reg(0xD101,0x33);
		write_reg(0xD102,0x00);
		write_reg(0xD103,0x34);
		write_reg(0xD104,0x00);
		write_reg(0xD105,0x3A);
		write_reg(0xD106,0x00);
		write_reg(0xD107,0x4A);
		write_reg(0xD108,0x00);
		write_reg(0xD109,0x5C);
		write_reg(0xD10A,0x00);
		write_reg(0xD10B,0x81);
		write_reg(0xD10C,0x00);
		write_reg(0xD10D,0xA6);
		write_reg(0xD10E,0x00);
		write_reg(0xD10F,0xE5);
		write_reg(0xD110,0x01);
		write_reg(0xD111,0x13);
		write_reg(0xD112,0x01);
		write_reg(0xD113,0x54);
		write_reg(0xD114,0x01);
		write_reg(0xD115,0x82);
		write_reg(0xD116,0x01);
		write_reg(0xD117,0xCA);
		write_reg(0xD118,0x02);
		write_reg(0xD119,0x00);
		write_reg(0xD11A,0x02);
		write_reg(0xD11B,0x01);
		write_reg(0xD11C,0x02);
		write_reg(0xD11D,0x34);
		write_reg(0xD11E,0x02);
		write_reg(0xD11F,0x67);
		write_reg(0xD120,0x02);
		write_reg(0xD121,0x84);
		write_reg(0xD122,0x02);
		write_reg(0xD123,0xA4);
		write_reg(0xD124,0x02);
		write_reg(0xD125,0xB7);
		write_reg(0xD126,0x02);
		write_reg(0xD127,0xCF);
		write_reg(0xD128,0x02);
		write_reg(0xD129,0xDE);
		write_reg(0xD12A,0x02);
		write_reg(0xD12B,0xF2);
		write_reg(0xD12C,0x02);
		write_reg(0xD12D,0xFE);
		write_reg(0xD12E,0x03);
		write_reg(0xD12F,0x10);
		write_reg(0xD130,0x03);
		write_reg(0xD131,0x33);
		write_reg(0xD132,0x03);
		write_reg(0xD133,0x6D);
		write_reg(0xD200,0x00);
		write_reg(0xD201,0x33);
		write_reg(0xD202,0x00);
		write_reg(0xD203,0x34);
		write_reg(0xD204,0x00);
		write_reg(0xD205,0x3A);
		write_reg(0xD206,0x00);
		write_reg(0xD207,0x4A);
		write_reg(0xD208,0x00);
		write_reg(0xD209,0x5C);
		write_reg(0xD20A,0x00);

		write_reg(0xD20B,0x81);
		write_reg(0xD20C,0x00);
		write_reg(0xD20D,0xA6);
		write_reg(0xD20E,0x00);
		write_reg(0xD20F,0xE5);
		write_reg(0xD210,0x01);
		write_reg(0xD211,0x13);
		write_reg(0xD212,0x01);
		write_reg(0xD213,0x54);
		write_reg(0xD214,0x01);
		write_reg(0xD215,0x82);
		write_reg(0xD216,0x01);
		write_reg(0xD217,0xCA);
		write_reg(0xD218,0x02);
		write_reg(0xD219,0x00);
		write_reg(0xD21A,0x02);
		write_reg(0xD21B,0x01);
		write_reg(0xD21C,0x02);
		write_reg(0xD21D,0x34);
		write_reg(0xD21E,0x02);
		write_reg(0xD21F,0x67);
		write_reg(0xD220,0x02);
		write_reg(0xD221,0x84);
		write_reg(0xD222,0x02);
		write_reg(0xD223,0xA4);
		write_reg(0xD224,0x02);
		write_reg(0xD225,0xB7);
		write_reg(0xD226,0x02);
		write_reg(0xD227,0xCF);
		write_reg(0xD228,0x02);
		write_reg(0xD229,0xDE);
		write_reg(0xD22A,0x02);
		write_reg(0xD22B,0xF2);
		write_reg(0xD22C,0x02);
		write_reg(0xD22D,0xFE);
		write_reg(0xD22E,0x03);
		write_reg(0xD22F,0x10);
		write_reg(0xD230,0x03);
		write_reg(0xD231,0x33);
		write_reg(0xD232,0x03);
		write_reg(0xD233,0x6D);
		write_reg(0xD300,0x00);
		write_reg(0xD301,0x33);
		write_reg(0xD302,0x00);
		write_reg(0xD303,0x34);
		write_reg(0xD304,0x00);
		write_reg(0xD305,0x3A);
		write_reg(0xD306,0x00);
		write_reg(0xD307,0x4A);
		write_reg(0xD308,0x00);
		write_reg(0xD309,0x5C);
		write_reg(0xD30A,0x00);

		write_reg(0xD30B,0x81);
		write_reg(0xD30C,0x00);
		write_reg(0xD30D,0xA6);
		write_reg(0xD30E,0x00);
		write_reg(0xD30F,0xE5);
		write_reg(0xD310,0x01);
		write_reg(0xD311,0x13);
		write_reg(0xD312,0x01);
		write_reg(0xD313,0x54);
		write_reg(0xD314,0x01);
		write_reg(0xD315,0x82);
		write_reg(0xD316,0x01);
		write_reg(0xD317,0xCA);
		write_reg(0xD318,0x02);
		write_reg(0xD319,0x00);
		write_reg(0xD31A,0x02);
		write_reg(0xD31B,0x01);
		write_reg(0xD31C,0x02);
		write_reg(0xD31D,0x34);
		write_reg(0xD31E,0x02);
		write_reg(0xD31F,0x67);
		write_reg(0xD320,0x02);
		write_reg(0xD321,0x84);
		write_reg(0xD322,0x02);
		write_reg(0xD323,0xA4);
		write_reg(0xD324,0x02);
		write_reg(0xD325,0xB7);
		write_reg(0xD326,0x02);
		write_reg(0xD327,0xCF);
		write_reg(0xD328,0x02);
		write_reg(0xD329,0xDE);
		write_reg(0xD32A,0x02);
		write_reg(0xD32B,0xF2);
		write_reg(0xD32C,0x02);
		write_reg(0xD32D,0xFE);
		write_reg(0xD32E,0x03);
		write_reg(0xD32F,0x10);
		write_reg(0xD330,0x03);
		write_reg(0xD331,0x33);
		write_reg(0xD332,0x03);
		write_reg(0xD333,0x6D);
		write_reg(0xD400,0x00);
		write_reg(0xD401,0x33);
		write_reg(0xD402,0x00);
		write_reg(0xD403,0x34);
		write_reg(0xD404,0x00);
		write_reg(0xD405,0x3A);
		write_reg(0xD406,0x00);
		write_reg(0xD407,0x4A);
		write_reg(0xD408,0x00);
		write_reg(0xD409,0x5C);
		write_reg(0xD40A,0x00);
		write_reg(0xD40B,0x81);

		write_reg(0xD40C,0x00);
		write_reg(0xD40D,0xA6);
		write_reg(0xD40E,0x00);
		write_reg(0xD40F,0xE5);
		write_reg(0xD410,0x01);
		write_reg(0xD411,0x13);
		write_reg(0xD412,0x01);
		write_reg(0xD413,0x54);
		write_reg(0xD414,0x01);
		write_reg(0xD415,0x82);
		write_reg(0xD416,0x01);
		write_reg(0xD417,0xCA);
		write_reg(0xD418,0x02);
		write_reg(0xD419,0x00);
		write_reg(0xD41A,0x02);
		write_reg(0xD41B,0x01);
		write_reg(0xD41C,0x02);
		write_reg(0xD41D,0x34);
		write_reg(0xD41E,0x02);
		write_reg(0xD41F,0x67);
		write_reg(0xD420,0x02);
		write_reg(0xD421,0x84);
		write_reg(0xD422,0x02);
		write_reg(0xD423,0xA4);
		write_reg(0xD424,0x02);
		write_reg(0xD425,0xB7);
		write_reg(0xD426,0x02);
		write_reg(0xD427,0xCF);
		write_reg(0xD428,0x02);
		write_reg(0xD429,0xDE);
		write_reg(0xD42A,0x02);
		write_reg(0xD42B,0xF2);
		write_reg(0xD42C,0x02);
		write_reg(0xD42D,0xFE);
		write_reg(0xD42E,0x03);
		write_reg(0xD42F,0x10);
		write_reg(0xD430,0x03);
		write_reg(0xD431,0x33);
		write_reg(0xD432,0x03);
		write_reg(0xD433,0x6D);
		write_reg(0xD500,0x00);
		write_reg(0xD501,0x33);
		write_reg(0xD502,0x00);
		write_reg(0xD503,0x34);
		write_reg(0xD504,0x00);
		write_reg(0xD505,0x3A);
		write_reg(0xD506,0x00);
		write_reg(0xD507,0x4A);
		write_reg(0xD508,0x00);
		write_reg(0xD509,0x5C);
		write_reg(0xD50A,0x00);
		write_reg(0xD50B,0x81);

		write_reg(0xD50C,0x00);
		write_reg(0xD50D,0xA6);
		write_reg(0xD50E,0x00);
		write_reg(0xD50F,0xE5);
		write_reg(0xD510,0x01);
		write_reg(0xD511,0x13);
		write_reg(0xD512,0x01);
		write_reg(0xD513,0x54);
		write_reg(0xD514,0x01);
		write_reg(0xD515,0x82);
		write_reg(0xD516,0x01);
		write_reg(0xD517,0xCA);
		write_reg(0xD518,0x02);
		write_reg(0xD519,0x00);
		write_reg(0xD51A,0x02);
		write_reg(0xD51B,0x01);
		write_reg(0xD51C,0x02);
		write_reg(0xD51D,0x34);
		write_reg(0xD51E,0x02);
		write_reg(0xD51F,0x67);
		write_reg(0xD520,0x02);
		write_reg(0xD521,0x84);
		write_reg(0xD522,0x02);
		write_reg(0xD523,0xA4);
		write_reg(0xD524,0x02);
		write_reg(0xD525,0xB7);
		write_reg(0xD526,0x02);
		write_reg(0xD527,0xCF);
		write_reg(0xD528,0x02);
		write_reg(0xD529,0xDE);
		write_reg(0xD52A,0x02);
		write_reg(0xD52B,0xF2);
		write_reg(0xD52C,0x02);
		write_reg(0xD52D,0xFE);
		write_reg(0xD52E,0x03);
		write_reg(0xD52F,0x10);
		write_reg(0xD530,0x03);
		write_reg(0xD531,0x33);
		write_reg(0xD532,0x03);
		write_reg(0xD533,0x6D);
		write_reg(0xD600,0x00);
		write_reg(0xD601,0x33);
		write_reg(0xD602,0x00);
		write_reg(0xD603,0x34);
		write_reg(0xD604,0x00);
		write_reg(0xD605,0x3A);
		write_reg(0xD606,0x00);
		write_reg(0xD607,0x4A);
		write_reg(0xD608,0x00);
		write_reg(0xD609,0x5C);
		write_reg(0xD60A,0x00);
		write_reg(0xD60B,0x81);

		write_reg(0xD60C,0x00);
		write_reg(0xD60D,0xA6);
		write_reg(0xD60E,0x00);
		write_reg(0xD60F,0xE5);
		write_reg(0xD610,0x01);
		write_reg(0xD611,0x13);
		write_reg(0xD612,0x01);
		write_reg(0xD613,0x54);
		write_reg(0xD614,0x01);
		write_reg(0xD615,0x82);
		write_reg(0xD616,0x01);
		write_reg(0xD617,0xCA);
		write_reg(0xD618,0x02);
		write_reg(0xD619,0x00);
		write_reg(0xD61A,0x02);
		write_reg(0xD61B,0x01);
		write_reg(0xD61C,0x02);
		write_reg(0xD61D,0x34);
		write_reg(0xD61E,0x02);
		write_reg(0xD61F,0x67);
		write_reg(0xD620,0x02);
		write_reg(0xD621,0x84);
		write_reg(0xD622,0x02);
		write_reg(0xD623,0xA4);
		write_reg(0xD624,0x02);
		write_reg(0xD625,0xB7);
		write_reg(0xD626,0x02);
		write_reg(0xD627,0xCF);
		write_reg(0xD628,0x02);
		write_reg(0xD629,0xDE);
		write_reg(0xD62A,0x02);
		write_reg(0xD62B,0xF2);
		write_reg(0xD62C,0x02);
		write_reg(0xD62D,0xFE);
		write_reg(0xD62E,0x03);
		write_reg(0xD62F,0x10);
		write_reg(0xD630,0x03);
		write_reg(0xD631,0x33);
		write_reg(0xD632,0x03);
		write_reg(0xD633,0x6D);
		//LV2 Page 0 enable
		write_reg(0xF000,0x55);
		write_reg(0xF001,0xAA);
		write_reg(0xF002,0x52);
		write_reg(0xF003,0x08);
		write_reg(0xF004,0x00);
		//Display control
		write_reg(0xB100, 0xCC);
		write_reg(0xB101, 0x00);
		//Source hold time
		write_reg(0xB600,0x05);
		//Gate EQ control
		write_reg(0xB700,0x70);
		write_reg(0xB701,0x70);
		//Source EQ control (Mode 2)
		write_reg(0xB800,0x01);
		write_reg(0xB801,0x03);
		write_reg(0xB802,0x03);
		write_reg(0xB803,0x03);
		//Inversion mode (2-dot)
		write_reg(0xBC00,0x02);
		write_reg(0xBC01,0x00);
		write_reg(0xBC02,0x00);
		//Timing control 4H w/ 4-delay
		write_reg(0xC900,0xD0);
		write_reg(0xC901,0x02);
		write_reg(0xC902,0x50);
		write_reg(0xC903,0x50);
		write_reg(0xC904,0x50);
		write_reg(0x3500,0x00);
		//write_reg(0x3600,0x00);
		write_reg(0x3A00,0x55);  //16-bit/pixel
		write_command(0x1100);
		bsp_delay_us(120);
		write_command(0x2900);
		lcd.command.write_gram 	= 0x2C00;
		lcd.command.read_gram		= 0x2E00;
		lcd.command.set_x 			= 0x2A00;
		lcd.command.set_y 			= 0x2B00;
	}else if(lcd.id==0x9325)//9325
	{
		write_reg(0x00E5,0x78F0); 
		write_reg(0x0001,0x0100); 
		write_reg(0x0002,0x0700); 
		write_reg(0x0003,0x1030); 
		write_reg(0x0004,0x0000); 
		write_reg(0x0008,0x0202);  
		write_reg(0x0009,0x0000);
		write_reg(0x000A,0x0000); 
		write_reg(0x000C,0x0000); 
		write_reg(0x000D,0x0000);
		write_reg(0x000F,0x0000);
		//power on sequence VGHVGL
		write_reg(0x0010,0x0000);   
		write_reg(0x0011,0x0007);  
		write_reg(0x0012,0x0000);  
		write_reg(0x0013,0x0000); 
		write_reg(0x0007,0x0000); 
		//vgh 
		write_reg(0x0010,0x1690);   
		write_reg(0x0011,0x0227);
		//delayms(100);
		//vregiout 
		write_reg(0x0012,0x009D); //0x001b
		//delayms(100); 
		//vom amplitude
		write_reg(0x0013,0x1900);
		//delayms(100); 
		//vom H
		write_reg(0x0029,0x0025); 
		write_reg(0x002B,0x000D); 
		//gamma
		write_reg(0x0030,0x0007);
		write_reg(0x0031,0x0303);
		write_reg(0x0032,0x0003);// 0006
		write_reg(0x0035,0x0206);
		write_reg(0x0036,0x0008);
		write_reg(0x0037,0x0406); 
		write_reg(0x0038,0x0304);//0200
		write_reg(0x0039,0x0007); 
		write_reg(0x003C,0x0602);// 0504
		write_reg(0x003D,0x0008); 
		//ram
		write_reg(0x0050,0x0000); 
		write_reg(0x0051,0x00EF);
		write_reg(0x0052,0x0000); 
		write_reg(0x0053,0x013F);  
		write_reg(0x0060,0xA700); 
		write_reg(0x0061,0x0001); 
		write_reg(0x006A,0x0000); 
		//
		write_reg(0x0080,0x0000); 
		write_reg(0x0081,0x0000); 
		write_reg(0x0082,0x0000); 
		write_reg(0x0083,0x0000); 
		write_reg(0x0084,0x0000); 
		write_reg(0x0085,0x0000); 
		//
		write_reg(0x0090,0x0010); 
		write_reg(0x0092,0x0600); 
		
		write_reg(0x0007,0x0133);
		write_reg(0x00,0x0022);//
	}else if(lcd.id==0x9328)//ILI9328   OK  
	{
  		write_reg(0x00EC,0x108F);// internal timeing      
 		write_reg(0x00EF,0x1234);// ADD        
		//write_reg(0x00e7,0x0010);      
        //write_reg(0x0000,0x0001);//开启内部时钟
        write_reg(0x0001,0x0100);     
        write_reg(0x0002,0x0700);//电源开启                    
		//write_reg(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
		//DRIVE TABLE(寄存器 03H)
		//BIT3=AM BIT4:5=ID0:1
		//AM ID0 ID1   FUNCATION
		// 0  0   0	   R->L D->U
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D 正常就用这个.
		// 1  1   1	   U->D	L->R
        write_reg(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
        write_reg(0x0004,0x0000);                                   
        write_reg(0x0008,0x0202);	           
        write_reg(0x0009,0x0000);         
        write_reg(0x000a,0x0000);//display setting         
        write_reg(0x000c,0x0001);//display setting          
        write_reg(0x000d,0x0000);//0f3c          
        write_reg(0x000f,0x0000);
		//电源配置
        write_reg(0x0010,0x0000);   
        write_reg(0x0011,0x0007);
        write_reg(0x0012,0x0000);                                                                 
        write_reg(0x0013,0x0000);                 
     	write_reg(0x0007,0x0001);                 
       	bsp_delay_ms(50); 
        write_reg(0x0010,0x1490);   
        write_reg(0x0011,0x0227);
        bsp_delay_ms(50); 
        write_reg(0x0012,0x008A);                  
        bsp_delay_ms(50); 
        write_reg(0x0013,0x1a00);   
        write_reg(0x0029,0x0006);
        write_reg(0x002b,0x000d);
        bsp_delay_ms(50); 
        write_reg(0x0020,0x0000);                                                            
        write_reg(0x0021,0x0000);           
		bsp_delay_ms(50); 
		//伽马校正
        write_reg(0x0030,0x0000); 
        write_reg(0x0031,0x0604);   
        write_reg(0x0032,0x0305);
        write_reg(0x0035,0x0000);
        write_reg(0x0036,0x0C09); 
        write_reg(0x0037,0x0204);
        write_reg(0x0038,0x0301);        
        write_reg(0x0039,0x0707);     
        write_reg(0x003c,0x0000);
        write_reg(0x003d,0x0a0a);
        bsp_delay_ms(50); 
        write_reg(0x0050,0x0000); //水平GRAM起始位置 
        write_reg(0x0051,0x00ef); //水平GRAM终止位置                    
        write_reg(0x0052,0x0000); //垂直GRAM起始位置                    
        write_reg(0x0053,0x013f); //垂直GRAM终止位置  
 
         write_reg(0x0060,0xa700);        
        write_reg(0x0061,0x0001); 
        write_reg(0x006a,0x0000);
        write_reg(0x0080,0x0000);
        write_reg(0x0081,0x0000);
        write_reg(0x0082,0x0000);
        write_reg(0x0083,0x0000);
        write_reg(0x0084,0x0000);
        write_reg(0x0085,0x0000);
      
        write_reg(0x0090,0x0010);     
        write_reg(0x0092,0x0600);  
        //开启显示设置    
        write_reg(0x0007,0x0133); 
	}else if(lcd.id==0x9320)//测试OK.
	{
		write_reg(0x00,0x0000);
		write_reg(0x01,0x0100);	//Driver Output Contral.
		write_reg(0x02,0x0700);	//LCD Driver Waveform Contral.
		write_reg(0x03,0x1030);//Entry Mode Set.
		//write_reg(0x03,0x1018);	//Entry Mode Set.
	
		write_reg(0x04,0x0000);	//Scalling Contral.
		write_reg(0x08,0x0202);	//Display Contral 2.(0x0207)
		write_reg(0x09,0x0000);	//Display Contral 3.(0x0000)
		write_reg(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		write_reg(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		write_reg(0x0d,0x0000);	//Frame Maker Position.
		write_reg(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		bsp_delay_ms(50); 
		write_reg(0x07,0x0101);	//Display Contral.
		bsp_delay_ms(50); 								  
		write_reg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		write_reg(0x11,0x0007);								//Power Control 2.(0x0001)
		write_reg(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		write_reg(0x13,0x0b00);								//Power Control 4.
		write_reg(0x29,0x0000);								//Power Control 7.
	
		write_reg(0x2b,(1<<14)|(1<<4));	    
		write_reg(0x50,0);	//Set X Star
		//水平GRAM终止位置Set X End.
		write_reg(0x51,239);	//Set Y Star
		write_reg(0x52,0);	//Set Y End.t.
		write_reg(0x53,319);	//
	
		write_reg(0x60,0x2700);	//Driver Output Control.
		write_reg(0x61,0x0001);	//Driver Output Control.
		write_reg(0x6a,0x0000);	//Vertical Srcoll Control.
	
		write_reg(0x80,0x0000);	//Display Position? Partial Display 1.
		write_reg(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		write_reg(0x82,0x0000);	//RAM Address End-Partial Display 1.
		write_reg(0x83,0x0000);	//Displsy Position? Partial Display 2.
		write_reg(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		write_reg(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		write_reg(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		write_reg(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		write_reg(0x93,0x0001);	//Panel Interface Contral 3.
		write_reg(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		write_reg(0x97,(0<<8));	//
		write_reg(0x98,0x0000);	//Frame Cycle Contral.	   
		write_reg(0x07,0x0173);	//(0x0173)
	}else if(lcd.id==0X9331)//OK |/|/|			 
	{
		write_reg(0x00E7, 0x1014);
		write_reg(0x0001, 0x0100); // set SS and SM bit
		write_reg(0x0002, 0x0200); // set 1 line inversion
        write_reg(0x0003,(1<<12)|(3<<4)|(1<<3));//65K    
		//write_reg(0x0003, 0x1030); // set GRAM write direction and BGR=1.
		write_reg(0x0008, 0x0202); // set the back porch and front porch
		write_reg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		write_reg(0x000A, 0x0000); // FMARK function
		write_reg(0x000C, 0x0000); // RGB interface setting
		write_reg(0x000D, 0x0000); // Frame marker Position
		write_reg(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		write_reg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		write_reg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		write_reg(0x0012, 0x0000); // VREG1OUT voltage
		write_reg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		bsp_delay_ms(200); // Dis-charge capacitor power voltage
		write_reg(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		write_reg(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		bsp_delay_ms(50); // Delay 50ms
		write_reg(0x0012, 0x000C); // Internal reference voltage= Vci;
		bsp_delay_ms(50); // Delay 50ms
		write_reg(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		write_reg(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		write_reg(0x002B, 0x000B); // Set Frame Rate
		bsp_delay_ms(50); // Delay 50ms
		write_reg(0x0020, 0x0000); // GRAM horizontal Address
		write_reg(0x0021, 0x013f); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		write_reg(0x0030, 0x0000);
		write_reg(0x0031, 0x0106);
		write_reg(0x0032, 0x0000);
		write_reg(0x0035, 0x0204);
		write_reg(0x0036, 0x160A);
		write_reg(0x0037, 0x0707);
		write_reg(0x0038, 0x0106);
		write_reg(0x0039, 0x0707);
		write_reg(0x003C, 0x0402);
		write_reg(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		write_reg(0x0050, 0x0000); // Horizontal GRAM Start Address
		write_reg(0x0051, 0x00EF); // Horizontal GRAM End Address
		write_reg(0x0052, 0x0000); // Vertical GRAM Start Address
		write_reg(0x0053, 0x013F); // Vertical GRAM Start Address
		write_reg(0x0060, 0x2700); // Gate Scan Line
		write_reg(0x0061, 0x0001); // NDL,VLE, REV 
		write_reg(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		write_reg(0x0080, 0x0000);
		write_reg(0x0081, 0x0000);
		write_reg(0x0082, 0x0000);
		write_reg(0x0083, 0x0000);
		write_reg(0x0084, 0x0000);
		write_reg(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		write_reg(0x0090, 0x0010);
		write_reg(0x0092, 0x0600);
		write_reg(0x0007, 0x0133); // 262K color and display ON
	}else if(lcd.id==0x5408)
	{
		write_reg(0x01,0x0100);								  
		write_reg(0x02,0x0700);//LCD Driving Waveform Contral 
		write_reg(0x03,0x1030);//Entry Mode设置 	   
		//指针从左至右自上而下的自动增模式
		//Normal Mode(Window Mode disable)
		//RGB格式
		//16位数据2次传输的8总线设置
		write_reg(0x04,0x0000); //Scalling Control register     
		write_reg(0x08,0x0207); //Display Control 2 
		write_reg(0x09,0x0000); //Display Control 3	 
		write_reg(0x0A,0x0000); //Frame Cycle Control	 
		write_reg(0x0C,0x0000); //External Display Interface Control 1 
		write_reg(0x0D,0x0000); //Frame Maker Position		 
		write_reg(0x0F,0x0000); //External Display Interface Control 2 
 		bsp_delay_ms(20);
		//TFT 液晶彩色图像显示方法14
		write_reg(0x10,0x16B0); //0x14B0 //Power Control 1
		write_reg(0x11,0x0001); //0x0007 //Power Control 2
		write_reg(0x17,0x0001); //0x0000 //Power Control 3
		write_reg(0x12,0x0138); //0x013B //Power Control 4
		write_reg(0x13,0x0800); //0x0800 //Power Control 5
		write_reg(0x29,0x0009); //NVM read data 2
		write_reg(0x2a,0x0009); //NVM read data 3
		write_reg(0xa4,0x0000);	 
		write_reg(0x50,0x0000); //设置操作窗口的X轴开始列
		write_reg(0x51,0x00EF); //设置操作窗口的X轴结束列
		write_reg(0x52,0x0000); //设置操作窗口的Y轴开始行
		write_reg(0x53,0x013F); //设置操作窗口的Y轴结束行
		write_reg(0x60,0x2700); //Driver Output Control
		//设置屏幕的点数以及扫描的起始行
		write_reg(0x61,0x0001); //Driver Output Control
		write_reg(0x6A,0x0000); //Vertical Scroll Control
		write_reg(0x80,0x0000); //Display Position – Partial Display 1
		write_reg(0x81,0x0000); //RAM Address Start – Partial Display 1
		write_reg(0x82,0x0000); //RAM address End - Partial Display 1
		write_reg(0x83,0x0000); //Display Position – Partial Display 2
		write_reg(0x84,0x0000); //RAM Address Start – Partial Display 2
		write_reg(0x85,0x0000); //RAM address End – Partail Display2
		write_reg(0x90,0x0013); //Frame Cycle Control
		write_reg(0x92,0x0000);  //Panel Interface Control 2
		write_reg(0x93,0x0003); //Panel Interface control 3
		write_reg(0x95,0x0110);  //Frame Cycle Control
		write_reg(0x07,0x0173);		 
		bsp_delay_ms(50);
	}	
	else if(lcd.id==0x1505)//OK
	{
		// second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        write_reg(0x0007,0x0000);
        bsp_delay_ms(50); 
        write_reg(0x0012,0x011C);//0x011A   why need to set several times?
        write_reg(0x00A4,0x0001);//NVM	 
        write_reg(0x0008,0x000F);
        write_reg(0x000A,0x0008);
        write_reg(0x000D,0x0008);	    
  		//伽马校正
        write_reg(0x0030,0x0707);
        write_reg(0x0031,0x0007); //0x0707
        write_reg(0x0032,0x0603); 
        write_reg(0x0033,0x0700); 
        write_reg(0x0034,0x0202); 
        write_reg(0x0035,0x0002); //?0x0606
        write_reg(0x0036,0x1F0F);
        write_reg(0x0037,0x0707); //0x0f0f  0x0105
        write_reg(0x0038,0x0000); 
        write_reg(0x0039,0x0000); 
        write_reg(0x003A,0x0707); 
        write_reg(0x003B,0x0000); //0x0303
        write_reg(0x003C,0x0007); //?0x0707
        write_reg(0x003D,0x0000); //0x1313//0x1f08
        bsp_delay_ms(50); 
        write_reg(0x0007,0x0001);
        write_reg(0x0017,0x0001);//开启电源
        bsp_delay_ms(50); 
  		//电源配置
        write_reg(0x0010,0x17A0); 
        write_reg(0x0011,0x0217);//reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        write_reg(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        write_reg(0x0013,0x0F00);//VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        write_reg(0x002A,0x0000);  
        write_reg(0x0029,0x000A);//0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        write_reg(0x0012,0x013E);// 0x013C  power supply on
        //Coordinates Control//
        write_reg(0x0050,0x0000);//0x0e00
        write_reg(0x0051,0x00EF); 
        write_reg(0x0052,0x0000); 
        write_reg(0x0053,0x013F); 
    	//Pannel Image Control//
        write_reg(0x0060,0x2700); 
        write_reg(0x0061,0x0001); 
        write_reg(0x006A,0x0000); 
        write_reg(0x0080,0x0000); 
    	//Partial Image Control//
        write_reg(0x0081,0x0000); 
        write_reg(0x0082,0x0000); 
        write_reg(0x0083,0x0000); 
        write_reg(0x0084,0x0000); 
        write_reg(0x0085,0x0000); 
  		//Panel Interface Control//
        write_reg(0x0090,0x0013);//0x0010 frenqucy
        write_reg(0x0092,0x0300); 
        write_reg(0x0093,0x0005); 
        write_reg(0x0095,0x0000); 
        write_reg(0x0097,0x0000); 
        write_reg(0x0098,0x0000); 
  
        write_reg(0x0001,0x0100); 
        write_reg(0x0002,0x0700); 
        write_reg(0x0003,0x1038);//扫描方向 上->下  左->右 
        write_reg(0x0004,0x0000); 
        write_reg(0x000C,0x0000); 
        write_reg(0x000F,0x0000); 
        write_reg(0x0020,0x0000); 
        write_reg(0x0021,0x0000); 
        write_reg(0x0007,0x0021); 
        bsp_delay_ms(20);
        write_reg(0x0007,0x0061); 
        bsp_delay_ms(20);
        write_reg(0x0007,0x0173); 
        bsp_delay_ms(20);
	}else if(lcd.id==0xB505)
	{
		write_reg(0x0000,0x0000);
		write_reg(0x0000,0x0000);
		write_reg(0x0000,0x0000);
		write_reg(0x0000,0x0000);
		
		write_reg(0x00a4,0x0001);
		bsp_delay_ms(20);		  
		write_reg(0x0060,0x2700);
		write_reg(0x0008,0x0202);
		
		write_reg(0x0030,0x0214);
		write_reg(0x0031,0x3715);
		write_reg(0x0032,0x0604);
		write_reg(0x0033,0x0e16);
		write_reg(0x0034,0x2211);
		write_reg(0x0035,0x1500);
		write_reg(0x0036,0x8507);
		write_reg(0x0037,0x1407);
		write_reg(0x0038,0x1403);
		write_reg(0x0039,0x0020);
		
		write_reg(0x0090,0x001a);
		write_reg(0x0010,0x0000);
		write_reg(0x0011,0x0007);
		write_reg(0x0012,0x0000);
		write_reg(0x0013,0x0000);
		bsp_delay_ms(20);
		
		write_reg(0x0010,0x0730);
		write_reg(0x0011,0x0137);
		bsp_delay_ms(20);
		
		write_reg(0x0012,0x01b8);
		bsp_delay_ms(20);
		
		write_reg(0x0013,0x0f00);
		write_reg(0x002a,0x0080);
		write_reg(0x0029,0x0048);
		bsp_delay_ms(20);
		
		write_reg(0x0001,0x0100);
		write_reg(0x0002,0x0700);
    write_reg(0x0003,0x1038);//扫描方向 上->下  左->右 
		write_reg(0x0008,0x0202);
		write_reg(0x000a,0x0000);
		write_reg(0x000c,0x0000);
		write_reg(0x000d,0x0000);
		write_reg(0x000e,0x0030);
		write_reg(0x0050,0x0000);
		write_reg(0x0051,0x00ef);
		write_reg(0x0052,0x0000);
		write_reg(0x0053,0x013f);
		write_reg(0x0060,0x2700);
		write_reg(0x0061,0x0001);
		write_reg(0x006a,0x0000);
		//write_reg(0x0080,0x0000);
		//write_reg(0x0081,0x0000);
		write_reg(0x0090,0X0011);
		write_reg(0x0092,0x0600);
		write_reg(0x0093,0x0402);
		write_reg(0x0094,0x0002);
		bsp_delay_ms(20);
		
		write_reg(0x0007,0x0001);
		bsp_delay_ms(20);
		write_reg(0x0007,0x0061);
		write_reg(0x0007,0x0173);
		
		write_reg(0x0020,0x0000);
		write_reg(0x0021,0x0000);	  
		write_reg(0x00,0x22);  
	}else if(lcd.id==0xC505)
	{
		write_reg(0x0000,0x0000);
		write_reg(0x0000,0x0000);
		bsp_delay_ms(20);		  
		write_reg(0x0000,0x0000);
		write_reg(0x0000,0x0000);
		write_reg(0x0000,0x0000);
		write_reg(0x0000,0x0000);
 		write_reg(0x00a4,0x0001);
		bsp_delay_ms(20);		  
		write_reg(0x0060,0x2700);
		write_reg(0x0008,0x0806);
		
		write_reg(0x0030,0x0703);//gamma setting
		write_reg(0x0031,0x0001);
		write_reg(0x0032,0x0004);
		write_reg(0x0033,0x0102);
		write_reg(0x0034,0x0300);
		write_reg(0x0035,0x0103);
		write_reg(0x0036,0x001F);
		write_reg(0x0037,0x0703);
		write_reg(0x0038,0x0001);
		write_reg(0x0039,0x0004);
		
		
		
		write_reg(0x0090, 0x0015);	//80Hz
		write_reg(0x0010, 0X0410);	//BT,AP
		write_reg(0x0011,0x0247);	//DC1,DC0,VC
		write_reg(0x0012, 0x01BC);
		write_reg(0x0013, 0x0e00);
		bsp_delay_ms(120);
		write_reg(0x0001, 0x0100);
		write_reg(0x0002, 0x0200);
		write_reg(0x0003, 0x1030);
		
		write_reg(0x000A, 0x0008);
		write_reg(0x000C, 0x0000);
		
		write_reg(0x000E, 0x0020);
		write_reg(0x000F, 0x0000);
		write_reg(0x0020, 0x0000);	//H Start
		write_reg(0x0021, 0x0000);	//V Start
		write_reg(0x002A,0x003D);	//vcom2
		bsp_delay_ms(20);
		write_reg(0x0029, 0x002d);
		write_reg(0x0050, 0x0000);
		write_reg(0x0051, 0xD0EF);
		write_reg(0x0052, 0x0000);
		write_reg(0x0053, 0x013F);
		write_reg(0x0061, 0x0000);
		write_reg(0x006A, 0x0000);
		write_reg(0x0092,0x0300); 
 
 		write_reg(0x0093, 0x0005);
		write_reg(0x0007, 0x0100);
	}else if(lcd.id==0x4531)//OK |/|/|
	{
		write_reg(0X00,0X0001);   
		bsp_delay_ms(10);   
		write_reg(0X10,0X1628);   
		write_reg(0X12,0X000e);//0x0006    
		write_reg(0X13,0X0A39);   
		bsp_delay_ms(10);   
		write_reg(0X11,0X0040);   
		write_reg(0X15,0X0050);   
		bsp_delay_ms(10);   
		write_reg(0X12,0X001e);//16    
		bsp_delay_ms(10);   
		write_reg(0X10,0X1620);   
		write_reg(0X13,0X2A39);   
		bsp_delay_ms(10);   
		write_reg(0X01,0X0100);   
		write_reg(0X02,0X0300);   
		write_reg(0X03,0X1038);//改变方向的   
		write_reg(0X08,0X0202);   
		write_reg(0X0A,0X0008);   
		write_reg(0X30,0X0000);   
		write_reg(0X31,0X0402);   
		write_reg(0X32,0X0106);   
		write_reg(0X33,0X0503);   
		write_reg(0X34,0X0104);   
		write_reg(0X35,0X0301);   
		write_reg(0X36,0X0707);   
		write_reg(0X37,0X0305);   
		write_reg(0X38,0X0208);   
		write_reg(0X39,0X0F0B);   
		write_reg(0X41,0X0002);   
		write_reg(0X60,0X2700);   
		write_reg(0X61,0X0001);   
		write_reg(0X90,0X0210);   
		write_reg(0X92,0X010A);   
		write_reg(0X93,0X0004);   
		write_reg(0XA0,0X0100);   
		write_reg(0X07,0X0001);   
		write_reg(0X07,0X0021);   
		write_reg(0X07,0X0023);   
		write_reg(0X07,0X0033);   
		write_reg(0X07,0X0133);   
		write_reg(0XA0,0X0000); 
	}else if(lcd.id==0x4535)
	{			      
		write_reg(0X15,0X0030);   
		write_reg(0X9A,0X0010);   
 		write_reg(0X11,0X0020);   
 		write_reg(0X10,0X3428);   
		write_reg(0X12,0X0002);//16    
 		write_reg(0X13,0X1038);   
		bsp_delay_ms(40);   
		write_reg(0X12,0X0012);//16    
		bsp_delay_ms(40);   
  		write_reg(0X10,0X3420);   
 		write_reg(0X13,0X3038);   
		bsp_delay_ms(70);   
		write_reg(0X30,0X0000);   
		write_reg(0X31,0X0402);   
		write_reg(0X32,0X0307);   
		write_reg(0X33,0X0304);   
		write_reg(0X34,0X0004);   
		write_reg(0X35,0X0401);   
		write_reg(0X36,0X0707);   
		write_reg(0X37,0X0305);   
		write_reg(0X38,0X0610);   
		write_reg(0X39,0X0610); 
		  
		write_reg(0X01,0X0100);   
		write_reg(0X02,0X0300);   
		write_reg(0X03,0X1030);//改变方向的   
		write_reg(0X08,0X0808);   
		write_reg(0X0A,0X0008);   
 		write_reg(0X60,0X2700);   
		write_reg(0X61,0X0001);   
		write_reg(0X90,0X013E);   
		write_reg(0X92,0X0100);   
		write_reg(0X93,0X0100);   
 		write_reg(0XA0,0X3000);   
 		write_reg(0XA3,0X0010);   
		write_reg(0X07,0X0001);   
		write_reg(0X07,0X0021);   
		write_reg(0X07,0X0023);   
		write_reg(0X07,0X0033);   
		write_reg(0X07,0X0133);   
	}else if(lcd.id==0X1963){
		write_command(0xE2);		//Set PLL with OSC = 10MHz (hardware),	Multiplier N = 35, 250MHz < VCO < 800MHz = OSC*(N+1), VCO = 300MHz
		write_ram(0x1D);		//参数1 
		write_ram(0x02);		//参数2 Divider M = 2, PLL = 300/(M+1) = 100MHz
		write_ram(0x04);		//参数3 Validate M and N values   
		bsp_delay_us(100);
		write_command(0xE0);		// Start PLL command
		write_ram(0x01);		// enable PLL
		bsp_delay_ms(10);
		write_command(0xE0);		// Start PLL command again
		write_ram(0x03);		// now, use PLL output as system clock	
		bsp_delay_ms(12);  
		write_command(0x01);		//软复位
		bsp_delay_ms(10);
		
		write_command(0xE6);		//设置像素频率,33Mhz
		write_ram(0x2F);
		write_ram(0xFF);
		write_ram(0xFF);
		
		write_command(0xB0);		//设置LCD模式
		write_ram(0x20);		//24位模式
		write_ram(0x00);		//TFT 模式 
	
		write_ram((LCD_HOR_RESOLUTION-1)>>8);//设置LCD水平像素
		write_ram(LCD_HOR_RESOLUTION-1);		 
		write_ram((LCD_VER_RESOLUTION-1)>>8);//设置LCD垂直像素
		write_ram(LCD_VER_RESOLUTION-1);		 
		write_ram(0x00);		//RGB序列 
		
		write_command(0xB4);		//Set horizontal period
		write_ram((LCD_HT-1)>>8);
		write_ram(LCD_HT-1);
		write_ram(LCD_HPS>>8);
		write_ram(LCD_HPS);
		write_ram(LCD_HOR_PULSE_WIDTH-1);
		write_ram(0x00);
		write_ram(0x00);
		write_ram(0x00);
		write_command(0xB6);		//Set vertical period
		write_ram((LCD_VT-1)>>8);
		write_ram(LCD_VT-1);
		write_ram(LCD_VPS>>8);
		write_ram(LCD_VPS);
		write_ram(LCD_VER_FRONT_PORCH-1);
		write_ram(0x00);
		write_ram(0x00);
		
		write_command(0xF0);	//设置LCD1963与CPU接口为16bit  
		write_ram(0x03);	//16-bit(565 format) data for 16bpp 

		write_command(0x29);	//开启显示
		//设置PWM输出  背光通过占空比可调 
		write_command(0xD0);	//设置自动白平衡DBC
		write_ram(0x00);	//disable
	
		write_command(0xBE);	//配置PWM输出
		write_ram(0x05);	//1设置PWM频率
		write_ram(0xFE);	//2设置PWM占空比
		write_ram(0x01);	//3设置C
		write_ram(0x00);	//4设置D
		write_ram(0x00);	//5设置E 
		write_ram(0x00);	//6设置F 
		
		write_command(0xB8);	//设置GPIO配置
		write_ram(0x03);	//2个IO口设置成输出
		write_ram(0x01);	//GPIO使用正常的IO功能 
		write_command(0xBA);
		write_ram(0X01);	//GPIO[1:0]=01,控制LCD方向
		
		lcd.command.write_gram 	= 0x002C;
		lcd.command.read_gram		= 0x002E;
		lcd.command.set_x 			= 0x002A;
		lcd.command.set_y 			= 0x002B;
		set_backlight(100);//背光设置为最亮
	}		 
	
	/* 屏蔽初始化后的短暂白屏 */
	bsp_delay_us(120);
	/* 点亮背光LED */
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	lcd.clear(CL_WHITE);
	write_reg(0x3600,(0<<7)|(0<<6)|(1<<5));
}

static uint16_t read_id(void)
{
	uint16_t id;
	write_command(0xA1);
	bsp_delay_us(1);
	read_ram();
	
	id = read_ram();
	id = (id << 8) | read_ram();

	if(id == 0x5761)
		return 0x1963;
	else
		return 0x0000;
}

static void set_backlight(uint8_t pwm)
{
	write_command(0xBE);		//配置PWM输出
	write_ram(0x05);		//1设置PWM频率
	write_ram(pwm * 2.55);	//2设置PWM占空比
	write_ram(0x01);		//3设置C
	write_ram(0xFF);		//4设置D
	write_ram(0x00);		//5设置E
	write_ram(0x00);		//6设置F
}

static void open(void)
{
	write_command(0x29);
}

static void close(void)
{
	write_command(0x28);
}

static void set_cursor(uint16_t _usX, uint16_t _usY)
{
	if(lcd.id==0X9341||lcd.id==0X5310){		    
		write_command(lcd.command.set_x); 
		write_ram(_usX>>8);write_ram(_usX&0XFF); 			 
		write_command(lcd.command.set_y); 
		write_ram(_usY>>8);write_ram(_usY&0XFF); 		
	}
	else if(lcd.id==0X6804)
	{
		write_command(lcd.command.set_x); 
		write_ram(_usX>>8);write_ram(_usX&0XFF); 
		write_command(lcd.command.set_y); 
		write_ram(_usY>>8);write_ram(_usY&0XFF); 
		
	}
	else if(lcd.id==0X1963) {  			 		
		write_command(lcd.command.set_x); 
		write_ram(_usX>>8);write_ram(_usX&0XFF); 
		write_ram(_usX>>8);write_ram(_usX&0XFF); 
		write_command(lcd.command.set_y); 
		write_ram(_usY>>8);write_ram(_usY&0XFF); 
		write_ram(_usY>>8);write_ram(_usY&0XFF); 
	}
	else if(lcd.id==0X5510){
		write_command(lcd.command.set_x);write_ram(_usX>>8); 		
		write_command(lcd.command.set_x+1);write_ram(_usX&0XFF);			 
		write_command(lcd.command.set_y);write_ram(_usY>>8);  		
		write_command(lcd.command.set_y+1);write_ram(_usY&0XFF);			
	}
	else{
		write_reg(lcd.command.set_x, _usX);
		write_reg(lcd.command.set_y, _usY);
	}	 
}

static void set_window(uint16_t _usX0, uint16_t _usY0, uint16_t _usX1, uint16_t _usY1)
{
	if(lcd.id==0X5510) {
		write_command(lcd.command.set_x);write_ram(_usX0>>8);  
		write_command(lcd.command.set_x+1);write_ram(_usX0&0XFF);	  
		write_command(lcd.command.set_x+2);write_ram(_usX1>>8);   
		write_command(lcd.command.set_x+3);write_ram(_usX1&0XFF);   
		write_command(lcd.command.set_y);write_ram(_usY0>>8);   
		write_command(lcd.command.set_y+1);write_ram(_usY0&0XFF);  
		write_command(lcd.command.set_y+2);write_ram(_usY1>>8);   
		write_command(lcd.command.set_y+3);write_ram(_usY1&0XFF); 
	}
	else if(lcd.id==0X1963) {
		LCD->REG = lcd.command.set_x;
		LCD->RAM = _usX0 >> 8;
		LCD->RAM = _usX0 & 0xFF;
		LCD->RAM = _usX1 >> 8;
		LCD->RAM = _usX1 & 0xFF;

		LCD->REG = lcd.command.set_y;
		LCD->RAM = _usY0 >> 8;
		LCD->RAM = _usY0 & 0xFF;
		LCD->RAM = _usY1 >> 8;
		LCD->RAM = _usY1 & 0xFF;
	}
}

static void clear(uint16_t _usColor)
{
	uint32_t i;
	uint32_t TotalPoint;

	TotalPoint = LCD_HOR_RESOLUTION * LCD_VER_RESOLUTION - 1;

	set_cursor(0, 0);

	write_command(lcd.command.write_gram);
	for(i = 0; i < TotalPoint; i++)
		LCD->RAM = _usColor;
}

static void put_pixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor)
{
	//_usX = LCD_HOR_RESOLUTION - 1 - _usX;
	
	set_cursor(_usX, _usY);

	write_command(lcd.command.write_gram);
	write_ram(_usColor);
}

static void put_pixel_gui(uint16_t _usX, uint16_t _usY, uint16_t _usColor)
{
	_usX = LCD_HOR_RESOLUTION - 1 - _usX;
	
	set_cursor(_usX, _usY);

	LCD->REG = lcd.command.write_gram;
	LCD->RAM = _usColor;
}

static uint16_t get_pixel(uint16_t _usX, uint16_t _usY)
{
	_usX = LCD_HOR_RESOLUTION - 1 - _usX;
	
	/* 设置光标位置 */
	set_cursor(_usX, _usY);
	
	/* 准备读显存 */
	write_command(lcd.command.read_gram);

	return read_ram();
}

static uint16_t get_pixel_gui(uint16_t _usX, uint16_t _usY)
{
	_usX = LCD_HOR_RESOLUTION - 1 - _usX;
	
	set_cursor(_usX, _usY);

	write_command(lcd.command.read_gram);

	return LCD->RAM;
}

static void draw_line(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint16_t _usColor)
{
	int32_t dx , dy ;
	int32_t tx , ty ;
	int32_t inc1 , inc2 ;
	int32_t d , iTag ;
	int32_t x , y ;
	
	/* 采用 Bresenham 算法，在2点间画一条直线 */

	put_pixel_gui(_usX1 , _usY1 , _usColor);

	/* 如果两点重合，结束后面的动作。*/
	if ( _usX1 == _usX2 && _usY1 == _usY2 )
		return;

	iTag = 0 ;
	/* dx = abs ( _usX2 - _usX1 ); */
	if (_usX2 >= _usX1)
		dx = _usX2 - _usX1;
	else
		dx = _usX1 - _usX2;

	/* dy = abs ( _usY2 - _usY1 ); */
	if (_usY2 >= _usY1)
		dy = _usY2 - _usY1;
	else
		dy = _usY1 - _usY2;
	
 /*如果dy为计长方向，则交换纵横坐标。*/
	if ( dx < dy ) {
		uint16_t temp;

		iTag = 1 ;
		temp = _usX1;
		_usX1 = _usY1;
		_usY1 = temp;
		temp = _usX2;
		_usX2 = _usY2;
		_usY2 = temp;
		temp = dx;
		dx = dy;
		dy = temp;
	}
	tx = _usX2 > _usX1 ? 1 : -1 ;    /* 确定是增1还是减1 */
	ty = _usY2 > _usY1 ? 1 : -1 ;
	x = _usX1 ;
	y = _usY1 ;
	inc1 = 2 * dy ;
	inc2 = 2 * ( dy - dx );
	d = inc1 - dx ;
	while ( x != _usX2 ) {
		if ( d < 0 )
			d += inc1 ;
		else {
			y += ty ;
			d += inc2 ;
		}
		if ( iTag )
			put_pixel_gui ( y , x , _usColor) ;
		
		else
			put_pixel_gui ( x , y , _usColor) ;
		
		x += tx ;

	}
}

static void draw_H_line(uint16_t _usX0 , uint16_t _usY , uint16_t _usX1 , uint16_t _usColor)
{
	uint16_t x;
	
	_usX0 = LCD_HOR_RESOLUTION - 1 - _usX0;
	_usX1 = LCD_HOR_RESOLUTION - 1 - _usX1;
	set_window(_usX1, _usY, _usX0, _usY);
	write_command(lcd.command.write_gram);
	for(x = _usX1; x <= _usX0; x++)
		LCD->RAM = _usColor;
}

static void draw_H_colorLine(uint16_t _usX , uint16_t _usY, uint16_t _usWidth, uint16_t *_pColor)
{
	uint16_t x;
	uint16_t _usX1 = _usX + _usWidth - 1;
	
	_usX = LCD_HOR_RESOLUTION - 1 - _usX;
	_usX1 = LCD_HOR_RESOLUTION - 1 - _usX1;
	set_window(_usX1, _usY, _usX, _usY);
	//write_reg(0x3600, (1<<7)|(0<<6)|(0<<5));
	//write_command(0x2C00);
	
	//set_window(_usX1, _usY, _usX, _usY);
	write_command(lcd.command.write_gram);
	for(x = 1; x <= _usWidth; x++)
		LCD->RAM = _pColor[_usWidth - x];
	//write_reg(0x3600, 0);
}

static void draw_V_line(uint16_t _usX , uint16_t _usY0 , uint16_t _usY1 , uint16_t _usColor)
{
	uint16_t y;
	
	_usX = LCD_HOR_RESOLUTION - 1 - _usX;
	set_window(_usX, _usY0, _usX, _usY1);
	write_command(lcd.command.write_gram);
	for(y = _usY0; y <= _usY1; y++) 
		LCD->RAM = _usColor;
	
}

static void draw_circle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor)
{
	int32_t  D;			/* Decision Variable */
	uint32_t  CurX;		/* 当前 X 值 */
	uint32_t  CurY;		/* 当前 Y 值 */

	D = 3 - (_usRadius << 1);
	CurX = 0;
	CurY = _usRadius;

	while (CurX <= CurY) {
		put_pixel_gui(_usX + CurX, _usY + CurY, _usColor);
		put_pixel_gui(_usX + CurX, _usY - CurY, _usColor);
		put_pixel_gui(_usX - CurX, _usY + CurY, _usColor);
		put_pixel_gui(_usX - CurX, _usY - CurY, _usColor);
		put_pixel_gui(_usX + CurY, _usY + CurX, _usColor);
		put_pixel_gui(_usX + CurY, _usY - CurX, _usColor);
		put_pixel_gui(_usX - CurY, _usY + CurX, _usColor);
		put_pixel_gui(_usX - CurY, _usY - CurX, _usColor);

		if (D < 0)
			D += (CurX << 2) + 6;
		else{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}

static void draw_rect(uint16_t _usX, uint16_t _usY, uint8_t _ucHeight, uint16_t _usWidth, uint16_t _usColor)
{
	/*
	 ---------------->---
	|(_usX，_usY)        |
	V                    V  _usHeight
	|                    |
	 ---------------->---
		  _usWidth
	*/

	draw_H_line(_usX, _usY, _usX + _usWidth - 1, _usColor);	/* 顶 */
	draw_H_line(_usX, _usY + _ucHeight - 1, _usX + _usWidth - 1, _usColor);	/* 底 */

	draw_V_line(_usX, _usY, _usY + _ucHeight - 1, _usColor);	/* 左 */
	draw_V_line(_usX + _usWidth - 1, _usX + _usWidth - 1, _usY + _ucHeight, _usColor);	/* 右 */
}

static void fill_rect(uint16_t _usX0, uint16_t _usY0, uint16_t _usX1, uint16_t _usY1, uint16_t _usColor)
{
	uint16_t x, y;
	
	_usX0 = LCD_HOR_RESOLUTION - 1 - _usX0;
	_usX1 = LCD_HOR_RESOLUTION - 1 - _usX1;
	
	for (y = _usY0; y <= _usY1; y++) {
		set_window(_usX1, y,_usX0 , y);
		write_command(lcd.command.write_gram);
		for(x = _usX1; x <= _usX0; x++)
			LCD->RAM = _usColor;
	
	}
}

#endif

