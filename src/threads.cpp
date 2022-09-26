#include <includes.h>
#include <includes.hpp>




void *WorkerThread(void *vargp){
    while(!WindowInitialized){ }

    
    clock_t loop_start,loop_end;
    double dt=0;
    static int framelast=0;
    static int framenow=0;
    double _timenow=0;


    circle newCirc[2];
    newCirc[0].center={150,150};
    newCirc[0].radius=50;
    newCirc[0].color=shadow;
    newCirc[1].center={450,450};
    newCirc[1].radius=50;
    newCirc[1].color=black;
    //TasksInit();
    int ObjSelected=-1;
    bool selected=0;
    text T;

    do{
        loop_start=clock();
        
        if(!ranOnce){
            ranOnce =1;
            //PushText(L"HIII",10,10,30,10,L"Comic Sans MS",blue);
            PushText(L"Welcome to the New World Order",400,10,3*8,8,L"Times New Roman",green);
            //stringOut.push_back(T);
            //printf("Here\n");    
            //printf("Count: %d\n",textCount);
            //stringOut.push_back(T);
        }
        //printf("And Here..\n\n");

        for(int i=0;i<2;i++){
            if(isMouseHovering((newCirc+i),Circle)){
                newCirc[i].color=red;
                newCirc[i].radius=55;
                if(Lbutton.holdTime>=0.05f){
                    if(!selected){
                        ObjSelected=i;
                        selected=1;
                    }

                }else{
                    selected=0;
                    ObjSelected=-1;
                    //newCirc[i].center=Lbutton.lastClickPos;
                }
            }else{
                newCirc[i].color=black;
                newCirc[i].radius=50;
            }
        }
        if(ObjSelected>=0){
            newCirc[ObjSelected].center=mousePos;
            newCirc[ObjSelected].color=blue;
        }
            

        if(screenEnable){
            Circle_Create(newCirc[0]);
            Circle_Create(newCirc[1]);
        }
            
        
        //circles();
        
        //BallDrop(dt);
        //Pendulum(dt);
        //CreateGraph();
        //GravitySimulation(dt);
        //Line_Create(l);
        //Text();

        


        //Frame Update Message Generator
        loop_end=clock();
        loop_time+=double(loop_end-loop_start)/double(CLOCKS_PER_SEC);
        loop_start=clock();
        screenEnable=0;
        if(frametime>=(1/FPS)){
            //fprintf(tr_logs,"FRAME_TIME= %lf\n",frametime);
            screenEnable=1;
            WorkerThreadDone=1;
            framenow++;
            if(_timenow>=1){
                //fprintf(msg_logs,"%s :: FPS = %d \n",time_str,framenow-framelast);
                //fprintf(tr_logs,"FPS = %d\n\n",framenow-framelast);
                printf("FPS = %d\n",framenow-framelast);
                framelast=framenow;
                _timenow=0;
            }
            frametime=0;
            while(!FrameUpdated){}
            FrameUpdated=0; 
        }
        
        loop_end=clock();
        loop_time+=double(loop_end-loop_start)/double(CLOCKS_PER_SEC);
        frametime+=loop_time;
        dt=loop_time;
        _timenow+=loop_time;
        loop_time=0;
    }while(1);
}


 void setKeyFunc(int i){
   
 }

void *InputThreadFunc(void *vargp){
    //void setKeyFunc(int i);
    int keyshift;
    //memset(key,0,sizeof(256));
    while(!(WindowInitialized && TimerInitialized)){ }

    while(1){
        keyshift=0;
        if(GetForegroundWindow()!=MainHandle){
            Sleep(10);
            continue;
        }
              
        GetCursorPos(&mouse);
        ScreenToClient(MainHandle, &mouse);
        mousePos={(float)mouse.x,(float)mouse.y};
        
        for(int i=0x01;i<=0xFE;i++){
            key[i]=((GetKeyState(i)) & 0x8000 ? 1:0);
            if(key[i]){
                if(!keytime[i].isPressed)
                    keytime[i].holdStart=runtime;
                keytime[i].isPressed=1;
                keytime[i].holdEnd=runtime;
                keytime[i].holdTime=keytime[i].holdEnd-keytime[i].holdStart;
            }else{
                if(keytime[i].isPressed){
                    
                    keytime[i].isPressed=0;
                    keytime[i].holdEnd=runtime;
                    keytime[i].holdTime=0;
                    keytime[i].lastHoldTime=keytime[i].holdEnd-keytime[i].holdStart;                    
                }
            }

            switch(i){
                case 'A' ... 'Z':     //65 - 90
                case '0' ... '9':     //48 - 57
                    if(keytime[i].isPressed)
                        keyText[i]=1;
                    else
                        keyText[i]=0;
                    break;
                default:            //27(ESCAPE) ,1 - 47 , 48 (0) - 57 (9) , 58 - 64 , 123 - 254
                    break;
            }
        }

 
        if(key[VK_LBUTTON]){
            if(!Lbutton.isHolding){    
                Lbutton.holdStart=runtime;
                Lbutton.lastClickPos=mousePos;
            }
            Lbutton.isHolding=1;
            Lbutton.holdEnd=runtime;
            Lbutton.holdTime=Lbutton.holdEnd-Lbutton.holdStart;
        }else{
            if(Lbutton.isHolding){
                Lbutton.isHolding=0;
                Lbutton.holdEnd=runtime;
                Lbutton.holdTime=0.00f;
                Lbutton.lastHoldTime=Lbutton.holdEnd-Lbutton.holdStart;
    /*
                if(M_writeBuf<MOUSE_BUF_MAX){
                    mouseBuffer[M_writeBuf].x=mousePos.x;
                    mouseBuffer[M_writeBuf].y=mousePos.y;
                    M_writeBuf++;
                }else{
                    //if( !(M_readBuf<M_writeBuf) ){
                        MwriteBufFull=1;
                        M_writeBuf=0;
                    //} 
                }
    */
            }
            
        }

        if(key[VK_MBUTTON]){
            if(!Mbutton.isHolding){
                Mbutton.holdStart=runtime;
                Mbutton.lastClickPos=mousePos;
            }
            Mbutton.isHolding=1;
            Mbutton.holdEnd=runtime;
            Mbutton.holdTime=Mbutton.holdEnd-Mbutton.holdStart;
        }else{
            if(Mbutton.isHolding){
                Mbutton.isHolding=0;
                Mbutton.holdEnd=runtime;
                Mbutton.holdTime=0;
                Mbutton.lastHoldTime=Mbutton.holdEnd-Mbutton.holdStart;
            }
                
        }

        if(key[VK_RBUTTON]){
            if(!Rbutton.isHolding){    
                Rbutton.holdStart=runtime;
                Rbutton.lastClickPos=mousePos;
            }
            Rbutton.isHolding=1;
            Rbutton.holdEnd=runtime;
            Rbutton.holdTime=Rbutton.holdEnd-Rbutton.holdStart;
        }else{
            if(Rbutton.isHolding){
                Rbutton.isHolding=0;
                Rbutton.holdEnd=runtime;
                Rbutton.holdTime=0;
                Rbutton.lastHoldTime=Rbutton.holdEnd-Rbutton.holdStart;
            }
        }

        if(key[VK_ESCAPE]){
            _exit(0);
        }

        Sleep(1);
    }
        
}



void *TimerThreadFunc(void *vargp){
   TimerInitialized=1;
   do{
    program_time=clock();
    
    runtime=double(program_time)/double(CLOCKS_PER_SEC);
    
    fprintf(tr_logs,"Time: %lf RunTime: %lf\n",program_time,runtime);
    time(&t);
    time_str = ctime(&t);
    time_str[strlen(time_str)-1] = '\0';
    Sleep(1);
   }while(1);
   
    
}

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
            fprintf(tr_logs,"In %0.4f ,%d\n",runtime,i);
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

