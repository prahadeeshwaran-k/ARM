#ifndef EEPROM_H
#define EEPROM_H

#include <LPC21xx.H>
#include "i2c.h"


void i2c_eeprom_write(unsigned char,unsigned short int,unsigned char);
unsigned char i2c_eeprom_read(unsigned char,unsigned short int);
void i2c_eeprom_page_write(unsigned char,unsigned short int,unsigned char *,unsigned char);
void i2c_eeprom_seq_read(unsigned char,unsigned short int,unsigned char *,unsigned char);
void i2c_eeprom_data_clear(unsigned char,unsigned short int,unsigned char,unsigned short int);

#endif // EEPROM_H
