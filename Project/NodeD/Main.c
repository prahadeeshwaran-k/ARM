/* main_nodeA_TX.c */
#include <LPC21xx.H>
#include <stdio.h>
#include "uart.h"
#include "can2.h"
#include "Delay.h"
#include "timer.h" 

main(){	
	CAN2_MSG m1;
	VPBDIV = 0x01;
	IODIR0 |= (1<<6) | (1<<7);

	uart0_init(115200);
	can2_init();

	uart0_tx_string("NODE D\r\n");
	/*sending data frame*/
	m1.id=0x00000003;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0;
	m1.byteB=0;
	
	while(1)
		{ 	
			if(((IOPIN0>>2)&1)==1){
				IOCLR0 = (1<<6) | (1<<7);
				uart0_tx_string("HeadLight: ON\r\n");
				m1.byteA=1;
				can2_tx(m1);//data-frame
				
			}else{
				IOSET0 = (1<<6) | (1<<7);
				uart0_tx_string("HeadLight: OFF\r\n");
				m1.byteA=0;
				can2_tx(m1);//data-frame
				
			}	
			delay_ms(1010); //wait 1 second for next update	
		}
}

