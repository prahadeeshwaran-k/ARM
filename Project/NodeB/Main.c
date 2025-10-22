//NODE B Main File
#include <LPC21XX.H>
#include "Delay.h"
#include "UART.h"
#include "CAN.h"
#include "LCD8Bit.h"

CAN2_MSG m1;

int main(){
	
	VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz
	UART0_INIT();
	UART0_STR("NODE B\r\n");
	can2_init();
		

	while(1)
		can2_rx(&m1);
		
		if(m1.rtr == 0){
			UART0_STR("nodeB: DATA-FRAME is received\r\n");
			UART0_HEX32(m1.id);
			UART0_TX(' ');
			UART0_HEX32(m1.dlc);
			UART0_TX(' ');
			UART0_HEX32(m1.byteA);
			UART0_TX(' ');
			UART0_HEX32(m1.byteB);
			UART0_STR("\r\n");
		}	
		else{
			UART0_STR("nodeB: REMOTE-FRAME is received\r\n");
			UART0_HEX32(m1.id);
			UART0_TX(' ');
			UART0_HEX32(m1.dlc);
			UART0_TX(' ');
			UART0_STR("\r\n");
		}
}
