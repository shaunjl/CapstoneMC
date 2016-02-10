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
#define LED1       _RB2  
#define LED2	   _RB3
#define BUT1       _RB15

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    _T1IF = 0;
//    if (LED2)
//    {
//        LED2 = 0;
////        LED1G = 1;
//    }
//    else
//    {
//    LED2 = 1;
//    }
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    _CNIF = 0;
    if (BUT1)
        LED1 = 1;
    else
        LED1 = 0;
}

int main() {
 
    AnalogConfig();
    PinConfig();
    TimerConfig();
    InputConfig();
    LED1 = 0;

    while(1)
        ;

    
    return (0);
}
