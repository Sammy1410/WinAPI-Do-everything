#include <includes.h>

//Here the definition of functions for graphics is written

void CanvasDraw(int x,int y,COLORREF color){
    int pos;
    int _y;
    
    if(!(x<0 || y<0 || x>=(windowDefault.width-1) || y>=(windowDefault.height-1)))
    {
       // _y=windowDefault.height-y;
        pos=y*windowDefault.width+x;
        ScreenBuf[bufcount]=pos;
        bufcount++;
        WinBuffer0[pos]=color;
    }    
}


void Circle_Create(circle circle){
    int i,j;
    float dist;
    i=circle.center.x-circle.radius;
   
    do{
        j=circle.center.y-circle.radius;
        do{
            dist= sqrt(pow((circle.center.x-i),2)+pow((circle.center.y-j),2));
            
            //if(fabs(dist-radius)<0.5){
            if(dist<circle.radius){
                CanvasDraw(i,j,circle.color);
            }    
            j+=1;
        }while(j<=(circle.center.y+circle.radius));
        i+=1;
    }while(i<=(circle.center.x+circle.radius));
     
}

static int c=0;

void Poly_Create(polyP Poly){
    
    line ldata;
    for(int j=1;j<=Poly->no;j++){
       /*
        if(c==0){
            fprintf(tr_logs,"Start: %0.2f , %0.2f\n",Poly->points[j-1]->x,Poly->points[j-1]->y);
            //fprintf(tr_logs,"End: %0.2f , %0.2f\n",Poly->points[j]->x,Poly->points[j]->y);
            //fprintf(tr_logs,"COLOR: %d\n",Poly->color[j]);
            
            fprintf(tr_logs,"\n");
        }

        */
        if(j==Poly->no){
            ldata.end={Poly->points[0]->x,Poly->points[0]->y};
        }else{
            ldata.end={Poly->points[j]->x,Poly->points[j]->y};
        }
        ldata.start={Poly->points[j-1]->x,Poly->points[j-1]->y};
        ldata.color=Poly->color[j-1];
        ldata.width=1;

        Line_Create(ldata);                                              
    }
    c++;
}

//Lines - Straight
void Line_Create(line Line){
    Line.slope=(Line.end.y-Line.start.y)/(Line.end.x-Line.start.x);
    double i,j;
    int k;
    float precision=0.3;
    if(Line.end.x==Line.start.x){
        k=Line.start.y;
        do{
            CanvasDraw(Line.start.x,k,Line.color);
            if(Line.start.y<Line.end.y){
                k++;
            }else{
                k--;
            }
        }while(fabs(k-Line.end.y)>=1);
        
        return;
    }

    for(int k=0;k<Line.width;k++){
        j=Line.start.y;
        i=Line.start.x+k;
        do{
           
            CanvasDraw(i,j,Line.color);
            
            if(Line.end.x<Line.start.x){
                i-=precision;
                j-=Line.slope*precision;
                if(i<=Line.end.x)
                    break;
            }else{
                i+=precision;
                j+=Line.slope*precision;
                if(i>=Line.end.x)
                    break;
            }
        }while(1);

    }  
}

//Rectangles
void Rect_Create(rect rect){
    rect.length=rect.end.x-rect.start.x;
    rect.breadth=rect.end.y-rect.start.y;
    for(int j=0;j<rect.breadth;j++){
        for (int i=0;i<rect.length;i++){
            CanvasDraw(rect.start.x+i,rect.start.y+j,rect.color);
        }
    }
    //Checking with pointers
    /*
    rect->length=rect->end.x-rect->start.x;
    rect->breadth=rect->end.y-rect->start.y;
    //fprintf(msg_logs,"%f %f %f %f %d\n",rect->start.x,rect->start.y,rect->end.x,rect->end.y,rect->color);
    for(int j=0;j<=rect->breadth;j++){
        for (int i=0;i<rect->length;i++){
            CanvasDraw(rect->start.x+i,rect->start.y+j,rect->color);
        }
    }
    */
}


void Text(){
    
    HDC a=GetDC(GetForegroundWindow());
    
    HFONT hFont = CreateFont(/*y_position, closest_match, escapement, orientation, FW_DONTCARE,
                              no_italic, no_ul, no_xout, ANSI_CHARSET,
                              OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
                              TEXT("Tekton Pro")/*"SYSTEM_FIXED_FONT"*//*);*/
          48,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Comic Sans MS"));
          
          
          HFONT hOldFont = (HFONT) SelectObject(a, hFont); // <-- add this
        
          //SetTextColor(hdc, RGB(0, 0, 0));
          //TextOut(hdc, 50, 10, TEXT("Hello"), strlen("Hello"));
          TextOut(a, 0, 0, TEXT("Hello"), strlen("Hello"));
          SelectObject(a, hOldFont); // <-- add this
          DeleteObject(hFont);

}

