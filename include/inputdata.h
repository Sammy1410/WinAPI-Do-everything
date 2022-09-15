#ifndef INPUTDATA_SEEN_INCLUDED
#define INPUTDATA_SEEN_INCLUDED

#include <includes.h>

#define MOUSE_BUF_MAX 5


//KeyBoard Inputs
#define KEY_DOWN(vk_code)  ((GetAsyncKeyState(vk_code))&0x8000 ? 1:0)

static int preState=0x30;
BYTE key[256];

//Arduino DATA 
char *ArduinoRbuf;
char *ArduinoWBuf;
int LenRbuf,LenWbuf;

//Mouse Inputs
POINT mouse;  //coordinates


struct buttontime{
    BOOL isHolding;
    float holdstart;
    float holdend;
    float holdtime;
}Lbutton,Rbutton,Mbutton;
int M_ScrollDown=0;
int M_ScrollUp=0;

FCOORD mouseBuffer[MOUSE_BUF_MAX];
int M_writeBuf=0;
int M_readBuf=0;
BOOL MwriteBufFull=0;


#endif