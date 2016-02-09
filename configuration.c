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
    // 16 bit counter, 8 MHz clock (4 MHz cycles)
    // this means 2^16/(4Mhz/256)) = 4.19 seconds between interrupts 
    _TON = 0; //timer1 off
    _TCKPS = 0b11; // 1 count: 256 cycles
    PR1 = 65000; //number to count to
    _TSYNC = 0; // do not sync to external clock
    _TCS = 0; // no external clock source
    _T1IP = 4; // Interrupt priority
    _T1IE = 1; // Enable interrupt
    _T1IF = 0; // Clear interrupt flag
    _TON = 1; //timer1 on
    TMR1 = 0; // set timer1 count to 0 initially
}

void InputConfig(){
    _CNIEB14 = 1;

}
