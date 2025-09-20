#include "AT24C08.h"

void I2C_eeprom_write(unsigned char slaveAddr,unsigned char wBuffAddr,unsigned char dat)
{
	I2C_Start();	
	I2C_Write(slaveAddr<<1); //slaveAddr + w
	I2C_Write(wBuffAddr);    //wBuffAddr
	I2C_Write(dat);    //wBuffAddr
	I2C_Stop();
	delay_ms(10);
}			 

unsigned char I2C_eeprom_read(unsigned char slaveAddr,unsigned char rBuffAddr)
{
	unsigned char dat;
	I2C_Start();	
	I2C_Write(slaveAddr<<1); //slaveAddr + w
	I2C_Write(rBuffAddr);    //rBuffAddr
	I2C_Restart();	
	I2C_Write(slaveAddr<<1|1); //slaveAddr + r  
	dat = I2C_ReadNACK();	
	I2C_Stop();
	return dat;
}

void I2C_eeprom_page_write(unsigned char slaveAddr,unsigned char wBuffStartAddr,unsigned char *p,unsigned char nBytes)
{
	unsigned char i;
	I2C_Start();	
	I2C_Write(slaveAddr<<1);    //slaveAddr + w
	I2C_Write(wBuffStartAddr);  //wBuffStartAddr
	for(i=0;i<nBytes;i++)
	{
	   I2C_Write(p[i]);             //wBuffAddr
	}
	I2C_Stop();
	delay_ms(10);
}			 

void I2C_eeprom_seq_read(unsigned char slaveAddr,unsigned char rBuffStartAddr,unsigned char *p,unsigned char nBytes)
{
	unsigned char i;
	I2C_Start();	
	I2C_Write(slaveAddr<<1); //slaveAddr + w
	I2C_Write(rBuffStartAddr);    //rBuffAddr
	I2C_Restart();	
	I2C_Write(slaveAddr<<1|1); //slaveAddr + r
	for(i=0;i<nBytes-1;i++)
	{
    p[i]=I2C_ReadACK();	
	}
	p[i]=I2C_ReadNACK();
	I2C_Stop();
}
