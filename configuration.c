#include "xc.h"
#include "configuration.h"



// read from the RA and RB bits but write to the LAT bits
void PinConfig(){
    ANSELA = 0; //set all A ports to digital (turn analog off)
    ANSELB = 0; //set all B ports to digital 

    _TRISA0 = 0; //set RA0 to output
    _TRISA1 = 0; //set RA1 to output
    _TRISA2 = 0; //set RA2 to output
    _TRISA3 = 0; //set RA3 to output
    _TRISB0 = 0; //set RB0 to output
    _TRISB1 = 0; //set RB1 to output
    _TRISB2 = 0; //set RB2 to output
    _TRISB3 = 0; //set RB3 to output
    _TRISB14 = 1; //set RB14 to input
    _TRISB15 = 1; //set RB15 to input
    
    _CVREN = 0;  // turn off cvref pin to be used for i2c
    _SPI1MD = 1;  //Turn SCK off to be used for I2C
    _TRISB8 = 0;  //RB8 as output for I2C
    _TRISB9 = 0;  //RB9 as output for I2X

}
void AnalogConfig(){
    
}
void TimerConfig(){
    // 16 bit counter, 8 MHz clock (4 MHz cycles)
    // this means 2^16/(4Mhz/256)) = 4.19 seconds between interrupts 
    _TON = 0; //timer1 off
    _TCKPS = 0b11; // 1 count: 256 cycles
    PR1 = 62500; //number to count to
    _TSYNC = 0; // do not sync to external clock
    _TCS = 0; // no external clock source
    _T1IP = 4; // Interrupt priority
    _T1IE = 0; // Enable interrupt
    _T1IF = 0; // Clear interrupt flag
    TMR1 = 0; // set timer1 count to 0 initially
}

// read from the RA and RB bits
void InputConfig(){
    _CNIEB14 = 1; //Enable Change Notification bit for B14
    _CNPUB14 = 0; //Disable pull-up resistor
    _CNPDB14 = 0; //Disable pull-down resistor
    _CNIEB15 = 1; //Enable Change Notification bit for B15
    _CNPUB15 = 0; //Disable pull-up resistor
    _CNPDB15 = 0; //Disable pull-down resistor
    _CNIP = 6; // set interrupt priority
    _CNIE = 0; // Enable CN interrupts
    _CNIF = 0; // clear interrupt flag
}

void I2C1Config(char addr, char* buffer)
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

void I2C2Config(char addr, char* buffer)
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