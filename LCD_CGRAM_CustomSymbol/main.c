#include <LPC21XX.H>
#include "delay.h"
#include "LCD.H"

void CGRAM_WRITE(unsigned int nBytes);
unsigned char CGRAM_lut[]={
	0x17,0x14,0x1f,0x05,0x05,0x1d,0x00
	};
int main(){
	LCD_INIT();
	LCD_COMMAND(0X80);
	CGRAM_WRITE(8);
	LCD_COMMAND(0x87);
	LCD_COMMAND(0);
}
void CGRAM_WRITE(unsigned int nBytes){
	unsigned char i;
	LCD_COMMAND(0X40);
	for(i = 0;i < nBytes;i++)
		LCD_DATA(CGRAM_lut[i]);
}
