#include <includes.h>
#include <arduino.h>







void *ArduinoThread(void *vargp){
    startHandle();
    char readTemp;
    //return 0;
    do{
            
        if (arduinoHandle != INVALID_HANDLE_VALUE)
        {
            ArduinoInitialized=1;    
        }
        //do something;

    }while(!ArduinoInitialized);

    BOOL stopRead=0;

    while(1){
        if(updated){
            WriteFile(arduinoHandle,Tx,strlen(Tx),&bytes_written,NULL);
            updated=0;
        }
              
       /* do{
                ReadFile(arduinoHandle,&readTemp,1,&bytes_read,NULL);
                
                if(readTemp!=13 && readTemp!=10){
                    Rx[RxLen]=readTemp;
                    RxLen++;
                    stopRead=0;
                }else{
                    stopRead=1;
                }
        }while(!stopRead);*/
        Sleep(1);
    }

    
    CloseHandle(arduinoHandle);
    getch();

}

void startHandle(){
    arduinoHandle = CreateFileA("\\\\.\\COM6", GENERIC_READ | GENERIC_WRITE, 1, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    arduinoParams.DCBlength=sizeof(arduinoParams);
    GetCommState(arduinoHandle,&arduinoParams);
    
    arduinoParams.BaudRate = 9600;
    arduinoParams.ByteSize = 8;
    arduinoParams.StopBits = TWOSTOPBITS;
    arduinoParams.Parity = NOPARITY;
    SetCommState(arduinoHandle, &arduinoParams);
}
