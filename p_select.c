/*
 * File:   p_select.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:31 AM
 */


#include "xc.h"
#include "p_select.h"

//void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
//{
//    _T1IF = 0;
//   if (LED2I)
//    {
//    LED1O = 1;
//    LED2O = 0;
//    }
//    else
//    {
//    LED1O = 0;
//    LED2O = 1;
//    }
//}

//void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
//{
//    _CNIF = 0;
//    if (BUT1I)
//        LED1O = 1;
//    else
//        LED1O = 0;
//}


//main file for button prototype
//int main() {
// 
//    AnalogConfig();
//    PinConfig();
//    TimerConfig();
//    InputConfig();
//    LED1O = 0;

//    while(1)
//    {
        //if button value changes
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
//    }   
//    return (0);
//}

//experimenting with I2C main function


/*
 @return the next state
 */
int p_select(void) {
    return 0;
}
