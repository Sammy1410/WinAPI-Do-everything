#include <includes.h>
#include <includes.hpp>
#include <iostream>

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
                    keytime[i].wasPressed=1;
                    keytime[i].holdEnd=runtime;
                    keytime[i].holdTime=0;
                    keytime[i].lastHoldTime=keytime[i].holdEnd-keytime[i].holdStart;                    
                }
            }
        }
        Sleep(1);
    }
        
}