#include <p24ep512GP204.h>

void uartConfig(void)
{
    // new config
    _UARTEN = 1; // UART enable bit
    _USIDL = 0; // dont discontinue module operation when device in idle mode
    
    
    // OLD config
    U1BRG = 25;                     //Baud rate set to 9600
    IPC2bits.U1RXIP = 4;            //interrupt priority level for receive
    IPC3bits.U1TXIP = 4;            //interrupt ptiority level for transmit
    U1STA = 0x8400;

    U1MODE = 0x8000;                //8-bit data, no parity, 1 stop bit
//    U1MODEbits.UARTEN = 1;          //enable the module
//   
//    U1STAbits.UTXISEL0 = 0;
//    U1STAbits.UTXISEL1 = 1;         //interrupt generated transmit is complete
    IFS0bits.U1RXIF = 0;            //clear receive interrupt flag

//    U1STAbits.UTXEN = 1;            //enable transmission
//    IEC0bits.U1RXIE = 0;            //UART receiver interrupt disabled
//    IEC0bits.U1TXIE = 0;            //UART transmitter interrupt disabled
}

//Configure UART1
void uartConfig2(void)
{

//OSCCON = 0; // Using 8MHz fast RC ocsillator no dividing option

RPINR18bits.U1RXR = 0b0100010; //UART1 rx set to RPI34 (pin 23)
RPOR0bits.RP35R  = 0b000001; //UART1 tx set to RP35 (pin 24)

//configure UART1 registers. This is a standard 8 bit no parity 1 stop bit
//serial configuration
//do this first
U1MODE = 0;

U1BRG = 12; // Essentially sets baud rate to 9600 bps while
//using 8 mhz FRC with a divide by 2 post scaler giving and execution rate of
// 2 MIPS. There is an equation in the datasheet. This number is
//affected by the internal clock used and the desired serial baudrate.

//configures send receive interrupts. Interrupts whenever the buffer becomes
//empty and as soon as a character is received. This should allow for an event
//driven serial routine to be setup. I despise polling.
U1STAbits.UTXISEL0 = 1;
U1STAbits.UTXISEL1 = 0;
U1STAbits.URXISEL = 0;

U1MODEbits.UARTEN = 1; //enables the uart

U1STAbits.UTXEN = 1; //setting this bit per the data sheet
//U1STAbits.URXEN = 1; //this should enable receiveing data

//reset RX interrupt flag (Guy did this in the tutorial and it works...)
IFS0bits.U1RXIF = 0;

}


void uartPutChar(char ch)
{
    while(U1STAbits.UTXBF);         //transmit only if TX buffer is empty
    U1TXREG = ch;
}

char uartGetChar()
{
    char temp;
    while(IFS0bits.U1RXIF == 0);    //wait for the buffer to fill up
    temp = U1RXREG;                 //copy char
    IFS0bits.U1RXIF = 0;            //reset interrupt
    return temp;                    //return received char
}

