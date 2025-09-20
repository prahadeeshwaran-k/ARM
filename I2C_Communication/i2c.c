#include "i2c.h"

void i2c_init(void)
{
	 PINSEL0|=SCL_EN|SDA_EN;
	 I2SCLL=LOADVAL;
	 I2SCLH=LOADVAL;
	 I2CONSET=1<<I2EN_BIT; 
}	

void i2c_start(void)
{
I2CONSET=1<<STA;
while(((I2CONSET>>SI)&1)==0);
I2CONCLR=1<<STA;
}

void i2c_restart(void)
{
I2CONSET=1<<STA;
I2CONCLR=1<<SI;
while(((I2CONSET>>SI)&1)==0);
I2CONCLR=1<<STA;
}

void i2c_write(unsigned char data)
{
I2DAT=data;
I2CONCLR=1<<SI;
while(((I2CONSET>>SI)&1)==0);
}

char i2c_ack(void)
{
I2CONSET=1<<AA;
I2CONCLR=1<<SI;
while(((I2CONSET>>SI)&1)==0);
I2CONCLR=1<<AA;
return I2DAT;
}

char i2c_nack(void)
{
I2CONSET=0x00;
I2CONCLR=1<<SI;
while(((I2CONSET>>SI)&1)==0);
return I2DAT;
}

void i2c_stop(void)
{
I2CONSET=1<<STO;
I2CONCLR=1<<SI;
}
