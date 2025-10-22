#ifndef __UART0_H__
#define __UART0_H__

#include <LPC21XX.H>



void UART0_INIT(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
void UART0_STR(const char *);
void UART0_HEX32(unsigned int value);

#endif  // __UART0_H__
