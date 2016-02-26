/*
 * File:   idle.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:09 AM
 */


#include "xc.h"
#include "idle.h"
#include "configuration.h"
#include "accel.h"

/*
 @return the next state
 */
int idle(void) {
    return 0;
    //timer for sleep mode - if any other interrupt then reset
    //button, timer for sleep mode - if pressed for multiple seconds then sleep mode
    
    TMR3 = 0; // set count to 0
    T3CONbits.TON = 1; // turn timer3 on
    int num_minutes = 0;
    
    while(1)
    {
        // go to sleep if no other mode selected after 5 minutes
        if(_T3IF){
            _T3IF = 0;
            num_minutes++;
        }
        if(num_minutes >= 5){
            T3CONbits.TON = 0; // turn timer3 off
            TMR3 = 0; // set count to 0
            return 1; // go to sleep mode
        }
//        //if button value changes
//        if(_CNIF)
//        {
//            _CNIF = 0;
//            if (BUT1I && BUT2I)
//            {
//                _TON = 1; // turn on timer
//                TMR1 = 0; // set timer1 count to 0
//           }else
//            {
//                _TON = 0; // turn off timer
//            }
//        }
//        //if timer hits 4 seconds
//        if(_T1IF){
//           _T1IF = 0; 
//            LED1O = 1;
//            _TON = 0;
//        }
    }   
    return(0);
}
