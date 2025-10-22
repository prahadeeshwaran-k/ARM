#include<lpc214x.h>
#include"Delay.h"
#include"HC_SR04.h"
#include"UART.h"

unsigned int range=0,i;

int main()
{
    VPBDIV=0x01;                 // PCLK = 60MHz
	UART0_CONFIG();
    ultrasonic_init();
	UART0_STR("HC-SR04");
	
    while(1) {
        range=get_range();
        dat((range/100)+48);
        dat(((range/10)%10)+48);
        dat((range%10)+48);
        show("cm");
    }
}