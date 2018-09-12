#include "bsp.h"
#include "FreeRTOS.h"                      
#include "task.h"
#include "GUI.h"

#if	(__USE_DRIVER_SYSTICK)

extern void xPortSysTickHandler(void);
extern volatile GUI_TIMER_TIME OS_TimeMS;

/**
  * @brief  ����ϵͳ�δ�ʱ�� SysTick
  * @param  ��
  * @retval ��
  */
void bsp_systick_init(void)
{

	uint32_t reloadValue;
	
	/* SysTickʱ�Ӳ���Ҫϵͳʱ����ô�ߣ�Ϊ�˽��͹��Ľ���8��Ƶ */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	
	/* ����OSCfg_TickRate_Hz�趨���ʱ�� */
	reloadValue = (SystemCoreClock / 8) / 1000u;
	
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;  /* ����SYSTICK�ж� */
	SysTick->LOAD = reloadValue;                /* ÿ1 / OS_TICKS_PER_SEC���ж�һ��	*/
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   /* ����SYSTICK */
}

/**
 * @brief   us��ʱ����,1usΪһ����λ
 * note     ��SysTickʱ����ϵͳʱ�Ӳ���Ƶ��������8000000��Ϊ1000000
 * @param  
 *		@arg nTime: ��ʱ��ʱ��
 * note     ��֤nTime��1 ~ 1000000 * 2^32 / SystemCoreClock֮��
 *	         ����ֵ 1 ~ 25565281��SystemCoreClock = 168MHz��
 * @retval  %NUL
 * add by Supersure 2018
 **/
void bsp_delay_us(__IO uint32_t nTime)
{
	uint32_t ticks;
	uint32_t told;
	uint32_t tnow;
	uint32_t tcnt;
	uint32_t reload;
	
	/* �ս���ʱ�ļ�����ֵ */
	told = SysTick->VAL;
	/* ��װ��ս */
	reload = SysTick->LOAD;
	/* �������ֵ */
	tcnt = 0;
	/* ��Ҫ�Ľ����� */
	ticks = nTime * (SystemCoreClock / 8000000);

	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			/* SYSTICK��һ���ݼ��ļ����� */
			if (tnow < told)
			{
				tcnt += told - tnow;
			}
			/* ����װ�صݼ� */
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;

			/* ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
			if (tcnt >= ticks)
			{
				break;
			}
		}
	}
	
}

void bsp_delay_ms(__IO uint32_t nTime)
{
	

	if(xTaskGetSchedulerState()==taskSCHEDULER_RUNNING)     	          
		vTaskDelay(nTime);         

	else
		bsp_delay_us((uint32_t)(nTime * 1000));
}

void SysTick_Handler(void)
{
	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
    xPortSysTickHandler();  

	
}

#endif



