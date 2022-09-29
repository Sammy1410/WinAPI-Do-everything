#ifndef ARDUINO_H_INCLUDED
#define ARDUINO_H_INCLUDED

//ARDUINO
#define COMMAND_MAX_LEN 100
#define MAX_ARGS 5
#define MAX_ARGS_STR 10
//char buffer[BUFFER_MAX_LEN];
char command[COMMAND_MAX_LEN];
char argp[MAX_ARGS][MAX_ARGS_STR];

int buf_len=0;
int cmd_len=0;
int argNo=0;
int arg_len[MAX_ARGS];


void startHandle();

HANDLE arduinoHandle;
DCB arduinoParams = { 0 };

DWORD bytes_written,bytes_read=0;
DWORD tot_bytes_written,tot_bytes_read=0;
char Tx[COMMAND_MAX_LEN+MAX_ARGS*MAX_ARGS_STR+MAX_ARGS];
char Rx[200];
int RxLen=0;

int _readerr;
int i;

int LEDisOn=0;
int updated=0;

#endif