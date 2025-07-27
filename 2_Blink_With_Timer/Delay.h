//Delay For Seconds
void delay(int sec){
	T0PR = 15000000 - 1; //Assign The Prescaler Value
	T0TCR = 0x01;				 //Enable The Counter Register T0TC & TOPC
	while(T0TC < sec){	 //Wait for the T0TV meet the condition
	T0TCR = 0X03;				 //Reset the T0TC Counter
	T0TCR = 0X00;				 //Disable the Counter Register T0TC & TOPC
	}
}

//Delay For MilleSeconds
void delay_ms(int ms){
	T0PR = 15000 - 1;
	T0TCR = 0x01;
	while(T0TC < ms){
	T0TCR = 0X03;
	T0TCR = 0X00;
	}
}

//Delay For MicroSeconds
void delay_micro(int micro){ 
	T0PR = 15 - 1;
	T0TCR = 0x01;
	while(T0TC < micro){
	T0TCR = 0X03;
	T0TCR = 0X00;
	}
}
