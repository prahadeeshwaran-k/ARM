#ifndef	DELAY_H
#define DELAY_H

#include <stdint.h>
#include <LPC21xx.H>

void delay(uint32_t sec);
void delay_ms(uint32_t ms);
void delay_micro(uint32_t micro);

#endif // DELAY_H
