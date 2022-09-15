#include <includes.h>

//Controlled by Window Thread

//Sets values to MainWindow Class, registers it and creates a window
//Finally it shows the window in the screen
int _InitializeWindow(HINSTANCE _thisInstance,int _ConsoleShowing){
    MainWindowClass.lpfnWndProc = MainHandleMsg;
    MainWindowClass.hInstance=_thisInstance;
    MainWindowClass.lpszClassName=CLASS_NAME;

    RegisterClass(&MainWindowClass);


    MainHandle = CreateWindowEx(
        0,
        CLASS_NAME,
        AppHeader,
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE ,
        windowDefault.xPos,
        windowDefault.yPos,
        windowDefault.width,
        windowDefault.height,
        NULL,
        NULL,
        _thisInstance,
        NULL
    );
    
    RECT rect;
    GetUpdateRect(MainHandle,&rect,0);
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, WS_CLIPSIBLINGS, 0);
    
    LONG lStyle = GetWindowLong(MainHandle, GWL_STYLE);
    lStyle &= ~(WS_CAPTION | WS_THICKFRAME  | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(MainHandle, GWL_STYLE, lStyle); 
    LONG lExStyle = GetWindowLong(MainHandle, GWL_EXSTYLE);
    lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
    SetWindowLong(MainHandle, GWL_EXSTYLE, lExStyle);
    SetWindowPos(MainHandle, NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    
    if(MainHandle == NULL){
        return 0;
    }
    ShowWindow(MainHandle,_ConsoleShowing);
    return 1;
}