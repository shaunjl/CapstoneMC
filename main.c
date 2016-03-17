/*
 * File:   main.c
 * Author: capstone team 23
 *
 * Created on February 1, 2016, 8:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24ep512GP204.h>
#include "configuration.h"
#include "i2c_helper.h"
#include "accel.h"
#include "idle.h"
#include "sleep.h"
#include "throwing.h"
#include "charging.h"
#include "p_select.h"
#include "app_config.h"
#include "pairing.h"

// Select 8 mhz frc clock
_FOSCSEL(FNOSC_FRC);

_FOSC(OSCIOFNC_ON); //Need to do this so that the pins that LED6 and LED12 are on are i/o pins and not always on.

_FICD(ICS_PGD2 & JTAGEN_OFF) // communicate on PGD2 and turn off JTAGEN so can do i2c1
_FPOR(ALTI2C1_OFF & ALTI2C2_OFF) //map i2c1 and i2c2 to the right pins

char buffer[8]="";

int main()
{
    
    extern int A1, A2, A3, A4;
    extern int PITCH;
    
    
    PinConfig();
//    LED5_11R = 1;
//    LED5_11G = 1;
   
    TimerConfig();  
    
    // I2C Config
    //i2c1_init(194); //start up i2c1
    //i2c2_init(194); //start up i2c2
    
    //Accel1Config(A1, buffer); //configures accelerometer on I2C1 line
    //Accel1Config(A2, buffer); //configures accelerometer on I2C1 line
    //Accel2Config(A3, buffer); 
    //Accel2Config(A4, buffer);
    // Initialize to IDLE mode, RISE ball
    PITCH = RISE;
    
    int state = THROWING; // TODO- change to IDLE
    while(1){
        switch ( state ) {
            case IDLE:
                state = idle();
                break;
            case SLEEP:
                state = sleep();
                break;
            case THROWING:
                state = throwing();
                break;
            case CHARGING:
                state = charging();
                break;
            case PSELECT:
                state = p_select();
                break;
            case APPCONFIG:
                state = app_config();
                break;
            case PAIRING:
                state = pairing();
                break;
            default:
                state = idle();
                break;
            }
    }
    
//    extern int t1,t2,t3,t4,t5;
//    T5CONbits.TON = 1;
//    _T5IE = 1;
//    LED1_7R = 0;
//    
//    while(1){
//           
//        if(t5)
//        {
//            t5 = 0;
//            if(LED1_7R == 0)
//            {
//                
//                LED1_7R = 1;
//            }
//         else
//            {
//                LED1_7R = 0;
//                
//            }
//        }
//            
//       
//        
//        
////            LED6_12G = 0;
////            LED1_7R = 1;
////            
////            Delay(1000);
////        
////        
////       
////            LED1_7R = 0;
////            LED1_7G = 1;
////        
////            Delay(1000);
////        
////        
////            LED2_8R = 1;
////            LED1_7G = 0;
////       
////            Delay(1000);
////        
////        
////            LED2_8R = 0;
////            LED2_8G = 1;
////        
////            Delay(1000);
////        
////        
////            LED3_9R = 1;
////            LED2_8G = 0;
////        
////            Delay(1000);
////        
////        
////            LED3_9R = 0;
////            LED3_9G = 1;
////        
////            Delay(1000);
////        
////              
////     
////            LED3_9G = 0;
////            LED4_10R = 1;
////        
////            Delay(1000);
////        
////        
////            LED4_10R = 0;
////            LED4_10G = 1;
////        
////            Delay(1000);
////        
////       
////            LED4_10G = 0;
////            LED5_11R = 1;
////        
////            Delay(1000);
////        
////        
////            LED5_11R = 0;
////            LED5_11G = 1;
////       
////            Delay(1000);
////        
////       
////            LED5_11G = 0;
////            LED6_12R = 1;
////        
////            Delay(1000);
////        
////     
////            LED6_12R = 0;
////            LED6_12G = 1;
////          
////            Delay(1000);
//        
//    }
    return (0);
}


         
