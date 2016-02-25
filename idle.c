/*
 * File:   idle.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:09 AM
 */


#include "xc.h"
#include "idle.h"
#include "configuration.h"

/*
 @return the next state
 */
int idle(void) {
    return 0;
    //timer for sleep mode - if any other interrupt then reset
    //button, timer for sleep mode - if pressed for multiple seconds then sleep mode

    while(1)
    {
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
