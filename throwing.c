/*
 * File:   throwing.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:30 AM
 */


#include "xc.h"
#include "throwing.h"
#include "accel.h"

/*
 @return the next state
 */
int throwing(void) {
    
    extern int A1, A2, A3, A4;
    extern int w,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
    
    char buffer[8]="";
    
    while(1){
        x1 = ReadX1(A1, buffer); //read x axis
        y1 = ReadY1(A1, buffer); //read y axis
        z1 = ReadZ1(A1, buffer); 

        x2 = ReadX1(A2, buffer);
        y2 = ReadY1(A2, buffer);
        z2 = ReadZ1(A2, buffer);

        x3 = ReadX2(A3, buffer);
        y3 = ReadY2(A3, buffer);
        z3 = ReadZ2(A3, buffer);

        x4 = ReadX2(A4, buffer);
        y4 = ReadY2(A4, buffer);
        z4 = ReadZ2(A4, buffer);
    }
}
