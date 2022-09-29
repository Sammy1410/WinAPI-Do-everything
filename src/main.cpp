#ifndef UNICODE
#define UNICODE
#endif
//#define _WIN32_WINNT  0x0500

#include <includes.h>
#include <includes.hpp>

#include "threads.cpp"

#include "initialize.c"
#include "default.c"
#include "functions.cpp"
#include "WinAPI.c"

#include "arduino.c"


#include "tasks.cpp"
#include "frame.cpp"
#include "input.cpp"
#include "graphic.cpp"


int WINAPI WinMain(HINSTANCE thisInstance,HINSTANCE prevInstance,PSTR _pCmdLine,int _ConsoleShowing){

    //Threads needed are defined    
    pthread_t GraphicsThread,WorkThread0,TimerThread,InputThread,ArduinoIO,TextBufferThread;

    //The value of main Window are global so it is sent from these local variables in WinMain
    MainInstance = thisInstance;
    prevMainInstance = prevInstance;
    pCmdLine = _pCmdLine;
    //ConsoleShowing = _ConsoleShowing;
    ConsoleShowing = 0;
    
    //Default info for the application is set here
    SetDefaults();

    int checkWindow;
    err_logs=fopen("F:\\Codes\\Windows Programs\\Windows C_C++\\Application\\logs\\error_logs.txt","a");
    msg_logs=fopen("F:\\Codes\\Windows Programs\\Windows C_C++\\Application\\logs\\message_logs.txt","a");
    warn_logs=fopen("F:\\Codes\\Windows Programs\\Windows C_C++\\Application\\logs\\warn_logs.txt","a");
    tr_logs=fopen("F:\\Codes\\Windows Programs\\Windows C_C++\\Application\\logs\\trial_logs.txt","w");

    //Threads initialized and connected to respective main functions
    pthread_create(&GraphicsThread,NULL,GraphicsUpdater,NULL);
    pthread_create(&WorkThread0,NULL,WorkerThread,NULL);
    pthread_create(&TimerThread,NULL,TimerThreadFunc,NULL);
    pthread_create(&InputThread,NULL,InputThreadFunc,NULL);
    pthread_create(&ArduinoIO,NULL,ArduinoThread,NULL);
    pthread_create(&TextBufferThread,NULL,TextThread,NULL);

 
    while(!TimerInitialized){ }

    checkWindow=_InitializeWindow(thisInstance,_ConsoleShowing);

    switch(checkWindow){
        case 0:
            fprintf(err_logs,"%sFailed To Initialize Window",ctime(&t));
            break;
        case 1:
            fprintf(msg_logs,"________________________________________________________________\n\n");
            fprintf(msg_logs,"%s :: Window Initialized\n\n",time_str);
            break;
    }
    WindowOn=1;
    WindowThreadDone=1;
    while (GetMessage(&MainWinMsg,NULL,0,0))
    {  
        Sleep(1);
        TranslateMessage(&MainWinMsg);
        DispatchMessage(&MainWinMsg);
    }
   _exit(0);   
        

}


void *TimerThreadFunc(void *vargp){
   TimerInitialized=1;
   do{
    program_time=clock();
    
    runtime=double(program_time)/double(CLOCKS_PER_SEC);
    
    //fprintf(tr_logs,"Time: %lf RunTime: %lf\n",program_time,runtime);
    time(&t);
    time_str = ctime(&t);
    time_str[strlen(time_str)-1] = '\0';
    Sleep(1);
   }while(1);
   
    
}

