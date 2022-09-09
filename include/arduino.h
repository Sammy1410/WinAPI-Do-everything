#ifndef ARDUINO_H_INCLUDED
#define ARDUINO_H_INCLUDED

#define COMMAND_MAX_LEN 10

void startHandle();

HANDLE arduinoHandle;
DCB arduinoParams = { 0 };

DWORD bytes_written,bytes_read=0;
DWORD tot_bytes_written,tot_bytes_read=0;
char *Tx,*Rx;

int _readerr;
int i;




#endif