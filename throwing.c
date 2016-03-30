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
    extern float A0x,A0y,A0z, alphax, alphay, alphaz, wx, wy, wz, psi, phi, theta, psidot, phidot, thetadot;
   
    char buffer[8]="";
    float timestep = .001;
   
    // set all values to zero
    void zeroVals(){
        wx=0.0;wy=0.0;wz=0.0;
        psi=0.0;phi=0.0;theta=0.0;
    }
    
    // Zero all vals
    zeroVals();
    
  
    
    AccelTimerConfig();
    
    while(1){
        
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
        
        A0x = (A1x+A2x+A3x+A4x)/4.0; //find balls x-acceleration in its own frame
        A0y = (A1y+A2y+A3y+A4y)/4.0; //find balls y-acceleration in its own frame
        A0z = (A1z+A2z+A3z+A4z)/4.0; //find balls z-acceleration in its own frame
        
               
        alphaz = (.015*(A1y-A0y) + .015*(A4x - A0x))/(.00045); //calculate angular acceleration about the ball's z-axis
        alphax = -1*(A0z-A2z+wy*wz*.015)/.015;  //calculate angular acceleration about the ball's x-axis (numerically)
        alphay = (A0z-A1z+wx*wz*.015)/.015;  //calculate angular acceleration about the ball's y-axis (numerically)
        
        
        
        wx = wx + alphax*timestep;  //calculate angular velocity about ball's x-axis (numerically)
        wy = wy + alphay*timestep;  //calculate angular velocity about ball's y-axis (numerically)
        wz = wz + alphaz*timestep;  //calculate angular velocity about ball's z-axis (numerically)
                
//        
//        if(_T4IF)
//        {
//            _T4IF = 0;
//            if(_RB2)
//            {
//                _LATB2 = 0;
//            }
//            if(_RB2==0)
//            {
//                _LATB2 = 1;
//            }
//        }

      
    }
    
    // VALLAN- Make sure that wherever you decide to return you call zeroVals() right before you return
    zeroVals();
    
    return 0;
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
