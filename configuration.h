#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <p24ep128GP202.h>

// Define types of ball
#define RISE  0
#define DROP  1
#define SCREW 2
#define CURVE 3

//set output registers to the LEDs
#define LED1I        _RB2  
#define LED1O       _LATB2
#define LED2I 	     _RB3
#define LED2O       _LATB3
//set input from charging
#define CHARGEIN     _RB13
//set input from buttons
#define BUT1IN       _RB14
#define BUT2IN       _RB15

// Define all states
#define IDLE          0
#define SLEEP         1
#define THROWING      2
#define CHARGING      3
#define PSELECT       4
#define APPCONFIG     5
#define PAIRING       6

void PinConfig();
void AnalogConfig();
void TimerConfig();
void InputConfig();
void ConfigTimer5(unsigned tckps, unsigned pr5, unsigned t5ip);
void AccelTimerConfig();

#endif	/* CONFIGURATION_H */

