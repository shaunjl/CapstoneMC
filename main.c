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
//_FOSCSEL(FNOSC_FRC);
// FOSCSEL
//#pragma config FNOSC = FRCDIVN          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
//#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)
//
//// FGS
//#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
//#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

//set output register B0 to the LEDs
#define LED1     _RB0  


int main() {
 
    AnalogConfig();
    PinConfig();
    TimerConfig();

    while(1)
    {
        
        LED1 = 1;
        
        //if (ADC1BUF1 > 100);
       //    _RA0 = 1;

    
    
    }
    
    return (0);
}
