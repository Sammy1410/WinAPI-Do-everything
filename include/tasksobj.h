#include <includes.h>



//Pendulum
force inertia,tension,spring,weight;
float wirek=0.15,len;
force Bob_Fg;
FCOORD walldot={600,200};
Particle bob;
circle bobC;
line wire;
float theta;




//Ball Drop
Particle ball;
circle ballC;

force W,damper;
float dampconstant=5;



//Gravity simulation
Particle *p;
int pCount;

    