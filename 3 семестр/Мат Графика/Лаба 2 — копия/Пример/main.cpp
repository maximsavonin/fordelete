#include "graphics.h"
#include "control.h"
#include "task.h"

using namespace std;

int main()
{
   initwindow(600, 450);
   
   create_control(FILL_1,   0, 400, "fill_1.bmp");
   create_control(FILL_2,  50, 400, "fill_2.bmp");
   create_control(SAVE,   400, 400, "save.bmp");
   create_control(EXIT,   500, 400, "exit.bmp");
   
   int left = 0, top = 0, width = 600, height = 400;
   Circ a[2];
   
   while (true)
   {
      while(mousebuttons() != 1);
      switch(select_control())
      {
         case NONE: break;
         case FILL_1: creatPoint(a, left, top, width, height); break;
         case FILL_2: treat(a); break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      while(mousebuttons());
   }
}