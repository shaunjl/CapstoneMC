#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <p24ep128GP202.h>

void PinConfig();
void AnalogConfig();
void TimerConfig();
void InputConfig();
void ConfigTimer5(unsigned tckps, unsigned pr5, unsigned t5ip);
void AccelTimerConfig();

#endif	/* CONFIGURATION_H */

