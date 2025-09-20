#ifndef AT24C08_H
#define AT24C08_H

#include <LPC21xx.h>
#include "I2C.h"

unsigned char I2C_eeprom_read(unsigned char slaveAddr,unsigned char rBuffAddr);
void I2C_eeprom_write(unsigned char slaveAddr,unsigned char wBuffAddr,unsigned char dat);
void I2C_eeprom_seq_read(unsigned char slaveAddr,unsigned char rBuffStartAddr,unsigned char *p,unsigned char nBytes);
void I2C_eeprom_page_write(unsigned char slaveAddr,unsigned char wBuffStartAddr,unsigned char *p,unsigned char nBytes);

#endif // AT24C08_H



