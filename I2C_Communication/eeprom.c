#include "eeprom.h"
#include "Delay.h"

void i2c_eeprom_write(unsigned char slaveAddr,unsigned short int wBuffAddr,unsigned char dat)
{
  i2c_start();	
  i2c_write(slaveAddr<<1); //slaveAddr + w
  i2c_write(wBuffAddr);    //wBuffAddr
  i2c_write(dat);   	//data
  i2c_stop();
  delay_ms(10);
}			 

unsigned char i2c_eeprom_read(unsigned char slaveAddr,unsigned short int rBuffAddr)
{
  unsigned char data;
  i2c_start();	
  i2c_write(slaveAddr<<1); //slaveAddr + w
  i2c_write(rBuffAddr);    //rBuffAddr
  i2c_restart();	
  i2c_write(slaveAddr<<1|1); //slaveAddr + r  
  data=i2c_nack();	
  i2c_stop();
  return data;
}

void i2c_eeprom_page_write(unsigned char slaveAddr,unsigned short int wBuffStartAddr,unsigned char *p,unsigned char nBytes)
{
  unsigned char i;
  i2c_start();	
  i2c_write(slaveAddr<<1);    //slaveAddr + w
  i2c_write(wBuffStartAddr);  //wBuffStartAddr
  for(i=0;i<nBytes;i++)
	{
	   i2c_write(p[i]);             //wBuffAddr
	}
  i2c_stop();
  delay_ms(10);
}			 

void i2c_eeprom_seq_read(unsigned char slaveAddr,unsigned short int rBuffStartAddr,unsigned char *p,unsigned char nBytes)
{
  unsigned char i;
  i2c_start();	
  i2c_write(slaveAddr<<1); //slaveAddr + w
  i2c_write(rBuffStartAddr);    //rBuffAddr
  i2c_restart();	
  i2c_write(slaveAddr<<1|1); //slaveAddr + r
  for(i=0;i<nBytes-1;i++)
	{
    p[i]=i2c_ack();	
	}
	p[i]=i2c_nack();
  i2c_stop();
}

void i2c_eeprom_data_clear(unsigned char slaveAddr,unsigned short int BuffStartAddr,unsigned char bytes,unsigned short int total_bytes)
{
	unsigned short int i;
	for(i=0;i<total_bytes;i++)
	{
	i2c_eeprom_write(slaveAddr,BuffStartAddr+i,bytes);
	}
}

