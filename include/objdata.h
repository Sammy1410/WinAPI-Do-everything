#ifndef FILE_OBJDATA_SEEN
#define FILE_OBJDATA_SEEN
#include <includes.h>

/*
class vector{
    public:
        float x=0;
        float y=0;
        float r=0;
        float t=0;

        void create(float _x,float _y,char* flag){
            if(strcmp("RT",flag)==0){
                x=_x*cos(_y);
                y=_x*sin(_y);
            }else if(strcmp("XY",flag)){
                r=sqrt(pow(_x,2)+pow(_y,2));
                t=atan(_y/_x);
            }
        }     
};
*/
class Particle{
    public:
        /*Particle(float posx,float posy,float m){
            posXY={posx,posy};
            posRT={(float)sqrt(pow(posx,2)+pow(posy,2)),atan(posy/posx)};
            mass=m;
        }
        */
        float radius=0;
        
        float mass=0;
        vec acc={0,0};
        vec vel={0,0};
        FCOORD posXY={0,0};
        FCOORD posRT={0,0};
        force f={0,0};

        void spawn(float posx,float posy,float m,float r){
            posXY={posx,posy};
            posRT={(float)sqrt(pow(posx,2)+pow(posy,2)),atan(posy/posx)};
            mass=m;
            radius=r;
        };
        private:

        
};

typedef struct _circledata{
        FCOORD center;
        float radius;
        BOOL filled;
        COLORREF color;
        FCOORD *points;
}circle,*circleP;


typedef struct _rectdata{
    FCOORD start;
    FCOORD end;
    FCOORD points;
    float length,breadth;
    BOOL filled;
    COLORREF color;
}rect,*rectP;

typedef struct _polydata{
    int no;
    COLORREF *color;
    PFCOORD *points;
}poly,*polyP;


typedef struct _linedata{
    FCOORD start;
    FCOORD end;
    float slope;
    float theta_v;
    float theta_h;
    int width;
    COLORREF color;
}line,*lineP;

#endif