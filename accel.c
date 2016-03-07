/*
 * File:   accel.c
 * Author: Shaun
 *
 * Created on February 24, 2016, 8:51 AM
 */


#include "xc.h"
#include "accel.h"
#include "i2c_helper.h"
#include <math.h>

// Accelerometer Config

int A1 = 0b00110010; //define address for accelerometer 1 (positive x-axis)
int A2 = 0b00110000; //define address for accelerometer 2 (positive y-axis)
int A3 = 0b00110010; //define address for accelerometer 3 (negative x-axis)
int A4 = 0b00110000; //define address for accelerometer 4 (negative y-axis)

int w,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,A1x,A1y,A1z,A2x,A2y,A2z,A3x,A3y,A3z,A4x,A4y,A4z;
float A0x,A0y,A0z, alphax, alphay, alphaz, wx, wy, wz, psi, phi, theta;

// Accel. 1 & 2 are on bus line 1, 3 & 4 are on bus line 2
// Accel. 1 & 2 are on x, y axis, Accel. 3 & 4 on -x, -y

// Config for both accelerometers on bus line 1
void Accel1Config(char addr, char* buffer)
{
    I2C1write(addr, 0x20, 0x3F); //configure CTRL_REG1 of accelerometer (normal mode and 1000 Hz rate and all axises on)
    I2C1requestFrom(addr, 0x20, 1, buffer);
    while(buffer[0] != 0x3F) //check to make sure it reconfigured if not run again
    {
        I2C1write(addr, 0x20, 0x3F); 
        I2C1requestFrom(addr, 0x20, 1, buffer);
    }
    
    I2C1write(addr, 0x23, 0x10); //configure CTRL_REG4 of accelerometer (Full-scale range (200g))
    I2C1requestFrom(addr, 0x23, 1, buffer); //check to make sure it configured, if not run again
    while(buffer[0] != 0x10)
    {
        I2C1write(addr, 0x23, 0x10);
        I2C1requestFrom(addr, 0x23, 1, buffer);
    }
   
}

// Config for both accelerometers on bus line 2
void Accel2Config(char addr, char* buffer)
{
    I2C2write(addr, 0x20, 0x3F); //configure CTRL_REG1 of accelerometer (normal mode and 1000 Hz rate and all axises on)
    I2C2requestFrom(addr, 0x20, 1, buffer);
    while(buffer[0] != 0x3F) //check to make sure it reconfigured if not run again
    {
        I2C2write(addr, 0x20, 0x3F); 
        I2C2requestFrom(addr, 0x20, 1, buffer);
    }
    
    I2C2write(addr, 0x23, 0x10); //configure CTRL_REG4 of accelerometer (Full-scale range (200g))
    I2C2requestFrom(addr, 0x23, 1, buffer); //check to make sure it configured, if not run again
    while(buffer[0] != 0x10)
    {
        I2C2write(addr, 0x23, 0x10);
        I2C2requestFrom(addr, 0x23, 1, buffer);
    }
   
}

// Read x values from bus line 1 
int ReadX1(char addr, char* buffer)
{
    int x;
    I2C1requestFrom(addr, 0x29, 1, buffer);
    x = buffer[0];
    
    return(x);
}

int ReadY1(char addr, char* buffer)
{
    int y;
    I2C1requestFrom(addr, 0x2B, 1, buffer);
    y = buffer[0];
    
    return(y);
}

int ReadZ1(char addr, char* buffer)
{
    int z;
    I2C1requestFrom(addr, 0x2D, 1, buffer);
    z = buffer[0];
    
    return(z);
}

int ReadX2(char addr, char* buffer)
{
    int x;
    I2C2requestFrom(addr, 0x29, 1, buffer);
    x = buffer[0];
    
    return(x);
}

int ReadY2(char addr, char* buffer)
{
    int y;
    I2C2requestFrom(addr, 0x2B, 1, buffer);
    y = buffer[0];
    
    return(y);
}

int ReadZ2(char addr, char* buffer)
{
    int z;
    I2C2requestFrom(addr, 0x2D, 1, buffer);
    z = buffer[0];
    
    return(z);
}

/*
 @return an array [x,y,z]
 */
float* GetAccelData(char* buffer)
{
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
        
        float ret[] = {A0x,A0y,A0z};
        
        return(ret);
}
