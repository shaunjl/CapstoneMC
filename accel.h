
#ifndef ACCEL_H
#define	ACCEL_H

#include <xc.h> // include processor files - each processor file is guarded.  

void Accel1Config(char addr, char* buffer);
void Accel2Config(char addr, char* buffer);
int ReadX(char addr, char* buffer);
int ReadY(char addr, char* buffer);
int ReadZ(char addr, char* buffer);
int ReadX2(char addr, char* buffer);
int ReadY2(char addr, char* buffer);
int ReadZ2(char addr, char* buffer);

#endif	/* ACCEL_H */

