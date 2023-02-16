#include <iostream>
#include "graphics.h"
#include "control.h"
#include "task.h"

using namespace std;

int main()
{
   initwindow(600, 450);
   
   setbkcolor(COLOR(20, 0, 80));
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   
   create_control(NPLUS,   0, 400, "NPLUS.bmp");
   create_control(NMINUS, 100, 400, "NMINUS.bmp");
   create_control(RPLUS, 150, 400, "RPLUS.bmp");
   create_control(RMINUS, 250, 400, "RMINUS.bmp");
   create_control(CLEAR, 300, 400, "clear.bmp");
   create_control(SAVE,   400, 400, "save.bmp");
   create_control(EXIT,   500, 400, "exit.bmp");
   
   IMAGE *image;
   image = loadBMP("fon.bmp");
   IMAGE *imaget;
   imaget = loadBMP("num.bmp");
   
   int left = 0, top = 0, width = 600, height = 400;
   
   int n = 5, r = 20;
   putimage(0, 0, image, COPY_PUT);
   while (true)
   {
      char text[4];
      sprintf(text, "%d", n);
      putimage(50, 400, imaget, COPY_PUT);
      outtextxy(75, 430, text);
      sprintf(text, "%d", r);
      putimage(200, 400, imaget, COPY_PUT);
      outtextxy(225, 430, text);
      while (mousebuttons() != 1)
      {
         if(mousey() < 400 && mousebuttons())
         {
            star(mousex(), mousey(), n, r);
            while(mousebuttons());
         }
      }
      switch (select_control())
      {
         case NONE: break;
         case NPLUS: n = n < 15 ? n+1 : n ; break;
         case NMINUS: n = n > 5 ? n-1 : n ; break;
         case RPLUS: r = r < 80 ? r + 10 : r; break;
         case RMINUS: r = r > 10 ? r - 10 : r; break;
         case CLEAR: putimage(0, 0, image, COPY_PUT); break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      while (mousebuttons());
   }
   freeimage(image);
}