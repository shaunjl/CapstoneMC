/* 
 * File:   bluetooth.h
 * Author: Capstone team 23
 *
 * Created on March 19, 2016, 12:45 PM
 */

#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

#include <xc.h> // include processor files - each processor file is guarded. 

void uartConfig(void);
void uartConfig2(void);
void uartPutChar(char ch);
char uartGetChar();

#endif	/* BLUETOOTH_H */


