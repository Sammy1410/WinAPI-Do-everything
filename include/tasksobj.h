#include <includes.h>
#include <vector>

//Circles
static float defRad=10;
int circleCount=0;
//circle **circ;
std::vector<circle> circ;
circle temp;

//Pendulum
force inertia,tension,spring,weight;
float wirek=100,len;
force Bob_Fg;
FCOORD walldot={600,300};
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
static Particle *p;
static int pCount;
    
//circle *pcircle;
circle pcircle;
float dist;
vec Force;
    

    