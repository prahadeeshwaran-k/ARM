#include "SPI.h"

void SPI_INIT(void)
{
	PINSEL0 |= 0x00001500;              // P0.4 SCK0, P0.5 MISO0, P0.6 MOSI0, P0.7 GPIO (CS)
    S0SPCCR  = 600;                     // ~100 kHz if PCLK=60 MHz
    S0SPCR = (1<<3) | (1<<4) | (1<<5);  // CPHA=1, CPOL=1, MSTR=1 (Mode 3)
    IODIR0  |= (1<<7);                  // P0.7 as output (CS)
    IOSET0   = (1<<7);                  // CS HIGH (idle)
}

unsigned char SPI_Write(unsigned char data)
{
	S0SPDR = data;  /* Load data to be written into the data register */
	while ( (S0SPSR & 0x80) == 0 );  /* Wait till data transmission is completed */
	return S0SPDR;  /* Return the data received */

}

unsigned char SPI_Read(void)
{
	S0SPDR = 0x00;  /* Transmit Flush byte */
	while ( (S0SPSR & 0x80) == 0 );  /* Wait till data transmission is completed the flag rised in the SPIF_BIT*/
	return S0SPDR;  /* Return the data received */
}
