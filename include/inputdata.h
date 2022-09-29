#ifndef INPUTDATA_SEEN_INCLUDED
#define INPUTDATA_SEEN_INCLUDED

#include <includes.h>

#define MOUSE_BUF_MAX 3

static int preState=0x30;
BYTE key[256];
//WCHAR txtBuf[]={'\0','\0','\0','\0','\0'};
char buf;
int txtWpos=0;

struct keydata{
    BOOL isPressed;
    BOOL wasPressed;
    float holdStart;
    float holdEnd;
    float holdTime;
    float lastHoldTime;
}keytime[256];


//Arduino DATA 
char *ArduinoRbuf;
char *ArduinoWBuf;
int LenRbuf,LenWbuf;

//Mouse Inputs
POINT mouse;  //coordinates
FCOORD mousePos;
FCOORD mouseclickPos={0,0};
struct buttontime{
    BOOL isHolding;
    float holdStart;
    float holdEnd;
    float holdTime;
    float lastHoldTime;
    FCOORD lastClickPos;
}Lbutton,Rbutton,Mbutton;
int M_ScrollDown=0;
int M_ScrollUp=0;

FCOORD mouseBuffer[MOUSE_BUF_MAX];
int M_writeBuf=0;
int M_readBuf=0;
BOOL MwriteBufFull=0;


#endif