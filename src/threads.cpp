#include <includes.h>

void *WorkerThread(void *vargp){
    while(!WindowInitialized){ }

    
    clock_t loop_start,loop_end;
    double dt=0;
    static int framelast=0;
    static int framenow=0;
    double _timenow=0;


    circle pointer;
    pointer.radius=8;
    pointer.color=blue;

    TasksInit();
    
    do{
        loop_start=clock();
        
        pointer.center={(float)mouse.x,(float)mouse.y};
        //Circle_Create(pointer);
        //BallDrop(dt);
        Pendulum(dt);
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
            fprintf(tr_logs,"FRAME_TIME= %lf\n",frametime);
            screenEnable=1;
            framenow++;
           
            if(_timenow>=1){
                //fprintf(msg_logs,"%s :: FPS = %d \n",time_str,framenow-framelast);
                fprintf(tr_logs,"FPS = %d\n\n",framenow-framelast);
                framelast=framenow;
                _timenow=0;
            }
            frametime=0;
            WorkerThreadDone=1; 
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

void *InputThreadFunc(void *vargp){

    //memset(key,0,sizeof(256));
    while(!(WindowInitialized && TimerInitialized)){ }
    

    
    while(1){
        GetCursorPos(&mouse);
        ScreenToClient(MainHandle, &mouse);
        
        GetKeyState(0);
        GetKeyboardState(key);
        
        if(key[VK_ESCAPE]!=0){
            //_exit(0);
        }
        Sleep(1);
    }
        
}

void *GraphicsUpdater(void *vargp){

    //Windows Rectangle's blank layer is defined
    //Memory is allocated to the buffers 0 and 1
    WinRectArray=(uint32_t *)malloc(windowDefault.width*windowDefault.height*sizeof(uint32_t));
    WinBuffer0=(uint32_t *)malloc(windowDefault.width*windowDefault.height*sizeof(uint32_t));
    ScreenBuf=(uint32_t *)malloc(2*windowDefault.width*windowDefault.height*sizeof(uint32_t));
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



  do{
        
        while(!WorkerThreadDone){}
        DeviceContext=GetDC(MainHandle);
        BufferBMP0=CreateBitmap(windowDefault.width,windowDefault.height,1,sizeof(COLORREF)*8,(void*)WinBuffer0);
        BufferMem0= CreateCompatibleDC(DeviceContext);
        SelectObject(BufferMem0,BufferBMP0);

        BitBlt(DeviceContext,0,0,windowDefault.width,windowDefault.height,BufferMem0,0,0,SRCCOPY); 
        WorkerThreadDone=0;
   
        int c=0;
        //for (int i=0;i<(windowDefault.width*windowDefault.height);i++){
        for(int i=0;i<bufcount;i++){
             //c=WinBuffer0[i];
              WinBuffer0[ScreenBuf[i]]=Wincolor;
              //WinBuffer0[i]=Wincolor;
             if(mouseLdown!=1 && mouseRdown!=1 && mouseMdown!=1){
                //if(WinBuffer0[i]!=Wincolor)  
             }else{
                c=1;
             }
        }
        //if(c!=1)
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


void *TimerThreadFunc(void *vargp){
   TimerInitialized=1;
   do{
    program_time=clock();
    Sleep(1);
    time(&t);
    time_str = ctime(&t);
    time_str[strlen(time_str)-1] = '\0';
   }while(1);
   
    
}
