#include <LPC21XX.H>
#include <string.h>
#include <stdlib.h>
#include "Delay.h"
#include "LCD.h"

int main() {
    unsigned char str[] = "Vector";
    int len = strlen((char*)str);
    int pos;

    LCD_INIT();
    delay_ms(20);  // extra wait after init

    while (1) {
        // Move string from left to right
        for (pos = 0; pos <= (16 - len); pos++) {
            LCD_COMMAND(0x01);            // Clear display
            delay_ms(2);                  // Important delay after clear
            LCD_COMMAND(0x80 + pos);      // Set cursor to row 1
            LCDPrintString(str);
            delay_ms(300);                // Adjust speed
        }

        // Move back from right to left
        for (pos = (16 - len - 1); pos >= 1; pos--) {
            LCD_COMMAND(0x01);            // Clear display
            delay_ms(2);
            LCD_COMMAND(0x80 + pos);
            LCDPrintString(str);
            delay_ms(300);
        }
    }
}
