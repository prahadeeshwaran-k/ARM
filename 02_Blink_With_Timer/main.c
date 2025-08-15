#include <LPC21XX.H>
#include "Delay.h"

int main(){
	IODIR0 = 0x00;
	while(1){
		IOSET0 = 0x01;
		delay(1);
		IOCLR0 = 0x01;
		delay(1);
	}
}
