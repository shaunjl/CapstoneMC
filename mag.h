
#ifndef MAG_H
#define	MAG_H

#include <xc.h> // include processor files - each processor file is guarded.  

void MagConfig(char addr, char* buffer);
int ReadX(char addr, char* buffer);
int ReadY(char addr, char* buffer);
int ReadZ(char addr, char* buffer);

#endif	/* MAG_H */
