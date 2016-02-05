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
    _TRISA0 = 0; //set RA0 to output
    _TRISA1 = 0; //set RA0 to output

}
void AnalogConfig(){
    
}
void TimerConfig(){
    
}