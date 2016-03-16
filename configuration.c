#include "xc.h"
#include "configuration.h"

int PITCH;

// read from the RA and RB bits but write to the LAT bits
void PinConfig(){
    ANSELA = 0; //set all A ports to digital (turn analog off)
    ANSELB = 0; //set all B ports to digital 
    ANSELC = 0; //set all C ports to digital

    //LED pins
    _TRISA2 = 0; 
    _TRISA3 = 0; 
    _TRISA4 = 0;
    _TRISA7 = 0;
    _TRISA9 = 0;
    _TRISA10 = 0;
    _TRISB5 = 0;
    _TRISB6 = 0;
    _TRISB12 = 0;
    _TRISB13 = 0;
    _TRISC6 = 0;
    _TRISC7 = 0;
    
    
    //_TRISB0 = 0; //set RB0 to output
    //_TRISB1 = 0; //set RB1 to output
    //_TRISB2 = 0; //set RB2 to output
    //_TRISB3 = 0; //set RB3 to output
    //_TRISB14 = 1; //set RB14 to input
    //_TRISB15 = 1; //set RB15 to input
    
    //_CVREN = 0;  // turn off cvref pin to be used for i2c
    //_SPI1MD = 1;  //Turn SCK off to be used for I2C
    //_TRISB8 = 0;  //RB8 as output for I2C
    //_TRISB9 = 0;  //RB9 as output for I2X

}
void AnalogConfig(){
    
}

// Note- this doesn't turn the timers on- you must turn them on to use
void TimerConfig(){
    //timer 1 - 3 second timer
    // 16 bit counter, 8 MHz clock (4 MHz cycles)
    // this means PRx/(4Mhz/TCKPS)) seconds between interrupts 
    _TON = 0; //timer1 off
    _TCKPS = 0b11; // 1 count: 256 cycles
    PR1 = 46875; //number to count to
    _TSYNC = 0; // do not sync to external clock
    _TCS = 0; // no external clock source
    _T1IP = 4; // Interrupt priority
    _T1IE = 0; // Enable interrupt
    _T1IF = 0; // Clear interrupt flag
    TMR1 = 0; // set timer1 count to 0 initial
   
    //timer 2 - 3 second timer
    // 16 bit counter, 8 MHz clock (4 MHz cycles)
    // this means PRx/(4Mhz/TCKPS)) seconds between interrupts 
    T2CONbits.TON = 0; //timer2 off
    T2CONbits.TCKPS = 0b11; // 1 count: 256 cycles
    PR2 = 46875; //number to count to
    T2CONbits.TCS = 0; // no external clock source
    _T2IP = 4; // Interrupt priority
    _T2IE = 0; // Enable interrupt
    _T2IF = 0; // Clear interrupt flag
    TMR2 = 0; // set timer2 count to 0 initial
   
    //timer 3 - 1 second timer
    // 16 bit counter, 8 MHz clock (4 MHz cycles)
    // this means PRx/(4Mhz/TCKPS)) seconds between interrupts 
    T3CONbits.TON = 0; //timer3 off
    T3CONbits.TCKPS = 0b11; // 1 count: 256 cycles
    PR3 = 15625; //number to count to
    T3CONbits.TCS = 0; // no external clock source
    _T3IP = 4; // Interrupt priority
    _T3IE = 0; // Enable interrupt
    _T3IF = 0; // Clear interrupt flag
    TMR3 = 0; // set timer3 count to 0 initial
    
    //timer 5 - Configurable timer (default 3 second)
    // 16 bit counter, 8 MHz clock (4 MHz cycles)
    // this means PRx/(4Mhz/TCKPS)) seconds between interrupts 
    T5CONbits.TON = 0; //timer3 off
    T5CONbits.TCKPS = 0b11; // 1 count: 256 cycles
    PR5 = 46875; //number to count to
    T5CONbits.TCS = 0; // no external clock source
    _T5IP = 4; // Interrupt priority
    _T5IE = 0; // Enable interrupt
    _T5IF = 0; // Clear interrupt flag
    TMR5 = 0; // set timer5 count to 0 initial
}

// read from the RA and RB bits


void InputConfig(){
    // Charging Pin
    _CNIEB13 = 1; //Enable Change Notification bit for B13 
    _CNPUB13 = 0; //Disable pull-up resistor
    _CNPDB13 = 0; //Disable pull-down resistor
    // Button 1
    _CNIEB14 = 1; //Enable Change Notification bit for B14 
    _CNPUB14 = 0; //Disable pull-up resistor
    _CNPDB14 = 0; //Disable pull-down resistor
    // Button 2
    _CNIEB15 = 1; //Enable Change Notification bit for B15 
    _CNPUB15 = 0; //Disable pull-up resistor
    _CNPDB15 = 0; //Disable pull-down resistor
    _CNIP = 6; // set interrupt priority
    _CNIE = 0; // Enable CN interrupts
    _CNIF = 0; // clear interrupt flag
    
}

void ConfigTimer5(unsigned tckps, unsigned pr5, unsigned t5ip){
    T5CONbits.TCKPS = tckps;
    PR5 = pr5;
    _T5IP = t5ip;
}

void AccelTimerConfig(){
    //timer 4 - 1/1000 second timer
    // 16 bit counter, 8 MHz clock (4 MHz cycles)
    // s 
    T4CONbits.TON = 0; //timer2 off
    T4CONbits.TCKPS = 0b00; // 1 count: 1 cycles
    PR4 = 3999; //number to count to 3999
    T4CONbits.TCS = 0; // no external clock source
    _T4IP = 4; // Interrupt priority
    _T4IE = 0; // Enable interrupt
    _T4IF = 0; // Clear interrupt flag
    TMR4 = 0; // set timer4 count to 0 initial
    T4CONbits.TON = 1;
}