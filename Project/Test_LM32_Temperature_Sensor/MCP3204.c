#include "MCP3204.h"

float MCP3204(unsigned char channelNo)
{
	unsigned char hByte,lByte;
	float adcVal=0;
	
	IO0CLR = (1<<7);  /* Enable SPI communication with slave */	
	SPI_Write(0x06);
	hByte = SPI_Write(channelNo<<6);
	lByte = SPI_Read();
	IO0SET = (1<<7);  /* SSEL = 1, disable SPI communication with slave */
	adcVal=((hByte & 0x0f) << 8) | lByte;
	
  return (float)((adcVal*3.3f)/4096.0f);
	
}

/*
Bit#:                  1| 2| 3| 4| 5| 6| 7 | 8|		| 9|10|11|_____12| 13| 14|15|16|	|17|18|19|20|21|22|23|24|
MCU TX (falling edge): 0| 0| 0| 0| 0| 1|S/D|D2|		|D1|D0| X|______X|  X|  X| X| X|	| X| X| X| X| X| X| X| X|
MCU RX (rising edge):  ?| ?| ?| ?| ?| ?| ? | ?|		| ?| ?| ?|0(NULL)|B11|B10|B9|B8|	|B7|B6|B5|B4|B3|B2|B1|B0|    

===========================================================
MCP3204/3208 SPI Communication Timing
===========================================================

MCU Transmitted Data (Aligned with falling edge of SCLK)
-----------------------------------------------------------
Bit#:   1  2  3  4  5  6  7  8
Data:   0  0  0  0  0  1  SGL/DIFF  D2

Bit#:   9 10 11 12 13 14 15 16
Data:   D1  D0  X  X  X  X  X  X

Bit#:  17 18 19 20 21 22 23 24
Data:   X  X  X  X  X  X  X  X
(X = “Don’t Care” Bits)


MCU Received Data (Aligned with rising edge of SCLK)
-----------------------------------------------------------
After 1st 8 bits transmitted:
Data:   ? ? ? ? ? ? ? ?    // Undefined during command phase

After 2nd 8 bits transmitted:
Data:   ? ? ? ? 0 (NULL) B11 B10 B9 B8

After 3rd 8 bits transmitted:
Data:   B7 B6 B5 B4 B3 B2 B1 B0

Notes:
------
- Data latched from ADC (DOUT) on rising edges of SCLK.
- Data sent to ADC (DIN) on falling edges of SCLK.
- Start bit = ‘1’
- SGL/DIFF: 1 = Single-ended, 0 = Differential mode
- D2, D1, D0 = Channel selection bits
- B11..B0 = 12-bit conversion result (MSB first)
===========================================================
*/
