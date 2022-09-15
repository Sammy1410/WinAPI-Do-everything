#include <includes.h>
#include <tasksobj.h>

void TasksInit(){
    //Pendulum
    bob.spawn(700,300,10,20);
    bobC.center=bob.posXY;
    bobC.color=green;
    bobC.radius=bob.radius;
    wire.start=walldot;
    wire.end=bob.posXY;
    wire.width=1;
    weight.r=gravity*bob.mass;
    weight.t=M_PI_2;
    len=distance(walldot,bob.posXY);


    
    //Ball Drop
    ball.spawn(600,100,10,40);
    ballC.radius=ball.radius;
    ballC.color=black;
    ballC.center=ball.posXY;


    W.r=9.81*(ball.mass);
    W.t=M_PI_2;
    ball.vel.x=5.00f;
    damper.x=dampconstant*ball.vel.x;
    damper.y=dampconstant*ball.vel.y;
    

    //Gravity Simulation
    pCount=5;
    p=(Particle *)malloc(pCount*sizeof(Particle));
    for(int i=0;i<pCount;i++){
        p[i].spawn(randINT(10,windowDefault.width),randINT(10,windowDefault.height),randINT(1,50),10);

    }


}

void Pendulum(double &dt){
    float dist;
    theta=anglerad(walldot,bob.posXY);
    dist=distance(walldot,bob.posXY);
    
    inertia.t=M_PI_2+theta;
    tension.t=M_PI+theta;
    tension.r=weight.r*sin(theta);
    
    inertia.r= bob.mass*( sqrt( pow(bob.vel.x,2) + pow(bob.vel.y,2) ) ) / dist;

    spring.r = wirek * (dist-len); 
    spring.t=M_PI+theta;
    
    bob.f={ /*inertia.r*cos(inertia.t) +*/ tension.r*cos(tension.t) + spring.r*cos(spring.t),
                    /*inertia.r*sin(inertia.t)+*/ weight.r*sin(weight.t) + spring.r*sin(spring.t) +tension.r*sin(tension.t)};
    bob.acc={ bob.f.x/bob.mass , bob.f.y/bob.mass};
    
    bob.vel.x+=bob.acc.x*dt;
    bob.vel.y+=bob.acc.y*dt;

    bob.posXY.x+=( bob.vel.x*dt )*scale;
    bob.posXY.y+=( bob.vel.y*dt )*scale;
    
    if(screenEnable){
        bobC.center=bob.posXY;
        wire.end=bob.posXY;
        Circle_Create(bobC);
        Line_Create(wire);
    }
}


void BallDrop(double &dt){
        
        ball.f={-1*damper.x,-1*damper.y};
        if(key['W']>0){
            ball.f.y-=W.r*sin(W.t);
        }

        if(key['D']>0){
            ball.f.x+=W.r*sin(W.t);
        }

        if(key['S']>0){
            ball.f.y+=W.r*sin(W.t);
        }

        if(key['A']>0){
            ball.f.x-=W.r*sin(W.t);
        }

        if((ball.posXY.x-ball.radius)<=0){
            ball.vel.x*=-1;
            ball.posXY.x=ball.radius;
        } 
        if((ball.posXY.x+ball.radius)>=windowDefault.width){
            //ball.f.x+=ball.mass*-1*ball.vel.x;
            ball.vel.x*=-1;
            ball.posXY.x=windowDefault.width-ball.radius;
        }
        if((ball.posXY.y-ball.radius)<=0) {
            ball.vel.y*=-1;
            ball.posXY.y=ball.radius;
        }
        if((ball.posXY.y+ball.radius) >=windowDefault.height){
            //ball.f.y+=ball.mass*-1*ball.vel.y;
            ball.vel.y*=-1;
            ball.posXY.y=windowDefault.height-ball.radius;
        }

       
        ball.acc={ball.f.x/ball.mass,ball.f.y/ball.mass};
        ball.vel.x+=ball.acc.x*dt;
        ball.vel.y+=ball.acc.y*dt;
        
        ball.posXY.x+=( ball.vel.x*dt+ 0.50f*ball.acc.x*pow(dt,2) ) *scale;
        ball.posXY.y+=( ball.vel.y*dt+ 0.50f*ball.acc.y*pow(dt,2) )  *scale;

        
        damper.x=dampconstant*ball.vel.x;
        damper.y=dampconstant*ball.vel.y;

        ballC.center=ball.posXY;

        if(screenEnable){
            Circle_Create(ballC);
        }
        //return &ball.posXY;

}

void GravitySimulation(double &dt){
    
    circle pcircle[pCount];
    float dist;
    vec Force;
    if(screenEnable){
        for(int i=0;i<pCount;i++){
                pcircle[i].center={p[i].posXY.x,p[i].posXY.y};
                pcircle[i].radius=p[i].radius;
                pcircle[i].color=black;
                //if(i==0)pcircle[0].radius=20;
                //if(i==pCount-1)pcircle[i].radius=20;
                Circle_Create(pcircle[i]);
            }    
    }
    
    for(int i=0;i<pCount;i++){
        p[i].f.x=0;
        p[i].f.y=0;
        int j;
        for(int k=0;k<pCount;k++){
            if(i==k) continue;
            if(i==(pCount-1)){
                j=0;
            }else{
                j=i;
            }
            //fprintf(tr_logs,"Mass %d to Mass %d\n",i,k);
            dist=distance(p[i].posXY,p[k].posXY);
            if(dist<10)continue;
            //fprintf(tr_logs,"Dist: %0.5f\n",dist);
            //fprintf(tr_logs,"Mass %d\t ( %0.5f , %0.5f )\n",i,p[i].posXY.x,p[i].posXY.y);
            //fprintf(tr_logs,"Mass %d\t ( %0.5f , %0.5f )\n",k,p[k].posXY.x,p[k].posXY.y);
            Force.r=(0.667)*p[i].mass*p[k].mass/pow(dist,2);
            Force.t=anglerad(p[i].posXY,p[k].posXY);
            
            //fprintf(tr_logs,"Force: %0.5f Angle: %0.5f\n",Force.r,Force.t);
            //fprintf(tr_logs,"Fx=%0.5f Fy=%0.5f\n\n",Force.r*cos(deg2rad(Force.t)),Force.r*sin(deg2rad(Force.t)));
            p[i].f.x+=Force.r*cos(Force.t);
            p[i].f.y+=Force.r*sin(Force.t);
            
        }
       // fprintf(tr_logs,"Angle: %0.5f\n",atan(p[i].f.y/p[i].f.x))
    }
    
    for(int i=0;i<pCount;i++){
        //if(i==0)continue;
        p[i].acc={p[i].f.x/p[i].mass,p[i].f.y/p[i].mass};
        p[i].vel.x+=p[i].acc.x*dt;
        p[i].vel.y+=p[i].acc.y*dt;
        p[i].posXY.x+=p[i].vel.x*dt+1/2*p[i].acc.x*pow(dt,2);
        p[i].posXY.y+=p[i].vel.y*dt+1/2*p[i].acc.y*pow(dt,2);
        if((p[i].posXY.x+20)>=(windowDefault.width) || (p[i].posXY.x-20)<=0){
            p[i].vel.x*=-1;
        }
        
        if((p[i].posXY.y+20)>=(windowDefault.height) || (p[i].posXY.y-20)<=0){
            p[i].vel.y*=-1;
        }

        p[i].posXY.x*=10;
        p[i].posXY.y*=10;
    }
}


void CreateGraph(){
    int i=0;
    if(screenEnable){      
        do{        
            for(int j=1;j<windowDefault.width;j++){
                CanvasDraw(j,i,shadow);
            }
            i+=5;
        }while(i<windowDefault.height);
    
        i=0;
        do{        
            for(int j=1;j<windowDefault.height;j++){
                CanvasDraw(i,j,shadow);
            }
            i+=5;
        }while(i<windowDefault.width);   
        
        i=50;
        for(int k=0;k<2;k++){
            for(int j=0;j<windowDefault.height;j++){
                CanvasDraw(i+k,j,RGB(53,53,53));
            }
        }
        i=windowDefault.height-75;
        for(int k=0;k<2;k++){
            for(int j=0;j<windowDefault.width;j++){
                CanvasDraw(j,i+k,RGB(53,53,53));
            }
        }
    
    }
    
}
