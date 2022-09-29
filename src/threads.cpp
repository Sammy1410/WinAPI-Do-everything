#include <includes.h>
#include <includes.hpp>
#include <iostream>
#include <arduino.h>


void *TextThread(void *vargp){
    char c;
    int pos=0;
    while(!(WindowInitialized && TimerInitialized)){ }
    char *arr=(char *)malloc(50*sizeof(char));
    wchar_t *send=(wchar_t *)malloc(50*sizeof(char));

    do{
        
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

       for(int i=0x06;i<100;i++){
        int c=0;
        int shift=0;
        if(keytime[i].wasPressed){
            keytime[i].wasPressed=0;
            switch(i){
                case 'A' ... 'Z':
                    
                    if(!(key[VK_SHIFT] || key[VK_CAPITAL])){
                        shift=32;
                    }
                    buf=i+shift;c=1;
                    break;
                case '0' ... '9':
                    buf=i;
                    c=1;
                    break;
                case VK_SPACE:
                    buf=32;c=1;
                    break;
                case VK_BACK:
                    //txtBuf.pop_back();
                    if(!txtWpos==0){
                        txtWpos--;
                        txtBuf[txtWpos]=0;
                    }
                    break;
            }
        }
            if(c){
                //txtBuf.push_back(buf);
                txtBuf[txtWpos]=buf;
                txtWpos++;
            }
            if(txtWpos>50){
                //txtBuf.clear();
                for(int i=0;i<50;i++){
                    txtBuf[i]=0;
                }
                txtWpos=0;
            }
       }
       Sleep(1);
    }while(1);
    
    return 0;
}

void *WorkerThread(void *vargp){
    while(!(WindowInitialized && TimerInitialized)){ }

    clock_t loop_start,loop_end;
    double dt=0;
    static int framelast=0;
    static int framenow=0;
    double _timenow=0;

    TasksInit();

    text T;
    char *arr=(char *)malloc(50*sizeof(char));
    wchar_t *send=(wchar_t *)malloc(50*sizeof(char));
    
    circle c;
    c.center={200,200};
    c.radius=20;
    c.defcolor=blue;
    
    

    do{
        loop_start=clock();
       
        if(isMouseHovering(&c,Circle)){
            if(keytime[VK_LBUTTON].wasPressed){
                keytime[VK_LBUTTON].wasPressed=0;
                if(LEDisOn){
                    LEDisOn=0;
                    updated=1;
                    strcpy(Tx,"off\n");
                }else{
                    LEDisOn=1;
                    updated=1;
                    strcpy(Tx,"on one\n");
                }
                
            }
        }

        if(LEDisOn){
            c.color=red;
        }else{
            c.color=black;
        }
        
        if(screenEnable){
            PushText(L"Red LED",180,240,20,10,defFont,bestT);
            Circle_Create(c);
            mbstowcs(send,txtBuf,50);
            PushText(send,500,10,14,7,defFont,blueT);
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
            ranOnce=0;
            WorkerThreadDone=1;
            framenow++;
            if(_timenow>=1){
                //fprintf(msg_logs,"%s :: FPS = %d \n",time_str,framenow-framelast);
                //fprintf(tr_logs,"FPS = %d\n\n",framenow-framelast);
                //printf("FPS = %d\n",framenow-framelast);
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


