#include "graphics.h"
#include "control.h"
#include "task.h"

using namespace std;

int main()
{
   initwindow(600, 450);
   
   create_control(FILL_1,   0, 400, "create.bmp");
   create_control(FILL_2,  150, 400, "treat.bmp");
   create_control(SAVE,   300, 400, "save.bmp");
   create_control(EXIT,   450, 400, "exit.bmp");
   
   int left = 0, top = 0, width = 600, height = 400;
   Point points[15];
   IMAGE *image;
   
   image = loadBMP("Map.bmp");
   putimage(left, top, image, COPY_PUT);
   
   freeimage(image);
   while (true)
   {
      while(mousebuttons() != 1);
      switch(select_control())
      {
         case NONE: break;
         case FILL_1: creatPoint(points, left, top, width, height); break;
         case FILL_2: treat(points); break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      while(mousebuttons());
   }
}