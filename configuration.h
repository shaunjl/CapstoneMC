#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <p24ep512GP204.h>

// Define types of ball
#define RISE  0
#define DROP  1
#define SCREW 2
#define CURVE 3

//set output registers to the LEDs. R for Red. G for green.
#define LED1_7R     _LATA7  
#define LED1_7G     _LATA10
#define LED2_8R 	_LATB13
#define LED2_8G     _LATB12
#define LED3_9R     _LATC7
#define LED3_9G     _LATC6
#define LED4_10R    _LATB6
#define LED4_10G    _LATB5
#define LED5_11R    _LATA9
#define LED5_11G    _LATA4
#define LED6_12R    _LATA3
#define LED6_12G    _LATA2


//set input from charging
#define CHARGEIN     _RB13
//set input from buttons
#define BUT1IN       _RC3
#define BUT2IN       _RC8

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

