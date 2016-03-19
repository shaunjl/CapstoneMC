/*
 * File:   mag.c
 * Author: Capstone team 23
 *
 * Created on February 24, 2016, 8:51 AM
 */


#include "xc.h"
#include "mag.h"
#include "i2c_helper.h"
#include <math.h>

// Magnetometer Config

//int M = 0b00110010; //define address 

//int mx,my,mz;
//
//// Config on bus line x
//void MagConfig(char addr, char* buffer)
//{
//    I2C1write(addr, 0x20, 0x3F); //configure CTRL_REG1 of accelerometer (normal mode and 1000 Hz rate and all axises on)
//    I2C1requestFrom(addr, 0x20, 1, buffer);
//    while(buffer[0] != 0x3F) //check to make sure it reconfigured if not run again
//    {
//        I2C1write(addr, 0x20, 0x3F); 
//        I2C1requestFrom(addr, 0x20, 1, buffer);
//    }
//    
//    I2C1write(addr, 0x23, 0x10); //configure CTRL_REG4 of accelerometer (Full-scale range (200g))
//    I2C1requestFrom(addr, 0x23, 1, buffer); //check to make sure it configured, if not run again
//    while(buffer[0] != 0x10)
//    {
//        I2C1write(addr, 0x23, 0x10);
//        I2C1requestFrom(addr, 0x23, 1, buffer);
//    }
//   
//}
//
//// Read x values from bus line 1 
//int ReadX(char addr, char* buffer)
//{
//    int x;
//    I2C1requestFrom(addr, 0x29, 1, buffer);
//    x = buffer[0];
//    
//    return(x);
//}
//
//int ReadY(char addr, char* buffer)
//{
//    int y;
//    I2C1requestFrom(addr, 0x2B, 1, buffer);
//    y = buffer[0];
//    
//    return(y);
//}
//
//int ReadZ(char addr, char* buffer)
//{
//    int z;
//    I2C1requestFrom(addr, 0x2D, 1, buffer);
//    z = buffer[0];
//    
//    return(z);
//}
//
///*
// @return an array [x,y,z] in units of m/s^2
// */
//float* GetAccelData(char* buffer)
//{
//        mx = ReadX1(A1, buffer); //read x axis of accelerometer 1
//        my = -1*ReadY1(A1, buffer); //read y axis of accelerometer 1
//        mz = -1*ReadZ1(A1, buffer); //read z axis of accelerometer 1
//
//        float ret[] = {mx,my,mz};
//        
//        return(ret);
//}
