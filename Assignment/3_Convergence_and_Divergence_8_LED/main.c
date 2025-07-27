#include<LPC21XX.H>
#include <stdint.h>
#include "Delay.h"
#define N 10

int main(){
	int i,j,k;
	IODIR0 = 0XFF;
	IOSET0 = 0XFF;//For active Low LEDs, set all the 8 LED  to off state 
	
	for(i=0;i<N;++i){
		for(j=7,k=0;j>k;--j,k++){
			IOCLR0 = (1<<j|1<<k); //Turning ON the LED by setting the j-th pin to '0' (active low)
			delay_ms(500);  			// Delay For 500 ms
			IOSET0 = (1<<j|1<<k); //Turning OFF the LED by setting the j-th pin to '1' (active low)
			delay_ms(500);
		}
		delay(1);
		
		++j,--k;
		for(;j<=7 && k>=0;--j,k++){
			IOCLR0 = (1<<j|1<<k); //Turning ON the LED by setting the j-th pin to '0' (active low)
			delay_ms(500);        // Delay For 500 ms
			IOSET0 = (1<<j|1<<k); //Turning OFF the LED by setting the j-th pin to '1' (active low)
			delay_ms(500);
		}
		delay(1);
	}
	return 0;
}
