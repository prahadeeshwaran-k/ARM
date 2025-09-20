#include <LPC21xx.h>
#include "Delay.h"
#include "SPI.h"
#include "MCP3204.h"
#include "LCD8Bit.h"
#include "uart.h"
#include <stdio.h>

int main()
{
	float f;
	SPI_INIT();
	LCD_INIT();
	UART0_CONFIG();
	LCDPrintString("MCP3204 ADC:");
    UART0_STR("LPC2129 MCP3204 ADC demo\r\n");
	while(1)
	{
		f = MCP3204(0);
		//LCD Printing
		LCD_COMMAND(0xC0);
		LCDPrintString("        "); // clear line
		LCD_COMMAND(0xC0);
		LCDPrintFloat3(f);
		//UART Printing
		UART0_STR("ADC: ");
		UART0_Float(f);
		UART0_STR("\r\n");
		
		delay_ms(500);
	}	
}
