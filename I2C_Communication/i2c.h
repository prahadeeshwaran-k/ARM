#ifndef I2C_H
#define I2C_H
#include <LPC21xx.H>


#define SCL_EN  0x00000010
#define SDA_EN  0x00000040
 
#define CCLK      60000000  //Hz
#define PCLK      CCLK/4    //Hz
#define I2C_SPEED 100000    //Hz
#define LOADVAL   ((PCLK/I2C_SPEED)/2)

#define AA 2
#define SI 3
#define STO 4
#define STA 5
#define I2EN_BIT 6

#define IRQ_Slot_En 0x20
#define UART0_En 6

void i2c_init(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_write(unsigned char);
char i2c_ack(void);
char i2c_nack(void);
void i2c_stop(void);

#endif // I2C_H
