#include "UART.h"

void UART0_INIT(void)
{	
	
    PINSEL0 |= 0x05;     // P0.0 as TXD0 and P0.1 as RXD0
    U0LCR = 0x83;        // Enable DLAB and set 8-bit word length
    U0DLL = 135;          // Baud rate setting (assuming 60MHz PCLK ? 9600 baud)
    U0DLM = 1;
    U0LCR = 0x03;        // Disable DLAB, 8-bit data, 1 stop bit, no parity
	
}

void UART0_TX(unsigned char dat)
{
    while (((U0LSR >> 5) & 1) == 0);  // Wait for THR empty
    U0THR = dat;                      // Transmit character
}

unsigned char UART0_RX(void)
{
    while ((U0LSR & 1) == 0);  // Wait until data ready
    return U0RBR;              // Return received byte
}

void UART0_STR(const char *s)
{
    while (*s)
        UART0_TX((unsigned char)*s++);        // Transmit string
}

void UART0_HEX32(unsigned int value)
{
    unsigned char hex_digits[] = "0123456789ABCDEF";
    int i;

    UART0_STR("0x");
    for (i = 28; i >= 0; i -= 4)
    {
        UART0_TX(hex_digits[(value >> i) & 0xF]);
    }
}



