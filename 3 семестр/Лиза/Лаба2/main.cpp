#include "graphics.h"
#include "control.h"
#include "task.h"

int main()
{
   initwindow(600, 450);
   
   create_control(FILL_1,   0, 400, "start.bmp");//изменить названия файлов
   create_control(FILL_2,  150, 400, "sq.bmp");
   create_control(SAVE,   300, 400, "save.bmp");
   create_control(EXIT,   450, 400, "exit.bmp");
   
   int left = 0, top = 0, width = 600, height = 400;
   
   IMAGE *image;
   image = loadBMP("back.bmp");
   putimage(left, top, image, COPY_PUT);
   freeimage(image);
   
   while (true)
   {
      while (mousebuttons() != 1);
      switch (select_control())
      {
         case NONE: break;
         case FILL_1: genPoint(left, top, width, height); break;
         case FILL_2: recPoint(left, top, width, height); break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      while(mousebuttons() == 1);
   }
}