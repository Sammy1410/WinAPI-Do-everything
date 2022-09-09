#include <includes.h>
#include <arduino.h>



void *ArduinoThread(void *vargp){
    startHandle();
    Tx=(char*)malloc(sizeof(char));
    Rx=(char*)malloc(sizeof(char));
    return 0;
    do{
            
        if (arduinoHandle != INVALID_HANDLE_VALUE)
        {
            ArduinoInitialized=1;    
        }
        //do something;

    }while(!ArduinoInitialized);



    while(1){
        *Rx='\0';
        *Tx='\0';
        tot_bytes_written=0;
        printf("\nuser@arduino:~ $ ");
        do{
            *Tx=getche();
            WriteFile(arduinoHandle,Tx,1,&bytes_written,NULL);
        }while(*Tx!=13 && *Tx!=10);

        printf("\n");
        //Sleep(500);
        


    do{
                *Rx='\0';
                ReadFile(arduinoHandle,Rx,1,&bytes_read,NULL);
                
                if((*Rx)!=13 && (*Rx)!=10){
                    printf("%c",*(Rx));
                }else{

                }
                  
        }while(*Rx!=13 && *Rx!=10);
        

    }
        printf("\n");

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
