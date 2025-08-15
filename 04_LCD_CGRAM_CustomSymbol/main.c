#include <LPC21XX.H>
#include "delay.h"
#include "LCD.H"

unsigned char CGRAM_lut[8]   = { 0x17,0x14,0x14,0x1F,0x05,0x05,0x1D,0x00};
unsigned char heart[8]       = { 0x00,0x0A,0x1F,0x1F,0x1F,0x0E,0x04,0x00 };
unsigned char smiley[8]      = { 0x00,0x0A,0x00,0x00,0x11,0x0E,0x00,0x00 };
unsigned char sad[8]         = { 0x00,0x0A,0x00,0x00,0x0E,0x11,0x00,0x00 };
unsigned char arrowRight[8]  = { 0x04,0x06,0x1F,0x06,0x04,0x00,0x00,0x00 };
unsigned char arrowLeft[8]   = { 0x04,0x0C,0x1F,0x0C,0x04,0x00,0x00,0x00 };
unsigned char battery[8]     = { 0x0E,0x11,0x11,0x11,0x11,0x1F,0x1F,0x00 };

// Function writes a given 8-byte pattern to a CGRAM location
void CGRAM_WRITE(unsigned char location, unsigned char* pattern) {
		int i ;
    LCD_COMMAND(0x40 + (location * 8)); // Set CGRAM address
    
    for (i = 0; i < 8; i++) {
        LCD_DATA(pattern[i]); // Write the byte from the passed-in pattern
    }
}

int main() {
    LCD_INIT();

    // Store all custom characters in CGRAM by passing the arrays directly
    CGRAM_WRITE(0, CGRAM_lut);
    CGRAM_WRITE(1, heart);
    CGRAM_WRITE(2, smiley);
    CGRAM_WRITE(3, sad);
    CGRAM_WRITE(4, arrowRight);
    CGRAM_WRITE(5, arrowLeft);
    CGRAM_WRITE(6, battery);

    // Display them on first line
    LCD_COMMAND(0x80);
    LCD_DATA(0);
    LCD_DATA(1);
    LCD_DATA(2);
    LCD_DATA(3);
    LCD_DATA(4);
    LCD_DATA(5);
    LCD_DATA(6);

    while(1);
}
