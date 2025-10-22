#include<lpc21Xx.h>
#include"Delay.h"
#include"HC_SR04.h"
#include"UART.h"

unsigned int range=0,i;

int main()
{
    VPBDIV=0x01; // PCLK = 60MHz
	UART0_CONFIG();
    HCSR04_INIT();
	UART0_STR("HC-SR04");
	
    while(1) {
        range=Range();
        UART0_Float(range);
		delay(1);
	}
}
