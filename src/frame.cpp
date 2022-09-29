#include <includes.h>
#include <includes.hpp>
#include <iostream>

void *GraphicsUpdater(void *vargp){

    //Windows Rectangle's blank layer is defined
    //Memory is allocated to the buffers 0 and 1
    WinRectArray=(uint32_t *)malloc(windowDefault.width*windowDefault.height*sizeof(uint32_t));
    WinBuffer0=(uint32_t *)malloc(windowDefault.width*windowDefault.height*sizeof(uint32_t));
    //ScreenBuf=(uint32_t *)malloc(2*windowDefault.width*windowDefault.height*sizeof(uint32_t));
    //WinBuffer1=(uint32_t *)malloc(windowDefault.width*windowDefault.height*sizeof(uint32_t));

    //defaultDC=GetDC(MainHandle);
    //Blank Layer is set to contain default windows color
    for (int i=0;i<(windowDefault.width*windowDefault.height);i++){
        //WinRectArray[i]=Wincolor;
        WinBuffer0[i]=Wincolor;
        //WinBuffer1[i]=Wincolor;
    }

    //and then declared as bitmap
    //WinRect=CreateBitmap(windowDefault.width,windowDefault.height,1,sizeof(COLORREF)*8,(void*)WinRectArray);
    
    BufferBMP0=CreateBitmap(windowDefault.width,windowDefault.height,1,sizeof(COLORREF)*8,(void*)WinBuffer0);
    //BufferBMP1=CreateBitmap(windowDefault.width,windowDefault.height,1,sizeof(COLORREF)*8,(void*)WinBuffer1);
    
    //WinRectMemDC= CreateCompatibleDC(DeviceContext);
    //BufferMem0= CreateCompatibleDC(DeviceContext);
    //BufferMem1= CreateCompatibleDC(DeviceContext); 

    WindowInitialized=1;
    while(!(WindowThreadDone && TimerInitialized)){ }

    HFONT hFont;
    wchar_t myText[64];
    
  do{
        int c=0;
        while(!WorkerThreadDone){}
        DeviceContext=GetDC(MainHandle);
        BufferBMP0=CreateBitmap(windowDefault.width,windowDefault.height,1,sizeof(COLORREF)*8,(void*)WinBuffer0);
        BufferMem0= CreateCompatibleDC(DeviceContext);
    //////    
        
        for(int i=0;i<textCount;i++){
            if(key[VK_CONTROL])
                break;
            swprintf_s(myText, stringOut[i].t);

            hFont = CreateFontW(stringOut[i].Lheight, stringOut[i].Lwidth, 0, 10, FW_DONTCARE,
                0, 0, 0, ANSI_CHARSET,
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
                stringOut[i].font);

            SelectObject(BufferMem0, hFont);
            SelectObject(BufferMem0,BufferBMP0);
            SetBkMode(BufferMem0, TRANSPARENT);
            SetTextColor(BufferMem0,stringOut[i].color);
            TextOut(BufferMem0,stringOut[i].pos.X,stringOut[i].pos.Y,myText,wcslen(stringOut[i].t));
            DeleteObject(hFont);
        }
       
        stringOut.clear();
        ranOnce=0;
        textCount=0;
        
        SelectObject(BufferMem0,BufferBMP0);
        BitBlt(DeviceContext,0,0,windowDefault.width,windowDefault.height,BufferMem0,0,0,SRCCOPY); 
        
        WorkerThreadDone=0;
   
        
            //for (int i=0;i<(windowDefault.width*windowDefault.height);i++){
        for(int i=0;i<bufcount;i++){
            //c=WinBuffer0[i];
            WinBuffer0[ScreenBuf[i]]=Wincolor;
            //WinBuffer0[i]=Wincolor;
        }    
        ScreenBuf.clear();
        bufcount=0;
        
        DeleteObject(BufferBMP0);
        DeleteDC(BufferMem0);
        ReleaseDC(MainHandle,DeviceContext);
        FrameUpdated=1;
        
    }while(WindowOn);
    
    DeleteDC(WinRectMemDC);
    free(WinRectArray);
    free(WinBuffer0);
    free(WinBuffer1);
    _exit(0);

}
