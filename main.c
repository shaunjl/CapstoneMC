/*
 * File:   main.c
 * Author: capstone team 23
 *
 * Created on February 1, 2016, 8:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24ep128GP202.h>
#include "configuration.h"
#include "i2c_helper.h"
#include "accel.h"
#include "idle.h"
#include "sleep.h"
#include "throwing.h"
#include "charging.h"
#include "p_select.h"
#include "app_config.h"
#include "pairing.h"

// Select 8 mhz frc clock
_FOSCSEL(FNOSC_FRC);
//set output registers to the LEDs and input to Buttons
#define LED1I       _RB2  
#define LED1O      _LATB2
#define LED2I 	    _RB3
#define LED2O      _LATB3
#define BUT1I       _RB14
#define BUT2I       _RB15

// Define all states
#define IDLE          0
#define SLEEP         1
#define THROWING      2
#define CHARGING      3
#define PSELECT       4
#define APPCONFIG     5
#define PAIRING       6

#define A1        0b00110010 //define address for accelerometer 1 (positive x-axis)
#define A2        0b00110000 //define address for accelerometer 2 (positive y-axis)
#define A3        0b00110010 //define address for accelerometer 3 (negative x-axis)
#define A4        0b00110000 //define address for accelerometer 4 (negative y-axis)

_FICD(ICS_PGD3 & JTAGEN_OFF) // communicate on PGD3 and turn off JTAGEN so can do i2c1
_FPOR(ALTI2C1_ON & ALTI2C2_ON) //map i2c1 and i2c2 to the right pins

char buffer[8]="";

int main()
{
    PinConfig();
    
    // I2C Config
    i2c1_init(194); //start up i2c1
    i2c2_init(194); //start up i2c2
    
    Accel1Config(A1, buffer); //configures accelerometer on I2C1 line
    Accel1Config(A2, buffer); //configures accelerometer on I2C1 line
    Accel2Config(A3, buffer); 
    Accel2Config(A4, buffer);
    
    
    int state = IDLE;
    while(1){
        switch ( state ) {
            case IDLE:
                state = idle();
                break;
            case SLEEP:
                state = sleep();
                break;
            case THROWING:
                state = throwing();
                break;
            case CHARGING:
                state = charging();
                break;
            case PSELECT:
                state = p_select();
                break;
            case APPCONFIG:
                state = app_config();
                break;
            case PAIRING:
                state = pairing();
                break;
            default:
                state = idle();
                break;
            }
    }
    return (0);
}
