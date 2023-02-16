#include "graphics.h"
#include "control.h"
#include "task.h"

int main() 
{
   initwindow(700, 600);
   
   IMAGE *image;
   
   image = loadBMP("fon.bmp");
   putimage(0, 0, image, COPY_PUT);
   
   create_control(SAVE, 550, 0, 650, 50);
   create_control(EXIT, 650, 0, 700, 50);
   create_control(LEFT, 0, 550, 100, 600);
   create_control(RIGHT, 100, 550, 200, 600);
   create_control(UP, 200, 550, 300, 600);
   create_control(DOWN, 300, 550, 400, 600);
   create_control(ROTEZ, 400, 550, 500, 600);
   create_control(ROTEY, 500, 550, 600, 600);
   create_control(ROTEX, 600, 550, 700, 600);
   Square square = Square();
   square.draw();

   while (true) 
   {
      while (mousebuttons() != 1);
      switch (select_control()) 
      {
         case NONE: break;
         case RIGHT : 
            square.move(0, 1);
            putimage(0, 0, image, COPY_PUT);
            square.draw();
            break;
         case LEFT : 
            square.move(0, -1);
            putimage(0, 0, image, COPY_PUT);
            square.draw();
            break;
         case UP : 
            square.move(1, 1);
            putimage(0, 0, image, COPY_PUT);
            square.draw();
            break;
         case DOWN: 
            square.move(1, -1);
            putimage(0, 0, image, COPY_PUT);
            square.draw();
            break;
         case ROTEX: 
            square.rote(0);
            putimage(0, 0, image, COPY_PUT);
            square.draw(); 
            break;
         case ROTEY: 
            square.rote(1);
            putimage(0, 0, image, COPY_PUT);
            square.draw();
            break;
         case ROTEZ: 
            square.rote(2);
            putimage(0, 0, image, COPY_PUT);
            square.draw();
            break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      delay(50);
   }
   freeimage(image);
}

