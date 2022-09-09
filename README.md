# Windows-Graphics

Here I am trying to use mostly C in my codes. I just made classes for checking how much easy will it make me, (not you I know many say to me to switch to C++ but 
I am using just C because it is what I like to use. I am also looking forward to use C++ objects too but this is just the start.)
I could use OpenGL and SFML and what else not in my codes to make it easily. But rather than using what is already built and is best I chose to
make my own code using WinAPI. 
This is because I am trying to learn how this all works in the background. I am trying to get to point where the software and hardware level meets in
the graphics handler. I know there is a bunch of things regarding about kernels and daemons but this is furthest point I have reached in my journey.

So the code is divided into four threads:
--> Main Thread
    This Thread is the mother thread. It sets defaults and creates a White Rectangle of set size. This also creates a buffer for screen where the other codes write into.
    As if the buffer is the virtual screen. Once the Worker Thread finishes writing to screen buffer, it displays it on screen as bitmap. It then clear the screen buffer.
    I am looking for making a second screen buffer also so that worker thread can render without waiting for buffer1 to be displayed. "Double buffering" may I say.
    
--> Timer Thread
    This thread runs and stores the time and date value in time_str variable.
    
--> Window Thread
    It receives message from 'Windows' such as mouse hover location, minimize screen, etc.
    
--> Worker Thread (1)
    This is one of the working threads. In any single loop it has to draw all the components specified on the screen buffer.

And yes I have written code so that almost all variables are global. I am just thinking that any variable may be of use for any other functions.
I don't care about security right now. So I will segregate it once I reach where I am headed.
