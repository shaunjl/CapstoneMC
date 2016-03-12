/*
 * File:   sleep.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:29 AM
 */


#include "xc.h"
#include "sleep.h"
#include "accel.h"
#include <math.h>
#include "configuration.h"

/*
 @return the next state
 */
int sleep(void) {
    
    float accel_threshold = 5.0; // TODO- change
    
    while(1){
        // CHARGING
        // go to charging on charging pin
        if(_CNIF)
        {
            _CNIF = 0;
            // check charging
            if (CHARGEIN){
                return 3;
            }
        }
        // IDLE
        char buffer[8]="";
        float * data = GetAccelData(buffer);
        float avg = (pow(data[0],2.0)+pow(data[1],2.0)+pow(data[2],2.0))/3.0;
        if (avg >= accel_threshold)
            return 0;
    }
    
    return 0;
}
