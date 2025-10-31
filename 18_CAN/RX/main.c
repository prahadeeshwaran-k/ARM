/* main_nodeA_TX.c */
#include "header.h"
main(){	
	CAN2_MSG m1;
	//m2;
	can2_init();
	/*sending data frame*/
	m1.id=0x000001AF;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0xDDCCBBAA;
	m1.byteB=0;
	
	/*m2.id=0x5;
	m2.dlc=7;
	m2.rtr=1;*/
	while(1)
		{		
		can2_tx(m1);//data-frame
		delay_s(1);
		/*can2_tx(m2);//remote frame
		delay_ms(2000);*/
		//can2_rx(&m2);
		}
}

