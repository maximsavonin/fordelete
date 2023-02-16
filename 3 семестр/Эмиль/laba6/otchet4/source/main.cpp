#define _USE_MATH_DEFINES
#include <math.h>
#include "graphics.h"
#include "control.h"
#include "task.h"

using namespace std;

int main()
{
   initwindow(800, 600);
   
   IMAGE *image;
   
   image = loadBMP("fon.bmp");
   putimage(0, 0, image, COPY_PUT);
   
   create_control(LEFT, 0, 550, 100, 600);
   create_control(RIGHT, 100, 550, 200, 600);
   create_control(UP, 200, 550, 300, 600);
   create_control(DOWN, 300, 550, 400, 600);
   create_control(SPIN, 400, 550, 500, 600);
   create_control(DSPIN, 500, 550, 600, 600);
   create_control(UP_SCALE, 600, 550, 700, 600);
   create_control(DOWN_SCALE, 700, 550, 800, 600);
   create_control(SAVE, 650, 0, 750, 50);
   create_control(EXIT, 750, 0, 800, 50);
   
   Point *figure;
   figure = new Point[4];
   figure[0].x = -100;
   figure[0].y = 100;
   figure[1].x = 0;
   figure[1].y = -100;
   figure[2].x = 100;
   figure[2].y = -100;
   figure[3].x = 0;
   figure[3].y = 100;
   
   Point center = {100, 100};
   
   int p=0;
   while (true){
      p=1-p;
      setactivepage(p);
      putimage(0, 0, image, COPY_PUT);
      draw(center, figure);
      if(mousebuttons()){
         switch(select_control()){
            case NONE:
               break;
            case UP:
               center.y -= 10;
               break;
            case DOWN:
               center.y += 10;
               break;
            case RIGHT:
               center.x += 10;
               break;
            case LEFT:
               center.x -= 10;
               break;
            case SPIN:
               spin(figure, -M_PI/15);
               break;
            case DSPIN:
               spin(figure, M_PI/15);
               break;
            case UP_SCALE:
               scale(figure, 1.1);
               break;
            case DOWN_SCALE:
               scale(figure, 0.9);
               break;
            case SAVE: save(); break;
            case EXIT: delete[]figure; closegraph(); return 0;
         }
      }
      
      setvisualpage(p);
      delay(50);
   }
   
   delete[]figure;
   closegraph();
}