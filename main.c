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
//set output register B0 to the LEDs
#define LEDR      _RA0  
#define LEDG      _RA1  

int main() {
 
    AnalogConfig();
    PinConfig();
    TimerConfig();

    while(1)
    {
        LEDG = 1;
        LEDR = 1;
    }
    
    return (0);
}
