#include <LPC21XX.H>
#include <stdint.h>
#include "Delay.h"
#include "LCD.h"

int main(void)
{
    const char msg[] = "BAD Boy Bala__";
		unsigned len = 0;
    unsigned offset = 0;
    int i, j, k;
    unsigned char frame[16];
	
    LCD_INIT();
    LCD_COMMAND(0x01);
    delay_ms(2);
	
		while (msg[len] != '\0') { len++; }
    if (len == 0) { return 0; }

    while(1){
				for (j = 0; j < 16; j++) {
            k = (offset + j) % len;//len +8 provide space ;ring = len + 8;
						if(k < len)
								frame[j] = msg[k];
						else
								frame[j] = ' ';  
        }
				
        LCD_COMMAND(0x80);
				
				for (i = 0; i < 16; i++)
						LCD_DATA(frame[i]);
				
        delay_ms(200);
        offset++;
        if (offset == len) { offset = 0; }
	}
}


