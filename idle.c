/*
 * File:   idle.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:09 AM
 */

// TODO- for some reason when you go to pitch select then back to idle it will automatically go back to pitch select

#include "xc.h"
#include "idle.h"
#include "configuration.h"
#include "accel.h"
#include <math.h>

/*
 @return the next state
 */
int idle(void) {
    extern int w,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,A1x,A1y,A1z,A2x,A2y,A2z,A3x,A3y,A3z,A4x,A4y,A4z;
    extern float A0x,A0y,A0z, alphax, alphay, alphaz, wx, wy, wz, psi, phi, theta, psidot, phidot, thetadot;
    
    float accel_threshold = 5.0; // TODO- change
    
    //timer2 for sleep mode - if any other interrupt then reset
    //button, timer for sleep mode - if pressed for multiple seconds then sleep mode
    extern int t2;
    _T2IF = 0;
    _T2IE = 1;
    TMR2 = 0; // set count to 0
    T2CONbits.TON = 1; // turn timer2 on
    int num_seconds = 0;
    t2 = 0;
    
    //timer1 for pitch selection
    extern int t1;
    _T1IF = 0;
    _T1IE = 1;
    TMR1 = 0; // set count to 0
    t1 = 0;
    
    //enable change notification 
    extern int cn;
    _CNIE = 1; //enables cn interrupt
    _CNIF = 0; // clear interrupt flag
    
    void stop_interrupts()
    {
        T2CONbits.TON = 0; // turn timer2 off
        TMR2 = 0; // set count to 0
        _T2IF = 0;
        _T2IE = 0;
        
        //timer1 for pitch selection
        _TON = 0; // turn timer1 off
        TMR1 = 0; // set count to 0
        _T1IF = 0;
        _T1IE = 0;
        
        //disable change notification 
        _CNIE = 0;
        
    }
    
//    char c = uartGetChar();
    
    while(1)
    {
        // SLEEP
        // go to sleep if no other mode selected after 5 minutes
        if(t2){
            t2 = 0;
            num_seconds+=3;
        }
        if(num_seconds >= 300){
            stop_interrupts();
            return SLEEP; // go to sleep mode0
        }
        
        // PITCH SELECTION AND CHARGING
        // go to charging on charging pin        
        if(cn)
        {
            cn = 0;
            // check charging
            if (CHARGEIN){
                stop_interrupts();
                return CHARGING;
            }else if (BUT1INOFF == 0 && BUT2INOFF == 0)
            {
                _TON = 1; // turn on timer
                TMR1 = 0; // set timer1 count to 0
           }else
            {
                _TON = 0; // turn off timer
            }
        }
        //if timer1 hits 3 seconds go to pitch selection
        if(t1){
           t1 = 0;
           stop_interrupts();
           return PSELECT; 
        }
        // go to pitch selection mode on button hold
        //if button input pin value changes

      
        // THROWING
//        char buffer[8]="";
//        float * data = GetAccelData(buffer);
//        float avg = (pow(data[0],2.0)+pow(data[1],2.0)+pow(data[2],2.0))/3.0;
//        if (avg >= accel_threshold)
//            return THROWING;
        
        
    }   
    
    return(IDLE);
}
