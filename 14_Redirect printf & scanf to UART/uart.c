#include <LPC21xx.h>

void initUART0(void)
{
    PINSEL0 |= 0x00000005;   // Enable TxD0 (P0.0) and RxD0 (P0.1)

    U0LCR= 1<<7 | 3<<0; //0x83 to turn on the 7bit
		U0DLL = 0X97;
		U0DLM = 0;
		U0LCR = 0X03;
}


void uartWrite(char c)
{
    while(!(U0LSR & (1<<5)));   // Wait for THR empty
    U0THR = c;
}

char uartRead(void)
{
    while(!(U0LSR & (1<<0)));   // Wait for RDR = 1
    return U0RBR;
}
