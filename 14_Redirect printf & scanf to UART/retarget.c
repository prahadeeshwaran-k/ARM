#include <LPC21xx.h>
#include <stdio.h>
#include "uart.h"

struct __FILE { int handle; };
FILE __stdout;
FILE __stdin;

int fputc(int c, FILE *stream)
{
    if(c == '\n') {
        uartWrite('\r');   // add CR before LF
    }
    uartWrite(c);
    return c;
}

int fgetc(FILE *stream)
{
    char c = uartRead();
    uartWrite(c);  // echo back
    return c;
}
	