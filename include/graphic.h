#ifndef FILE_GRAPHIC_SEEN
#define FILE_GRAPHIC_SEEN

#include <includes.h>

uint32_t *WinRectArray;
HBITMAP WinRect;
HDC WinRectMemDC;

int LastBufferSet=0;

BOOL BufShown0=1;
BOOL BufShown1=0;
uint32_t *WinBuffer0,*WinBuffer1;
HBITMAP BufferBMP0,BufferBMP1;
HDC BufferMem0,BufferMem1;


//uint32_t *ScreenBuf;
int bufcount=0;


HBITMAP bmp;

void CanvasDraw(int x,int y,COLORREF color);
void Poly_Create(polyP Poly);
void Line_Create(line Line);
void Rect_Create(rectP rect);
void Circle_Create(circle Circle);
void Text();

#endif