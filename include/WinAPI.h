#ifndef FILE_WINAPI
#define FILE_WINAPI
#include <includes.h>


const wchar_t CLASS_NAME[]= L"Main Window Class";
const wchar_t AppHeader[]=L"Default_WindowName";

struct _windowDefault{
    int xPos;
    int yPos;

    int width;
    int height;
}windowDefault;

HWND MainHandle,ActiveWindow;
HINSTANCE MainInstance,prevMainInstance;
PSTR pCmdLine;
int ConsoleShowing;


WNDCLASS MainWindowClass={};

HDC DeviceContext;  
HDC defaultDC; 
MSG MainWinMsg = {};

int _InitializeWindow(HINSTANCE _thisInstance,int _ConsoleShowing);
LRESULT CALLBACK MainHandleMsg(HWND _MainHandle,UINT uMsg,WPARAM wParam,LPARAM lparam);



#endif