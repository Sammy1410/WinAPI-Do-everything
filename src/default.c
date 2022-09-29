#include <includes.h>

//Sets initial defaults that the application is going to use

int SetDefaults(){
    //for application window
    //windowDefault.xPos=CW_USEDEFAULT;
    //windowDefault.yPos=CW_USEDEFAULT;
    windowDefault.xPos=0;
    windowDefault.yPos=0;
    windowDefault.width=1280;
    windowDefault.height=720;
    
    for(int i=0;i<256;i++){
        key[i]=0;
        //txtBuf[i]=0;    
        keytime[i].isPressed=0;
        keytime[i].holdStart=0;
        keytime[i].holdEnd=0;
        keytime[i].holdTime=0;
        keytime[i].lastHoldTime=0;
    }
        
    
    Lbutton.isHolding=0;
    Lbutton.holdStart=0;
    Lbutton.holdEnd=0;
    Lbutton.holdTime=0;
    Lbutton.lastHoldTime=0;

    Rbutton.isHolding=0;
    Rbutton.holdStart=0;
    Rbutton.holdEnd=0;
    Rbutton.holdTime=0;
    Rbutton.lastHoldTime=0;
    
    Mbutton.isHolding=0;
    Mbutton.holdStart=0;
    Mbutton.holdEnd=0;
    Mbutton.holdTime=0;
    Mbutton.lastHoldTime=0;    
    return 0;
}
    