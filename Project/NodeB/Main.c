/* main_nodeA_TX.c */

#include <LPC21xx.H>

#include <stdint.h>

#include <stdio.h>

#include "uart.h"

#include "timer.h"


#define TRIG (1<<2) //P0.2

#define ECHO (1<<3) //P0.3
#define motor (1<<8)





typedef unsigned int u32;

typedef 	signed int s32;

typedef unsigned char u8;

typedef 	signed char s8;

typedef unsigned short int u16;

typedef   signed short int s16;


typedef struct CAN2

{

	u32 id;

	u32 rtr;

	u32 dlc;

	u32 byteA;

	u32 byteB;

}CAN2_MSG; 


int echoTime=0;

float distance=0;

int temp;


void can2_init(void){

	PINSEL1|=0x00014000;//P0.23-->RD2 & P0.24-->TD2

	//VPBDIV=1; //PCLK=60MHz


	C2MOD=0x1; //CAN2 into Reset  Mode 

	AFMR=0x2; //accept all receiving messages(data/remote)

	

	C2BTR=0x001C001D; //B125Kbps @ PLCK=60MHz(BRP=Pclk/bit rate*16)

	

	C2MOD=0x0; //CAN1 into Normal Mode

}


void can2_tx(CAN2_MSG m1)

{

  C2TID1=m1.id;

	C2TFI1=(m1.dlc<<16);	

	if(m1.rtr==0) //if data frame

	{

		C2TFI1&=~(1<<30);//RTR=0

		C2TDA1=m1.byteA; //lower 4bytes of data

		C2TDB1=m1.byteB; //upper 4bytes of data

	}

	else{

		C2TFI1|=(1<<30); //RTR=1

	}

	C2CMR=(1<<0)|(1<<5);//Start Xmission & select Tx Buf1

	//C2CMR=(3<<0)|(1<<5);//Start Xmission & select Tx Buf1

	while((C2GSR&(1<<3))==0);//wait for data Xmission.

}


void can2_rx(CAN2_MSG *m1){

	while((C2GSR&0x1)==0);

	m1->id=C2RID;

	m1->dlc=(C2RFS>>16)&0xF;

	m1->rtr=(C2RFS>>30)&0x1;

	if(m1->rtr==0){ //if data frame

		m1->byteA=C2RDA;

		m1->byteB=C2RDB;

	}

	C2CMR=(1<<2);//free receiver buffer(imp)

}


main(){	

	CAN2_MSG m1;

	VPBDIV = 0x01;


	initTimer0(); //Init Timer for delay functions

	uart0_init(115200);

	can2_init();


	IO0DIR |= TRIG | motor;    //Set P0.2(TRIG) as output

	IO0DIR &= ~(ECHO); //Set P0.3(ECHO) as input (explicitly)

	IO0CLR |= TRIG;    //Set P0.2 LOW initially


	uart0_tx_string("HC-SR04 Sensor\r\n");

	/*sending data frame*/

	m1.id=0x00000001;

	m1.rtr=0;//data frame

	m1.dlc=4;

	m1.byteA=0;

	m1.byteB=0;

	

	while(1)

		{

		IO0SET |= TRIG;

		delayUS(10);

		IO0CLR |= TRIG;


		while(!(IO0PIN & ECHO)); //Wait for a HIGH on ECHO pin

		startTimer0(); //Start counting

		while(IO0PIN & ECHO); //Wait for a LOW on ECHO pin

		echoTime = stopTimer0(); //Stop counting and save value(us) in echoTime


		distance = (0.0343 * echoTime)/2; //Find the distance

		temp = distance;

		if(temp > 20){
				IOSET0 = motor;
				uart0_tx_string("RUN ");
		}
		else{
			   IOCLR0 = motor;
			   uart0_tx_string("STOP ");
		}


		uart0_tx_float(temp);

		uart0_tx_string("\r\n");

		m1.byteA=distance;

		can2_tx(m1);//data-frame

		delayMS(1000); //wait 1 second for next update

		}

}