/* main_nodeA_TX.c */
#include <LPC21xx.H>
#include <stdio.h>
#include "uart.h"
#include "can2.h"
#include "Delay.h"
main(){	
	CAN2_MSG m1;
	int i;
	VPBDIV = 0x01;

	uart0_init(115200);
	can2_init();

	uart0_tx_string("NODE C\r\n");
	/*sending data frame*/
	m1.id=0x00000002;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0;
	m1.byteB=0;
	
	while(1)
		{
			for(i=0;i<100;i += 5){
				uart0_tx_string("Speed: ");
				uart0_tx_integer(i);
				uart0_tx_string("\r\n");
		   		m1.byteA=i;
				can2_tx(m1);//data-frame
				delay_ms(700); //wait 1 second for next update
				}
		}
}

