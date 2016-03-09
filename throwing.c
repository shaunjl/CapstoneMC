/*
 * File:   throwing.c
 * Author: capstone team 23
 *
 * Created on February 23, 2016, 8:30 AM
 */


#include "xc.h"
#include "throwing.h"
#include "accel.h"
#include <math.h>



int binTwosComplementToSignedDecimal(char binary[],int significantBits);

/*
 @return the next state
 */
int throwing(void) {
    
    extern int A1, A2, A3, A4;
    extern int w,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,A1x,A1y,A1z,A2x,A2y,A2z,A3x,A3y,A3z,A4x,A4y,A4z;
    extern float A0x,A0y,A0z, alphax, alphay, alphaz, wx, wy, wz, psi, phi, theta;
    
    char buffer[8]="";
    float timestep = .001;
    
    wx = 0;
    wy = 0;
    wz = 0;
    
    psi = 0;
    phi = 0;
    theta = 0;
    
    _LATB2 = 1;
    
    AccelTimerConfig();
    
    while(1){
        //int l[8];
        //l[0] = 1;
        //l[1] = 1;
        //l[2] = 1;
        //l[3] = 1;
        //l[4] = 1;
        //l[5] = 1;
        //l[6] = 1;
        //l[7] = 0;
        
        //w = -1*l[0]*pow(2,7)+l[1]*pow(2,6)+l[2]*pow(2,5)+l[3]*pow(2,4)+l[4]*pow(2,3)+l[5]*pow(2,2)+l[6]*pow(2,1)+l[7]*pow(2,0);
        
        //l = 0xFE;
        //l = ~l;
        //l = l+1;
        //l = -l;
        //l = 0xFE;
        
        //w = binTwosComplementToSignedDecimal(l,8);
        
        //read data from accelerometers and put into correct global axes
        A1x = ReadX1(A1, buffer); //read x axis of accelerometer 1
        A1y = -1*ReadY1(A1, buffer); //read y axis of accelerometer 1
        A1z = -1*ReadZ1(A1, buffer); //read z axis of accelerometer 1

        A2x = ReadX1(A2, buffer); //read x axis of accelerometer 2
        A2y = -1*ReadY1(A2, buffer);  //read y axis of accelerometer 2
        A2z = -1*ReadZ1(A2, buffer);  //read z axis of accelerometer 2

        A3x = ReadX2(A3, buffer);  //read x axis of accelerometer 3
        A3y = -1*ReadY2(A3, buffer);  //read y axis of accelerometer 3
        A3z = -1*ReadZ2(A3, buffer);  //read z axis of accelerometer 3

        A4x = ReadX2(A4, buffer);  //read x axis of accelerometer 4
        A4y = -1*ReadY2(A4, buffer);  //read y axis of accelerometer 4
        A4z = -1*ReadZ2(A4, buffer);  //read z axis of accelerometer 4
        
        A0x = (A1x+A2x+A3x+A4x)/4.0;
        A0y = (A1y+A2y+A3y+A4y)/4.0;
        A0z = (A1z+A2z+A3z+A4z)/4.0;
        
        alphaz = (.015*(A1y-A0y) + .015*(A4x - A0x))/(.00045);
        
        alphax = -1*(A0z-A2z+wy*wz*.015)/.015;
        alphay = (A0z-A1z+wx*wz*.015)/.015;
        
        wx = wx + alphax*timestep;
        wy = wy + alphay*timestep;
        wz = wz + alphaz*timestep;
        
        
        if(_T4IF)
        {
            _T4IF = 0;
            if(_RB2)
            {
                _LATB2 = 0;
            }
            if(_RB2==0)
            {
                _LATB2 = 1;
            }
        }

      
    }
}

int binTwosComplementToSignedDecimal(char binary[],int significantBits) 
{
    int power = pow(2,significantBits-1);
    int sum = 0;
    int i;

    for (i=0; i<significantBits; ++i)
    {
        if ( i==0 && binary[i]!='0')
        {
            sum = power * -1;
        }
        else 
        {
            sum += (binary[i]-'0')*power;//The -0 is needed
        }
        power /= 2;
    }

    return sum;
}

//void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
//{
//    _T4IF = 0;
//            if(_RB2)
//            {
//                _LATB2 = 0;
//            }
//            if(_RB2==0)
//            {
//                _LATB2 = 1;
//            }
//}