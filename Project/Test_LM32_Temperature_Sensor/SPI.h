#ifndef SPI_H_
#define SPI_H_
#include <LPC21xx.h>

void SPI_INIT(void);
unsigned char SPI_Write(unsigned char);
unsigned char SPI_Read(void);

#endif /* SPI_H_ */
