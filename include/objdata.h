#ifndef FILE_OBJDATA_SEEN
#define FILE_OBJDATA_SEEN
#include <includes.h>

class Particle{
    public:
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
        COLORREF defcolor;
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