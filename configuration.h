#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <p24ep128GP202.h>

void PinConfig();
void AnalogConfig();
void TimerConfig();
void InputConfig();
void I2C1Config(char addr, char* buffer);
void I2C2Config(char addr, char* buffer);
int ReadX(char addr, char* buffer);
int ReadY(char addr, char* buffer);
int ReadZ(char addr, char* buffer);
int ReadX2(char addr, char* buffer);
int ReadY2(char addr, char* buffer);
int ReadZ2(char addr, char* buffer);
#endif	/* CONFIGURATION_H */

