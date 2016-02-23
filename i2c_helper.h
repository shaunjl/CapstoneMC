/* 
 * File:   i2c_helper.h
 * Author: capstone team 23
 *
 * Created on February 15, 2016, 10:59 AM
 */

#ifndef I2C_HELPER_H
#define	I2C_HELPER_H
#include <p24ep128GP202.h>

char i2c1_read_ack(void);
char i2c1_read(void);
char send_i2c1_byte(int data);
void reset_i2c1_bus(void);
void i2c1_restart(void);
void i2c1_start(void);
void i2c1_init(int BRG);

void I2C1write(char addr, char sub, char value);
void I2C1write2bytes(char addr, char val1, char val2);
void I2C1write4bytes(char addr, char val1, char val2, char val3, char val4);
void I2C1requestFrom(char addr, char sub, char val, char* buffer);



#endif	/* I2C_HELPER_H */

