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
#define LED1I       _RB2  
#define LED1O      _LATB2
#define LED2I 	    _RB3
#define LED2O      _LATB3
#define BUT1I       _RB14
#define BUT2I       _RB15

//void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
//{
//    _T1IF = 0;
//   if (LED2I)
//    {
//    LED1O = 1;
//    LED2O = 0;
//    }
//    else
//    {
//    LED1O = 0;
//    LED2O = 1;
//    }
//}

//void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
//{
//    _CNIF = 0;
//    if (BUT1I)
//        LED1O = 1;
//    else
//        LED1O = 0;
//}

int main() {
 
    AnalogConfig();
    PinConfig();
    TimerConfig();
    InputConfig();
    LED1O = 0;

    while(1)
    {
        //if button value changes
        if(_CNIF)
        {
            _CNIF = 0;
            if (BUT1I && BUT2I)
            {
                _TON = 1; // turn on timer
                TMR1 = 0; // set timer1 count to 0
            }else
            {
                _TON = 0; // turn off timer
            }
        }
        //if timer hits 4 seconds
        if(_T1IF){
            _T1IF = 0; 
            LED1O = 1;
        }
    }   
    return (0);
}
