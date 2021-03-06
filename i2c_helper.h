/* 
 * File:   i2c_helper.h
 * Author: vsherrod
 *
 * Created on February 15, 2016, 10:59 AM
 */

#ifndef I2C_HELPER_H
#define	I2C_HELPER_H
#include <p24ep512GP204.h>

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

char i2c2_read_ack(void);
char i2c2_read(void);
char send_i2c2_byte(int data);
void reset_i2c2_bus(void);
void i2c2_restart(void);
void i2c2_start(void);
void i2c2_init(int BRG);

void I2C2write(char addr, char sub, char value);
void I2C2write2bytes(char addr, char val1, char val2);
void I2C2write4bytes(char addr, char val1, char val2, char val3, char val4);
void I2C2requestFrom(char addr, char sub, char val, char* buffer);




#endif	/* I2C_HELPER_H */

