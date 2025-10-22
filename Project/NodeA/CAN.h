#ifndef __CAN_H__
#define __CAN_H__

#include <LPC21xx.H>



typedef struct CAN2
{
	unsigned int id;
	unsigned int rtr;
	unsigned int dlc;
	unsigned int byteA;
	unsigned int byteB;
}CAN2_MSG;

void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);

#endif  // __CAN_H__
