#ifndef FILE_FUNCTIONS_SEEN
#define FILE_FUNCTIONS_SEEN

#include <includes.h>

BOOL WindowOn;
BOOL WindowThreadDone=0;
BOOL WindowInitialized=0;

int location(int x,int y);

BOOL isMouseHovering(void *obj,int objnum);
BOOL checkCircleHover(circle *c);

void PushText(WCHAR* txt,int posX,int posY,float Fheight,float Fwidth,WCHAR* font,COLORREF color);

float distance(FCOORD p1,FCOORD p2);
float roundf(float var,int places);

float angle(FCOORD p1,FCOORD p2);
float anglerad(FCOORD p1,FCOORD p2);
float deg2rad(float ang);
float rad2deg(float ang);

int randINT(int low,int high);
float randF(float low,float high);



void _exit(int err_code);

#endif