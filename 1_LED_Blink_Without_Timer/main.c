#include<LPC21XX.H>
#define LED 0x01;

void delay_ms(int ms){
	unsigned int i;
	for(;ms>0;ms--){
		for(i=12000;i>0;i--);
	}
}

int main(){
	IODIR0 = 0x00000001; //P0.0 as output pin and reset as i/p pin
	while(1){
		IOSET0 = LED;		//Write Logic 1 to P0.0
		delay_ms(1000);	//wait for 1.sec
		IOCLR0 = LED;		//Write Logic 0 to P0.0
		delay_ms(1000);	//wait for 1.sec
	}
}
