/*
 * File:   configuration.c
 * Author: Shaun
 *
 * Created on February 1, 2016, 8:33 AM
 */


#include "xc.h"
#include "configuration.h"

void PinConfig(){
    _ANSA0 = 0; //set Port A0 to digital
    _TRISA0 = 0; //set RA0 to output
    

}
void AnalogConfig(){
    
}
void TimerConfig(){
    
}