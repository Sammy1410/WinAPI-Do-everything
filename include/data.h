#ifndef FILE_DATA_SEEN
#define FILE_DATA_SEEN

#include <includes.h>
float scale=100;
float FPS=60.00f;

const float gravity=9.81;
double frametime=0,loop_time=0;
BOOL screenEnable=0;


typedef enum {Circle, Rect, Triangle}objlist;

time_t t;

WCHAR defFont[]= L"Segoe UI";
typedef struct _Text{
    COORD pos;
    float Lheight;
    float Lwidth;
    int len;
    COLORREF color;
    WCHAR font[32];
    WCHAR t[640];    
}text;
int textCount=0;
BOOL ranOnce=0;

typedef struct _FCOORD{
    float x;
    float y;
}FCOORD,*PFCOORD;

typedef struct _vecCart{
    float x;
    float y;
    float r;
    float t;
}vec,*vecP,force,*forceP;


template<class type>
class queue{

    private:
        int _capacity=2;
        int _size=1;
        type *data=(type *)malloc(sizeof(type));
        type *temp;

    
    public:

        type* begin(){
            return data;
        }

        type* end(){
            return data+(_size-1);
        }


        bool isFull(){
            return (_size>=_capacity)?1:0;
        }

        bool isempty(){
            return (_size==0)?1:0;
        }

        type *peek(int pos){
            if(pos>=_size)
                return NAN;
            return data+pos;
        }

        void putIn(type val){
            data[_size-1]=val;
            _size++;
            if(_capacity>=_size){
                _capacity+=100;
                temp=(type *)calloc(_capacity,sizeof(type));
                for(int i=0;i<_size;i++){
                    temp[i]=data[i];
                }
                free(data);
                data=temp;
                //temp=NULL;
            }
        }

        int dequeue(){
            if(isempty()){
                return -1;
            }
        }
};



char *time_str;
double program_time,runtime;

//std::fstream err_logs,warn_logs,msg_logs;
FILE *err_logs,*warn_logs,*msg_logs,*tr_logs;

#endif