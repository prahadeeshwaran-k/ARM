#include <LPC21xx.h>
#include "Delay.h"
#include "UART.h"
#include "LCD.h"

int main(void)
{
		unsigned char ch[16];
    initUART0();
		LCD_INIT();

    printf("LPC2129 UART0 Assignment 3");
		LCD_COMMAND(0x80);
		LCDPrintString("Name:");
    while(1)
    {		printf("\nEnter Name: ");
				scanf("%s",ch);
        printf("\nHello %s",ch);
				LCD_COMMAND(0xC0);
				LCDPrintString(ch);     
    }


}
