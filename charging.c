/*
 * File:   charging.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:31 AM
 */


#include "xc.h"
#include "charging.h"
#include "configuration.h"

/*
 @return the next state
 */
int charging(void) {
    
    char buffer[8]="";
    extern int A1, A2, A3, A4;
    
    while(1)
    {
        LED6_12G = 1;
        
        I2C1requestFrom(A1, 0x0F, 1, buffer);
        
        if(buffer[0] == 0b00110010)
        {
            LED1_7R = 1;
        }
        
//        I2C1requestFrom(A2, 0x20, 1, buffer);
//        
//        if(buffer[0] == 0x3F)
//        {
//            LED2_8R = 1;
//        }
//        
//        I2C1requestFrom(A1, 0x23, 1, buffer);
//        
//        if(buffer[0] == 0x10)
//        {
//            LED3_9R = 1;
//        }
//        
//        I2C1requestFrom(A2, 0x23, 1, buffer);
//        
//        if(buffer[0] == 0x10)
//        {
//            LED4_10R = 1;
//        }
        
        
        
    }
    return 0;
}
