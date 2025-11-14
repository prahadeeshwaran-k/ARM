/* main_nodeB_RX.c */
#include <LPC21XX.H>
#include "can2.h"
#include "uart.h"
main(){	
	CAN2_MSG m1;
	can2_init();
	uart0_init(115200);
	uart0_tx_string("nodeB TESTING CAN\r\n");
	while(1){		
		can2_rx(&m1);
		
		if(m1.rtr==0){
			uart0_tx_string("nodeB: DATA-FRAME is received\r\n");
			uart0_tx_hex(m1.id);
			uart0_tx(' ');
			uart0_tx_hex(m1.dlc);
			uart0_tx(' ');
			uart0_tx_hex(m1.byteA);
			uart0_tx(' ');
			uart0_tx_hex(m1.byteB);
			uart0_tx_string("\r\n");
		}	
		else{
			uart0_tx_string("nodeB: REMOTE-FRAME is received\r\n");
			uart0_tx_hex(m1.id);
			uart0_tx(' ');
			uart0_tx_hex(m1.dlc);
			uart0_tx(' ');
			uart0_tx_string("\r\n");
		}	
	}
}

