#ifndef DELAY_H
#define DELAY_H
#include <stdint.h>

//Delay For Seconds
void delay(uint32_t sec){
	T0PR = 15000000 - 1; //Assign The Prescaler Value
	T0TCR = 0x01;				 //Enable The Counter Register T0TC & TOPC
	while(T0TC < sec); 	 //Wait for the T0TV meet the condition
	T0TCR = 0X03;				 //Reset the T0TC Counter
	T0TCR = 0X00;				 //Disable the Counter Register T0TC & TOPC
}

//Delay For MilleSeconds
void delay_ms(uint32_t  ms){
	T0PR = 15000 - 1;		 //Assign The Prescaler Value
	T0TCR = 0x01;				 //Enable The Counter Register T0TC & TOPC
	while(T0TC < ms);    //Wait for the T0TV meet the condition
	T0TCR = 0X03;				 //Reset the T0TC Counter
	T0TCR = 0X00;				 //Disable the Counter Register T0TC & TOPC
}

//Delay For MicroSeconds
void delay_micro(uint32_t micro){ 
	T0PR = 15 - 1;			//Assign The Prescaler Value
	T0TCR = 0x01;				//Enable The Counter Register T0TC & TOPC
	while(T0TC < micro);//Wait for the T0TV meet the condition
	T0TCR = 0X03;				//Reset the T0TC Counter
	T0TCR = 0X00;				//Disable the Counter Register T0TC & TOPC
}

#endif // DELAY_H
