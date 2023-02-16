#include "graphics.h"
#include "control.h"
#include "task.h"

int main()
{
   initwindow(800, 600);
   
   IMAGE * image;
   image = loadBMP ("spider.bmp");
   putimage (0,0,image,COPY_PUT);
   
   create_control(MARK_POINTS, 700, 0, "mark_points.bmp");
   create_control(BEZIER_CURVE,700, 100,"bezier_curve.bmp");
   create_control(CHAIKIN_ALG, 700, 200, "chaikin_alg.bmp");
   create_control(SAVE,   700, 300, "save.bmp");
   create_control(EXIT,   700, 400, "exit.bmp");
   
   int left = 0, top = 0, width = 700, height = 600;
   
   while (true)
   {
      while (mousebuttons() != 1);
      switch (select_control())
      {
         case NONE: break;
         case MARK_POINTS: 
         putimage (0,0,image,COPY_PUT);
         create_control(MARK_POINTS, 700, 0, "mark_points.bmp");
         create_control(BEZIER_CURVE, 700, 100, "bezier_curve.bmp");
         create_control(CHAIKIN_ALG, 700, 200, "chaikin_alg.bmp");
         create_control(SAVE,   700, 300, "save.bmp");
         create_control(EXIT,   700, 400, "exit.bmp");
         mark_points(left, top, width, height);
         break;
         case BEZIER_CURVE: bezier_curve(); break;
         case CHAIKIN_ALG: chaikin_alg(); break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
   }
   freeimage (image);
}