/*
 * File:   p_select.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:31 AM
 */


#include "xc.h"
#include "p_select.h"
#include "configuration.h"

/*
 @return the next state
 */
int p_select(void) {
    // spherical coordinates
    extern float psi, phi, theta;
    extern int PITCH;
    
    // Set up Timer3
    TMR3 = 0;
    _T3IF = 0;
    T3CONbits.TON = 1;
    
    while(1){
        
        //Flash LED 
        if(_T3IF){
            _T3IF = 0;
            if (LED1I)
                LED1O = 0;
            else
                LED1O = 1;     
        }
        // SELECT PITCH
        //if button input pin value changes
        if(_CNIF)
        {
            _CNIF = 0;
            if (BUT1IN && BUT2IN) // if pressing both buttons
            {
                // TODO - get phi, phi, theta values
                // depending on orientation of ball set PITCH
                LED1O = 0;
                return 0;
            }
        }
    
    }
    return 0;
}
