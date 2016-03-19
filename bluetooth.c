#include <p24ep512GP204.h>

void uartConfig(void)
{
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

