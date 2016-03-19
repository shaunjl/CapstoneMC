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
    extern int t3, cn; //for timer3 and CN interrupts
    extern int PITCH;
    
    // Set up Timer3
    TMR3 = 0;
    _T3IF = 0;
    _T3IE = 1;
    T3CONbits.TON = 1;
    
    _CNIE = 1; //enables cn interrupt
    
    while(1){
        
        //Flash LED 
        if(t3){
            t3 = 0;
            if (LED6_12R){
                LED6_12R = 0;
            }else
                LED6_12R = 1;     
        }
        // SELECT PITCH
        //if button input pin value changes
        if(cn)
        {
            cn = 0;
            if (BUT1INOFF == 0 && BUT2INOFF == 0) // if pressing both buttons (they are equal to 0 if pressed)
            {
                // TODO - get phi, phi, theta values
                // depending on orientation of ball set PITCH
                LED6_12R = 0;
                LED6_12G = 1;
                Delay(1000);
                LED6_12G = 0;
                T3CONbits.TON = 0;
                TMR3 = 0;
                _T3IF = 0;
                _T3IE = 0;
                _CNIE = 0;
                return IDLE;
            }
            
        }
    
    }
    return 0;
}
