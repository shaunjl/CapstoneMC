/*
 * File:   main.c
 * Author: Shaun
 *
 * Created on February 1, 2016, 8:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24ep128GP202.h>
#include "configuration.h"

// Select 8 mhz frc clock
_FOSCSEL(FNOSC_FRC);
//set output registers to the LEDs and input to Buttons
#define LED1R      _RA0  
#define LED1G      _RA1  
#define LED2R	   _RB0
#define LED2G	   _RB1
#define LED3R	   _RB2
#define LED3G	   _RB3
#define LED4R	   _RA2
#define LED4G	   _RA3
#define BUT1       _RB14
#define BUT2       _RB15


void _ISR _T1Interrupt(void)
{
    printf("Interrupt");
    _T1IF = 0;
    
    if (LED1G == 1)
    {
        LED1G = 0;
        LED1R = 1;
    }
    else if (LED1G == 0)
    {
        LED1R = 0;
        LED1G = 1;
    }
}

int main() {
 
    AnalogConfig();
    PinConfig();
    TimerConfig();
    LED1G = 1;
    LED1R = 1;

    while(1)
        ;

    
    return (0);
}
