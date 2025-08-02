#include <LPC21XX.H>
#include <stdlib.h>
#include "Delay.h"
#include "LCD.h"

#define BUTTON_1 10
#define BUTTON_2 11
#define BUTTON_3 12

//Note: If ther is No '\0' termination it will print all the  Characters 
unsigned char Message[4][17] = {
    {"NoButton Pressed\0"},
    {"Button 1 Pressed\0"},
    {"Button 2 Pressed\0"},
    {"Button 3 Pressed\0"}
};

int main() {
 
		LCD_INIT();
    while (1) {
        LCD_COMMAND(0x80); // Move cursor to first line
        if (!((IOPIN0 >> BUTTON_1) & 1)) {
            LCDPrintString(Message[1]); 
        } else if (!((IOPIN0 >> BUTTON_2) & 1)) {
            LCDPrintString(Message[2]);
        } else if (!((IOPIN0 >> BUTTON_3) & 1)) {
            LCDPrintString(Message[3]);
        } else {
						LCDPrintString(Message[0]);
        }
        delay_ms(200);  	// Debounce delay
    }
}
