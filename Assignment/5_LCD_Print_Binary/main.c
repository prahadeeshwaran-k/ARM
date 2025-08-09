#include <LPC21XX.H>
#include <stdlib.h>
#include "Delay.h"
#include "LCD.h"
int main(){
	int num = 764;
	int i =0;
	unsigned char binary_str[32] ={0};
	
	LCD_INIT();
	LCD_COMMAND(0x80);
	for (i = 0; i < 32; i++) {
    if ((num >> (31 - i)) & 1)   // Shift original num by (31-i) to get MSB first
        binary_str[i] = '1';     // Store at current index 'i'
    else
        binary_str[i] = '0';
	}
	LCDPrintString(binary_str);
	
	return 0;

}

