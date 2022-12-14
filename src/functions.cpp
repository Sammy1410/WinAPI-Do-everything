#include <includes.h>
#include <includes.hpp>

BOOL isMouseHovering(void *obj,int objnum){
    int val=0;

    switch(objnum){
        case Circle:
            return checkCircleHover((circle*)obj);
            break;
        case Rect:
            break;
        case Triangle:
            break;
        default: 
            return -1;
    }
    return 0;
}

BOOL checkCircleHover(circle *c){
    int hit =0;
    float lSide,rSide,top,bottom;
    lSide=c->center.x-c->radius;
    rSide=c->center.x+c->radius;
    top=c->center.y-c->radius;
    bottom=c->center.y+c->radius;
    if( mousePos.x >= lSide && mousePos.x <= rSide)
        hit++;
    if( mousePos.y >= top && mousePos.y <= bottom)
        hit++;

    if(hit==2)
        return 1;
    else
        return 0;
}


void PushText(WCHAR *txt,int posX,int posY,float Fheight,float Fwidth,WCHAR* font,COLORREF color){
    text T;
    T.color=color;
    T.pos.X=posX;
    T.pos.Y=posY;
    swprintf_s(T.font,font);
    //printf("%s\n",txt);
    swprintf_s(T.t,txt);
    //swprintf_s(T.t,L"0");
    T.Lheight=Fheight;
    T.Lwidth=Fwidth;
    stringOut.push_back(T);
    textCount++;
}

void _exit(int err_code){
    fclose(err_logs);
    fclose(warn_logs);
    fclose(msg_logs);

    for(int i=0;i<256;i++){
        key[i]=0;
    }
    SetKeyboardState(key);
    //WindowOn=0;
    ReleaseDC(MainHandle,defaultDC);
    exit(err_code);
}


int location(int x,int y){
    return (y*windowDefault.width+x);
}


float angle(FCOORD p1,FCOORD p2){
    
    return atan(fabs(p2.y-p1.y)/fabs(p2.x-p1.x));
}


float anglerad(FCOORD p1,FCOORD p2){
    float ar,ad,a;
    ar=atan(fabs(p2.y-p1.y)/fabs(p2.x-p1.x));
    if(p2.x>=p1.x && p2.y>=p1.y){
        a=ar;
    }else if(p2.x<=p1.x && p2.y>=p1.y){
        a=M_PI-ar;
    }else if(p2.x<=p1.x && p2.y<=p1.y){
        a=M_PI+ar;
    }else if(p2.x>=p1.x && p2.y<=p1.y){
        a=M_PI*2-ar;
    }

    return a;
}

float deg2rad(float ang){
    return (ang/180)*M_PI;
}

float rad2deg(float ang){
    return (ang/M_PI)*180;
}

float distance(FCOORD p1,FCOORD p2){
    return (sqrt( pow((p2.y-p1.y),2)+pow((p2.x-p1.x),2) ));
}

int randINT(int low,int high){
    srand(time(NULL)*rand()/RAND_MAX);
    return ((rand()% high-low+1)-low);
}

float randF(float low,float high){
    float num;
    int lowINT=(int)round(low);
    int highINT=(int)round(high);
    srand(time(0));
    num=fabs( (float)(randINT(lowINT,highINT)+fabs(((float)rand())/RAND_MAX)) );
    
    return num;
    //return ((rand()% high-low+1)-low);
}


float roundf(float var,int places){

    float value = (int)(var * pow(10,places) + .5);
    return (float)value / pow(10,places);
}


