#include "gpio.h"
#include "Uart.h"

int main()
{
	UART0_Init(115200);
	
	Switch_Init();
	for(;;) {
	}
}

