#include <LPC21XX.H>
#include <stdint.h>
#define INC_BUTTON (1 << 10)   // P0.10 -> Increase duty
#define DEC_BUTTON (1 << 11)   // P0.11 -> Decrease duty

void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

__irq void PWM_ISR (void)
{
	
	if ( PWMIR & 0x0008 )	/* If interrupt due to PWM3 */
	{
		PWMIR = 0x0008;	/* Clear PWM3 interrupt */
	}	
	VICVectAddr = 0x00000000;
}

int main (void)
{
	
	unsigned int value;
	value = 100; // Start at 1% duty cycle (10 / 1000)
	
	VPBDIV		= 0x00000001; /* PCLK = 60MHz */
	PINSEL0 = PINSEL0 | 0x00000008; /* Configure P0.1 as PWM3 */
	VICVectAddr0 = (unsigned) PWM_ISR; /* PWM ISR Address */
	VICVectCntl0 = (0x00000020 | 8); /* Enable PWM IRQ slot */
	VICIntEnable = VICIntEnable | 0x00000100; /* Enable PWM interrupt */
	VICIntSelect = VICIntSelect | 0x00000000; /* PWM configured as IRQ */
	
    /* Configure P0.10 and P0.11 as inputs */
    /* *** NOTE: You MUST use external pull-up resistors on these pins *** */
	IODIR0 &= ~(INC_BUTTON | DEC_BUTTON);

// For single edge controlled PWM3
	PWMTCR = 0x02; 	/* Reset and disable counter for PWM */
	PWMPR = 0x3B;	/* Prescale value for 1usec, Pclk=60MHz (59+1)*/
	PWMMR0 = 1000;	/* Time period of PWM wave, 1msec (1kHz) */
	PWMMR3 = value;	/* Ton of PWM wave */
	PWMMCR = 0x00000203;	/* Reset and interrupt on MR0 match, interrupt on MR3 match */
	PWMLER = 0x09;	/* Latch enable for PWM3 and PWM0 */
	PWMPCR = 0x0800;	/* Enable PWM3 and PWM0, single edge controlled PWM on PWM3 */
	PWMTCR = 0x09;	/* Enable PWM and counter */
	
	PWMMR3 = 100;
    PWMLER = (1 << 3);
	while (1)
	{
		
		// Increase duty cycle (+10%) when P0.10 pressed
        if (!(IOPIN0 & INC_BUTTON))
        {
            value += 100;
            if (value > 1000)
                value = 1000; // Clamp at 100%

            PWMMR3 = value;
            PWMLER = (1 << 3);  /* <-- FIX: Latch new value for MR3 */
            delay_ms(200);      // debounce delay
        }
		
		// Decrease duty cycle (-10%) when P0.11 pressed
        if (!(IOPIN0 & DEC_BUTTON))
        {
            if (value >= 100)
                value -= 100;
            else
                value = 0; // Clamp at 0%

            PWMMR3 = value;
            PWMLER = (1 << 3);  /* <-- FIX: Latch new value for MR3 */
            delay_ms(200);      // debounce delay
        }
	}
	
	/*
	while (1)
	{
		while (value != 999)
		{
			PWMMR3 = value;
			PWMLER = 0x08;
			delay_ms(5);
			value++;
		}
		while (value != 1)
		{
			PWMMR3 = value;
			PWMLER = 0x08;
			delay_ms(5);
			value--;
		}	
	}
	*/
	
}
