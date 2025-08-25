#include <LPC21xx.h>
#include "Delay.h"
#include "UART.h"
#include "LCD.h"

int main(void)
{
		char ch;
    initUART0();
		LCD_INIT();

    printf("LPC2129 UART0 Assignment 2");
		LCD_COMMAND(0x80);
		LCDPrintString("OppositeCase:");
    while(1)
    {		printf("\nEnter a Character: ");
				scanf("%c",&ch);
				if((ch >= 'a' && ch <= 'z') ||(ch >= 'A' && ch <= 'Z'))
						ch = ch^32;
        printf("\nThe Opposite Case is: %c",ch);
				LCD_COMMAND(0xC0);
				LCD_DATA(ch);        
    }


}
