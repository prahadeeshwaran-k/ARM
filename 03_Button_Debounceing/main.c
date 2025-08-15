#include<LPC21XX.H>
#include"Delay.h"
#include"LCD.h"
#define SW 2

int main(){
	int count = 0;
	LCD_INIT();
	LCD_COMMAND(0X80);
	LCDPrintString("Switch Count");
	while(1){
		if(((IOPIN0>>SW)&1)==0){
			delay_ms(200);//to avoid the Switch Bounceing
			count++;
			LCD_COMMAND(0xC0);
			LCDPrintInt(count);
			while(((IOPIN0>>SW)&1)==0);//Wait For Switch Release
		}
	}
}
