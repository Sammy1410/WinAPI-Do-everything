#ifndef FILE_DATA_SEEN
#define FILE_DATA_SEEN

#include <includes.h>
float scale=100;
float FPS=60.00f;
double frametime=0,loop_time=0;
BOOL screenEnable=0;




time_t t;

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
class queueCOORD{

    private:
        int size_max=50;

    
    public:
        type *data;
        int size=0;

        queueCOORD(int _size){
            data=(type *)calloc(_size,sizeof(type));
        }

        bool isFull(){
            if(size>=size_max){
                return 1;
            }else{
                return 0;
            }
        }

        bool isempty(){
            if(size==0){
                return 1;
            }else{
                return 0;
            }
        }

        type *peek(){
            return &(data[size]);
        }

        int putIn(float _x,float _y){
            if(isFull()){
                return -1;
            }
            
            data[size].x=_x;
            data[size].y=_y;
            size++;
            return 1;
        }

        int putInF(float _x,float _y){
            if(isFull()){
                data=(type*)malloc(sizeof(type));
                size_max++;
            }
            
            data[size].x=_x;
            data[size].y=_y;
            size++;
            return 1;
        }

        int dequeue(){
            if(isempty()){
                return -1;
            }
            

        }


};


template<class type>
class queue{

    private:
        int size_max=50;

    
    public:
        type *data;
        int size=0;

        queue(int _size){
            data=(type *)calloc(_size,sizeof(type));
        }

        bool isFull(){
            if(size>=size_max){
                return 1;
            }else{
                return 0;
            }
        }

        bool isempty(){
            if(size==0){
                return 1;
            }else{
                return 0;
            }
        }

        type *peek(){
            return data+size;
        }

        int putIn(float n){
            if(isFull()){
                return -1;
            }
            
            data[size]=n;
            size++;
            return 1;
        }

        int putInF(float n){
            if(isFull()){
                data=(type*)malloc(sizeof(type));
                size_max++;
            }
            
            data[size]=n;
            size++;
            return 1;
        }

        int read(){
            if(isempty()){
                return -1;
            }
            

        }


};


char *time_str;
double program_time;

//std::fstream err_logs,warn_logs,msg_logs;
FILE *err_logs,*warn_logs,*msg_logs,*tr_logs;

#endif