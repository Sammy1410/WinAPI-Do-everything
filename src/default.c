#include <includes.h>

//Sets initial defaults that the application is going to use

int SetDefaults(){
    //for application window
    windowDefault.xPos=CW_USEDEFAULT;
    windowDefault.yPos=CW_USEDEFAULT;
    windowDefault.width=1280;
    windowDefault.height=720;
    
    for(int i=0;i<256;i++)
        key[i]=0;
    
    Lbutton.isHolding=0;
    Lbutton.holdstart=0;
    Lbutton.holdend=0;
    Lbutton.holdtime=0;

    Rbutton.isHolding=0;
    Rbutton.holdstart=0;
    Rbutton.holdend=0;
    Rbutton.holdtime=0;
    
    Mbutton.isHolding=0;
    Mbutton.holdstart=0;
    Mbutton.holdend=0;
    Mbutton.holdtime=0;
    
    
    return 0;



}
    