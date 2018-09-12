#include "systask.h"

int main()
{
	__set_PRIMASK(1);
	bsp_Init();
	usr_c322_led_init();
	os.init0();

	while(1)
	{
		
	}
	
}


