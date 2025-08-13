#include <lpc21xx.h>
#include "Delay.h"   // Your delay_ms() function
#include "LCD.h"     // Your LCD init and send functions
#include <string.h>

char msg[] = "Hello Bye Bye Bye ... Bye Bye Bye  "; // Extra spaces for smooth wrap

void scroll_text(char *str) {
    int i, j;
    int len = strlen(str);
    

    for (i = 0; i < len; i++) {
        LCD_COMMAND(0x80); // Move to first line, position 0
        for (j = 0; j < 16; j++) {
            LCD_DATA(str[(i + j)%len]); // Print character with wrap-around
        }
        delay_ms(300); // Delay between shifts
    }
}

int main(void) {
    LCD_INIT(); // Initialize LCD
		scroll_text(msg);
    while (1) {
         
    }
}
