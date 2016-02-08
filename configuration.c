/*
 * File:   configuration.c
 * Author: Shaun
 *
 * Created on February 1, 2016, 8:33 AM
 */

#include "xc.h"
#include "configuration.h"

void PinConfig(){
    ANSELA = 0; //set all A ports to digital (turn analog off)
    ANSELB = 0; //set all B ports to digital 

    _TRISA0 = 0; //set RA0 to output
    _TRISA1 = 0; //set RA1 to output
    _TRISA2 = 0; //set RA2 to output
    _TRISA3 = 0; //set RA3 to output
    _TRISB0 = 0; //set RB0 to output
    _TRISB1 = 0; //set RB1 to output
    _TRISB2 = 0; //set RB2 to output
    _TRISB3 = 0; //set RB3 to output
    _TRISB14 = 1; //set RB14 to input
    _TRISB15 = 1; //set RB15 to input

}
void AnalogConfig(){
    
}
void TimerConfig(){
    
}

void InputConfig(){
    _CNIEB14 = 1;

}
