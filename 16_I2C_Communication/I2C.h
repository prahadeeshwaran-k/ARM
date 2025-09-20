#ifndef I2C_H
#define I2C_H
#include <LPC21XX.H>


#define SCL  0x00000010
#define SDA  0x00000040

#define CCLK      60000000  //Hz
#define PCLK      CCLK/4    //Hz
#define I2C_SPEED 100000    //Hz
#define LOADVAL   ((PCLK/I2C_SPEED)/2)

#define I2EN 	(1<<6) //Enable/Disable bit
#define START   (1<<5) //Start Set/Clear bit
#define STOP  	(1<<4) //Stop bit
#define SI   	(1<<3) //Serial Interrupt Flag Clear bit
#define AACK   	(1<<2) //Assert Acknowledge Set/Clear bit

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_Write(unsigned char data);
unsigned char I2C_ReadNACK(void);
unsigned char I2C_ReadACK(void);

#endif // I2C_H
