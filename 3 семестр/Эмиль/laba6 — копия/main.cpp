#define _USE_MATH_DEFINES
#include <math.h>
#include "graphics.h"
#include "control.h"
#include "task.h"

using namespace std;

struct Point
{
   int x, y;
};

void init_controls(){
   init_control(UP,0,0,"up.bmp");
   init_control(DOWN,100,0,"down.bmp");
   init_control(RIGHT,200,0,"right.bmp");
   init_control(LEFT,300,0,"left.bmp");
   init_control(L_SPIN,400,0,"lspin.bmp");
   init_control(R_SPIN,500,0,"rspin.bmp");
   init_control(U_SCALE,600,0,"uscale.bmp");
   init_control(D_SCALE,700,0,"dscale.bmp");
   init_control(SAVE,700,700,"save.bmp");
   init_control(EXIT,600,700,"exit.bmp");
}

void draw_interface(){
   for(int i=0;i<N_CONTROLS;i++){
      draw_image(i);
   }
}

int main()
{
   initwindow(800, 800);
   
   Point *figure;
   figure = new Point[4];
   figure[0].x = 0;
   figure[0].y = 200;
   figure[1].x = 100;
   figure[1].y = 0;
   figure[2].x = 200;
   figure[2].y = 0;
   figure[3].x = 100;
   figure[3].y = 200;
   
   Point center = {100, 100};
   
   double *tempx, *tempy;
   tempx=new double [4];
   tempy=new double [4];
   
   tempx[0]=0;
   tempx[1]=100;
   tempx[2]=200;
   tempx[3]=100;
   
   tempy[0]=200;
   tempy[1]=0;
   tempy[2]=0;
   tempy[3]=200;
   
   Figure f(4,100,100,tempx,tempy);
   init_controls();
   int p=0;
   while (true){
      p=1-p;
      setactivepage(p);
      clearviewport();
      f.Draw(COLOR(255,255,0));
      if(mousebuttons()){
         switch(select_control()){
            case NONE:
               break;
            case UP:
               f.GoTo(0,-10);
               break;
            case DOWN:
               f.GoTo(0,10);
               break;
            case RIGHT:
               f.GoTo(10,0);
               break;
            case LEFT:
               f.GoTo(-10,0);
               break;
            case L_SPIN:
               f.Spin(-M_PI/8);
               break;
            case R_SPIN:
               f.Spin(M_PI/8);
               break;
            case U_SCALE:
               f.Scale(1.2);
               break;
            case D_SCALE:
               f.Scale(0.8);
               break;
            case SAVE:
               save();
               break;
            case EXIT:
               goto M;
         }
      }
      draw_interface();
      setvisualpage(p);
      delay(30);
   }
   M:
   delete[]tempx;
   delete[]tempy;
   free_image();
   closegraph();
}