#include "I2C.h"

void I2C_Init(void) {	
	//Configure I/O pin for SCL & SDA functions using PINSEL0
	// PINSEL0 = 0X00000050;
	PINSEL0 |= SCL | SDA;
	//Configure Speed for I2C Serial Communication
	I2SCLL=LOADVAL;
	I2SCLH=LOADVAL;
	//I2C Peripheral Enable for Communication
	I2CONSET = I2EN;
}


int I2CWaitForSI(void) //Wait till I2C0 block sets SI
{
	int timeout = 0;
	while ( !(I2CONSET & SI) ) //Wait till SI bit is set. This is important!
	{
		timeout++;
		if (timeout > 10000) return 0; //In case we have some error on bus
	}
	return 1; //SI has been set
}


void I2C_Start(void)
{
	I2CONCLR = START | STOP | SI | AACK; //Clear everything
	I2CONSET = START; //Set start bit to send a start condition
	I2CWaitForSI(); //Wait till the SI bit is set
	I2CONCLR = START;
}


void I2C_Stop(void)
{
	int timeout = 0;
	I2CONSET = STOP ; //Set stop bit to send a stop condition
	I2CONCLR = SI;
	//But in Sir Code
	//stop will cleared automatically
	//while(((I2CONSET>>STO_BIT)&1));//He commented
	while (I2CONSET & STOP) //Wait till STOP is send. This is important!
	{
		timeout++;
		if (timeout > 10000) //In case we have some error on bus
		{
			return;
		}
	}
}


void I2C_Restart(void)
{
	// start condition
	I2CONSET = START;
	//clr SI_BIT
	I2CONCLR = SI;
	//wait for SI bit status
	I2CWaitForSI();
	// clear start condition
	I2CONCLR = START;
}	


void I2C_Write(unsigned char data)
{
 	I2DAT = data;
	I2CONCLR = START | STOP | SI; //Clear These to TX data
	I2CWaitForSI(); //wait till TX is finished
}

//When to use which?
//I2C_ReadACK() ? Use for every byte you read except the last one (keeps slave sending data).
//I2C_ReadNACK() ? Use for the last byte to signal the end of reading (slave stops sending).

//Read a byte and send NACK
//1.When master has finished reading the last byte, it must send NACK to the slave, so the slave stops sending data.
//2.To do this, AA must be cleared (AA=0) before clearing SI.
//3.After that, STOP condition is usually issued.

unsigned char I2C_ReadNACK(void)
{	
	I2CONSET = AACK;   			// clear ACK bit ? send NACK
  	I2CONCLR = SI;   			// clear ACK bit ? send NACK
	while(((I2CONSET>>SI)&1)==0);   // wait for SI
	return I2DAT;						// return received data
}
//Read a byte and send ACK
//1.When master is reading multiple bytes from a slave, it must acknowledge every byte except the last one.
//2.Setting AA = 1 tells the hardware to automatically send ACK to the slave after reading.
//3.This function returns the received byte from I2DAT.

unsigned char I2C_ReadACK(void)
{	
	I2CONSET = 1 << AACK;   // assert ACK
  	I2CONCLR = 1 << AACK;   // clear SI to start read
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR = 0x04; //  Assert Ack
 	return I2DAT; // return received data

}

//“Assert ACK” = setting AA=1, which tells the hardware to generate an ACK on the bus after a byte is received.
//It’s how the master signals “I want more data.”
