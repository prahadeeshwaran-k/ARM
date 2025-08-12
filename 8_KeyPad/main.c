#include<LPC21XX.H>
#include"delay.h"
#include"LCD.h"
#include"KeyPad.h"


int main(){
	int result ;
	LCD_INIT();

	while(1){
		LCD_COMMAND(0x80);
		LCDPrintString("4X4 keypad");
		LCD_COMMAND(0xC0);
		result = keyScan();
		LCD_DATA((result/10)+48);
		LCD_DATA((result%10)+48);
		delay_ms(2000);
		LCD_COMMAND(0x01);
	}

}
