#ifndef FILE_THREADS_SEEN
#define FILE_THREADS_SEEN

#include <includes.h>




BOOL TimerInitialized=0;
BOOL WorkerThreadDone=0;
BOOL FrameUpdated=0;
BOOL ArduinoInitialized=0;


//threaded functions
void *WorkerThread(void *vargp);
void *GraphicsUpdater(void *vargp);
void *TimerThreadFunc(void *vargp);
void *InputThreadFunc(void *vargp);
void *ArduinoThread(void *vargp);

#endif