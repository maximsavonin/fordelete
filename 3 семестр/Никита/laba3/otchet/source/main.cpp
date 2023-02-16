#include <iostream>
#include "graphics.h"
#include "control.h"
#include "task.h"

using namespace std;

int main()
{
   initwindow(600, 450);
   
   create_control(RUP, 0, 400, "rup.bmp");
   create_control(RDOWN, 75, 400, "rdown.bmp");
   create_control(NUP,   150, 400, "nup.bmp");
   create_control(NDOWN, 225, 400, "ndown.bmp");
   create_control(CLEAR, 300, 400, "clear.bmp");
   create_control(SAVE,   400, 400, "save.bmp");
   create_control(EXIT,   500, 400, "exit.bmp");
   
   IMAGE *image;
   image = loadBMP("fon.bmp");
   
   int left = 0, top = 0, width = 600, height = 400;
   int n = 5, r = 50;
   
   putimage(0, 0, image, COPY_PUT);
   while (true)
   {
      while (mousebuttons() != 1)
      {
         if(mousey()+r < 400 && mousebuttons())
         {
            setcolor(COLOR(255, 0, 0));
            star(mousex(), mousey(), n, r);
            while(mousebuttons());
         }
      }
      switch (select_control())
      {
         case NONE: break;
         case NUP: if(n < 20) n++; break;
         case NDOWN: if(n > 5) n--; break;
         case RUP: if(r < 100) r += 10; break;
         case RDOWN: if(r > 10) r -= 10; break;
         case CLEAR: putimage(0, 0, image, COPY_PUT); break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      while (mousebuttons());
   }
   freeimage(image);
}