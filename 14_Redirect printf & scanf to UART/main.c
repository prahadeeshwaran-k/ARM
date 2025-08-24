#include <LPC21xx.h>
#include <stdio.h>
#include "uart.h"

int main(void)
{
    int num = 0;
    initUART0();

    printf("LPC2129 UART0 printf/scanf demo\r\n");

    while(1)
    {
        printf("Enter an integer between 0 and 1000: ");
        scanf("%d", &num);

        if(num >= 0 && num <= 1000)
            printf("\r\nYou entered: %d\r\n", num);
        else
            printf("\r\nInvalid input!\r\n");
    }

    return 0;
}
