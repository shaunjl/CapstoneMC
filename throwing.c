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
#include "configuration.h"



int binTwosComplementToSignedDecimal(char binary[],int significantBits);

/*
 @return the next state
 */
int throwing(void) {
    
    extern int A1, A2, A3, A4, t4, PITCH;
    extern int x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,A1x,A1y,A1z,A2x,A2y,A2z,A3x,A3y,A3z,A4x,A4y,A4z;
    extern float A0x,A0y,A0z,A0xi,A0yi,A0zi,V0xi,V0yi,V0zi, alphax, alphay, alphaz, wx, wy, wz, psi, phi, theta, psidot, phidot, thetadot;
   
    char buffer[8]="";
    float timestep = .001;
    
    float lx,ly, led_angle; //used to determine which leds to light up
    float w; //for angular velocity magnitude
    float alpha_range_good = .17;
    float alpha_range_ok = .35;
    
    //depending on the pitch set the value of the angular velocity thresholds
    float w_good, w_ok;
    
    if (PITCH == RISE)
    {
        w_good = 26;
        w_ok = 22;
    }
    else if (PITCH == DROP)
    {
        w_good = 23;
        w_ok = 20; 
    }
    else if (PITCH == CURVE)
    {
        w_good = 25;
        w_ok = 21;
    }
    else if (PITCH == SCREW)
    {
        w_good = 25;
        w_ok = 21;
    }
   
    // set all values to zero
    void zeroVals(){
        wx=0.0;wy=0.0;wz=0.0;
        psi=0.0;phi=0.0;theta=0.0;
        V0xi=0.0;V0yi=0.0;V0zi=0.0;
    }
    
    // Zero all values
    zeroVals();
    
  
    
    AccelTimerConfig();
    
    while(1){
        
        if(t4)
        {
            t4=0;
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
           
            if ((A0x > 2*9.81 || A0x < -2*9.81) || (A0y > 2*9.81 || A0y < -2*9.81) || (A0z > 2*9.81 || A0z < -2*9.81)) 
            {
                alphaz = (.015*(A1y-A0y) + .015*(A4x - A0x))/(.00045); //calculate angular acceleration about the ball's z-axis
                alphax = -1*(A0z-A2z+wy*wz*.015)/.015;  //calculate angular acceleration about the ball's x-axis (numerically)
                alphay = (A0z-A1z+wx*wz*.015)/.015;  //calculate angular acceleration about the ball's y-axis (numerically)



                wx = wx + alphax*timestep;  //calculate angular velocity about ball's x-axis (numerically)
                wy = wy + alphay*timestep;  //calculate angular velocity about ball's y-axis (numerically)
                wz = wz + alphaz*timestep;  //calculate angular velocity about ball's z-axis (numerically)
                
                w =  sqrt(powf(wx,2.0) + powf(wy,2.0) + powf(wz,2.0));

                
                phidot = wx + sin(phi)*tan(theta)*wy + cos(phi)*tan(theta)*wz; //calculate how phi is changing in time
                thetadot = cos(phi)*wy - sin(phi)*wz; //calculate how theta is changing in time
                psidot = sin(phi)/cos(theta)*wy + cos(phi)/cos(theta)*wz; //calculate how psi is changing in time

                theta = theta + thetadot*timestep; //calculate pitch
                phi = phi + phidot*timestep; //calculate roll
                psi = psi + psidot*timestep; //calculate yaw

                A0xi = A0x + sin(phi)*tan(theta)*A0y + cos(phi)*tan(theta)*A0z; //calculate acceleration in world x-frame
                A0yi = cos(phi)*A0y - sin(phi)*A0z; //calculate acceleration in world y-frame
                A0zi = sin(phi)/cos(theta)*A0y + cos(phi)/cos(theta)*A0z; //need to add in acceleration from gravity.  //calculate acceleration in world z-frame

                V0xi = V0xi + A0xi*timestep;  //calculate velocity in world x-frame
                V0yi = V0yi + A0yi*timestep;  //calculate velocity in world y-frame
                V0zi = V0zi + A0zi*timestep;  //calculate velocity in world z-frame
                
                
                // Find angle relative to expected
                
                //depending on the pitch set the value of the correct theta and psi in world frame
                float theta_right, psi_right;

                if (PITCH == RISE)
                {
                    theta_right = atan2(V0yi, V0xi) + PI/2;
                    psi_right = 0;
                }
                else if (PITCH == DROP)
                {
                    theta_right = atan2(V0yi, V0xi) - PI/2;
                    psi_right = 0; 
                }
                else if (PITCH == CURVE)
                {
                    theta_right = atan2(V0yi, V0xi) + PI/2;
                    psi_right = 3*PI/4;
                }
                else if (PITCH == SCREW)
                {
                    theta_right = atan2(V0yi, V0xi) - PI/2;
                    psi_right = PI/4;
                }
                
                // unit vector for ideal
                wxideal = cos(theta_right)*sin(psi_right);
                wyideal = sin(theta_right)*sin(psi_right);
                wzideal = cos(psi_right);
                
                //w in world frame
                wxi = cos(theta)*cos(psi)*wx + (sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi))*wy + (cos(phi)*sin(theta)*cos(psi)+sin(phi)*sin(psi))*wz;
                wyi = cos(theta)*sin(psi)*wx + (sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi))*wy + (cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi))*wz;
                wzi = -sin(theta)*wx + sin(phi)*cos(theta)*wy + cos(phi)*cos(theta)*wz;  
                
                // find angle between two vectors
                alpha = abs(acos((wxideal*wxi + wyideal*wyi + wzideal*wzi)/ w));
                
                //calculate which LEDs to light up by projecting the spin axis onto the x-y plane
                if(wy!=0) //if it is equal to zero then there will be a singularity and so we have to calculate it another way
                {
                    //find l, a vector perpendicular to the projection of the axis onto the x-y plane
                    lx = 1; //choose lx to be one
                    ly = -wx/wy; //calculate what ly must be to be perpendicular to the vector wx and wy (this condition is true based off of a dot product)
                    led_angle = atan2(ly,lx);  //calculate angle ly makes from the x-axis of the ball
                    
                    //light up the appropriate leds.
                    if((led_angle > -15*PI/180.0 && led_angle <= 15*PI/180.0) || (led_angle<= -165*PI/180.0) || (led_angle> 165*PI/180.0))
                    {
                        LED1_7G = 0;
                        LED1_7R = 0;
                        LED2_8R = 0;
                        LED2_8G = 0;
                        LED3_9R = 0;
                        LED3_9G = 0;
                        LED5_11G = 0;
                        LED5_11R = 0;
                        LED6_12G = 0;
                        LED6_12R = 0;
                        if (w >= w_good && alpha < alpha_range_good)
                        {
                            LED4_10G = 1;
                            LED4_10R = 0;
                        }
                        else if (w >= w_good && alpha < alpha_range_ok)
                        {
                            LED4_10R = 1;
                            LED4_10G = 1;
                        }
                        else
                        {
                            LED4_10R = 1;
                            LED4_10G = 0;
                        }
                        
                    }

                    else if ((led_angle > 15*PI/180.0 && led_angle <= 45*PI/180.0) || (led_angle > -165*PI/180.0 && led_angle <= -135*PI/180.0))
                    {
                        LED1_7G = 0;
                        LED1_7R = 0;
                        LED2_8R = 0;
                        LED2_8G = 0;
                        LED3_9R = 0;
                        LED3_9G = 0;
                        LED4_10R = 0;
                        LED4_10G = 0;
                        LED6_12G = 0;
                        LED6_12R = 0;
                        
                        if (w >= w_good && alpha < alpha_range_good)
                        {
                            LED5_11G = 1;
                            LED5_11R = 0;
                        }
                        else if (w >= w_good && alpha < alpha_range_ok)
                        {
                            LED5_11R = 1;
                            LED5_11G = 1;
                        }
                        else
                        {
                            LED5_11R = 1;
                            LED5_11G = 0;
                        }
                    }

                    else if ((led_angle > 45*PI/180.0 && led_angle <= 75*PI/180.0) || (led_angle > -135*PI/180.0 && led_angle <= -105*PI/180.0))
                    {
                        LED1_7G = 0;
                        LED1_7R = 0;
                        LED2_8R = 0;
                        LED2_8G = 0;
                        LED3_9R = 0;
                        LED3_9G = 0;
                        LED4_10R = 0;
                        LED4_10G = 0;
                        LED5_11G = 0;
                        LED5_11R = 0;
                        if (w >= w_good && alpha < alpha_range_good)
                        {
                            LED6_12G = 1;
                            LED6_12R = 0;
                        }
                        else if (w >= w_good && alpha < alpha_range_ok)
                        {
                            LED6_12R = 1;
                            LED6_12G = 1;
                        }
                        else
                        {
                            LED6_12R = 1;
                            LED6_12G = 0;
                        }                     
                    }

                    else if ((led_angle > 75*PI/180.0 && led_angle <= 105*PI/180.0) || (led_angle > -105*PI/180.0 && led_angle <= -75*PI/180.0))
                    {
                        LED2_8R = 0;
                        LED2_8G = 0;
                        LED3_9R = 0;
                        LED3_9G = 0;
                        LED4_10R = 0;
                        LED4_10G = 0;
                        LED5_11G = 0;
                        LED5_11R = 0;
                        LED6_12G = 0;
                        LED6_12R = 0;
                        if (w >= w_good && alpha < alpha_range_good)
                        {
                            LED1_7G = 1;
                            LED1_7R = 0;
                        }
                        else if (w >= w_good && alpha < alpha_range_ok)
                        {
                            LED1_7R = 1;
                            LED1_7G = 1;
                        }
                        else
                        {
                            LED1_7R = 1;
                            LED1_7G = 0;
                        }
                    }

                    else if ((led_angle > 105*PI/180.0 && led_angle <= 135*PI/180.0) || (led_angle > -75*PI/180.0 && led_angle <= -45*PI/180.0))
                    {
                        LED1_7G = 0;
                        LED1_7R = 0;
                        LED3_9R = 0;
                        LED3_9G = 0;
                        LED4_10R = 0;
                        LED4_10G = 0;
                        LED5_11G = 0;
                        LED5_11R = 0;
                        LED6_12G = 0;
                        LED6_12R = 0;
                        if (w >= w_good && alpha < alpha_range_good)
                        {
                            LED2_8G = 1;
                            LED2_8R = 0;
                        }
                        else if (w >= w_good && alpha < alpha_range_ok)
                        {
                            LED2_8R = 1;
                            LED2_8G = 1;
                        }
                        else
                        {
                            LED2_8R = 1;
                            LED2_8G = 0;
                        }
                    }

                    else if ((led_angle > 135*PI/180.0 && led_angle <= 165*PI/180.0) || (led_angle > -45*PI/180.0 && led_angle <= -15*PI/180.0))
                    {
                        LED1_7G = 0;
                        LED1_7R = 0;
                        LED2_8R = 0;
                        LED2_8G = 0;
                        LED4_10R = 0;
                        LED4_10G = 0;
                        LED5_11G = 0;
                        LED5_11R = 0;
                        LED6_12G = 0;
                        LED6_12R = 0;
                        if (w >= w_good && alpha < alpha_range_good)
                        {
                            LED3_9G = 1;
                            LED3_9R = 0;
                        }
                        else if (w >= w_good && alpha < alpha_range_ok)
                        {
                            LED3_9R = 1;
                            LED3_9G = 1;
                        }
                        else
                        {
                            LED3_9R = 1;
                            LED3_9G = 0;
                        }
                    }
                }
                else
                {
                    LED2_8R = 0;
                    LED2_8G = 0;
                    LED3_9R = 0;
                    LED3_9G = 0;
                    LED4_10R = 0;
                    LED4_10G = 0;
                    LED5_11G = 0;
                    LED5_11R = 0;
                    LED6_12G = 0;
                    LED6_12R = 0;
                    if (w >= w_good && alpha < alpha_range_good)
                        {
                            LED1_7G = 1;
                            LED1_7R = 0;
                        }
                        else if (w >= w_good && alpha < alpha_range_ok)
                        {
                            LED1_7R = 1;
                            LED1_7G = 1;
                        }
                        else
                        {
                            LED1_7R = 1;
                            LED1_7G = 0;
                        }
                    }

            }
        
       
        }
    }    
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
