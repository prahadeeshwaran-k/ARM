#include<LPC21XX.H>
#include"Delay.h"

int DigitalRead(int pin){
	return ((IOPIN0>>pin)&1);
}

void PressButton(int led, int button){
	if((DigitalRead(button)==0)){
			IOCLR0 = 1<<led;
		}else{
			IOSET0 = 1<<led
		}
}

int main(){													  
	IODIR0=0x0F;
	IOSET0=0x0F;
	while(){
		PressButton(0,4);
		PressButton(1,5);
		PressButton(2,6);
		PressButton(3,7);
	}
}