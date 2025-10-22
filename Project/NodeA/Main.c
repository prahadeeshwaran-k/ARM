//NODE A Main File
#include <LPC21XX.H>
#include "Delay.h"
#include "UART.h"
#include "CAN.h"

CAN2_MSG m1;

int main(){
	
	VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz
	UART0_INIT();
	can2_init();
	
	UART0_STR("NODE A\r\n");
	
	m1.id=0x000001AF;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0xDDCCBBAA;
	m1.byteB=0;
	

	while(1)
		{
		UART0_STR("TX\r\n");
		can2_tx(m1);//data-frame
		delay(1);
		}
}
