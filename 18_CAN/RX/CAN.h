#ifndef CAN_H
#define CAN_H

#include <LPC21xx.H>

//CMR CAN Command Registers
#define TR (1<<0)   //: Transmission Requests 
#define AT (1<<1)   //: Abort Transmission 
#define RRB (1<<2)  //: Release Receiver Buffer 
#define CDO (1<<3)  //: Clear Data Overrun 
#define SRR (1<<4)  //: Self Reception Request 
#define STB1 (1<<5) //: Select Tx Buffer 1 for transmission 
#define STB2 (1<<6) //: Select Tx Buffer 2 for transmission 
#define STB3 (1<<7) //: Select Tx Buffer 3 for transmission

//GSR CAN Gobal Status Registers
#define RSB (1<<0) //: Receive Buffer Status
#define TCS (1<<3) //: Transmit Complete Status 

typedef union {
    struct {
        unsigned int TFL_RESERVED1:16;  // bits 0..15
        unsigned int DLC          :4;   // bits 16..19
        unsigned int TFL_RESERVED2:10;  // bits 20..29
        unsigned int RTR          :1;   // bit  30
        unsigned int TFL_RESERVED3:1;   // bit  31
    } b;
    unsigned int raw;                  // same 32-bit storage
} TxFrameInfo;

typedef struct can {
    unsigned int TDA;  // Lower bytes
    unsigned int TDB;  // Upper bytes
    TxFrameInfo  TFI;  // Tx Frame Info (bitfields + raw view)
    unsigned int ID:11; // 11-bit CAN ID
} Frame;

typedef struct CAN2
{
	unsigned int id;
	unsigned int rtr;
	unsigned int dlc;
	unsigned int byteA;
	unsigned int byteB;
}CAN2_MSG;

#endif // CAN_H