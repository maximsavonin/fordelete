#include "graphics.h"
#include "control.h"
#include "task.h"

int main() 
{
   initwindow(700, 600);
   
   create_control(SAVE, 0, 0, "save.bmp");
   create_control(EXIT, 600, 0, "exit.bmp");
   create_control(RX, 0, 550, "RX.bmp");
   create_control(RY, 100, 550, "RY.bmp");
   create_control(RZ, 200, 550, "RZ.bmp");
   create_control(RIGHT, 300, 550, "right.bmp");
   create_control(LEFT, 400,550, "left.bmp");
   create_control(UP, 500, 550, "up.bmp");
   create_control(DOWN, 600, 550, "down.bmp");
   Figure Piramida = Figure();
   Piramida.draw();

   while (true) 
   {
      while (mousebuttons() != 1);
      switch (select_control()) 
      {
         case NONE: break;
         case RIGHT : 
            Piramida.move(0, 1);
            setfillstyle(SOLID_FILL, BLACK);
            bar(100, 0, 600, 50);
            bar(0, 50, 700, 500);
            Piramida.draw();
            break;
         case LEFT : 
            Piramida.move(0, -1);
            setfillstyle(SOLID_FILL, BLACK);
            bar(100, 0, 600, 50);
            bar(0, 50, 700, 500);
            Piramida.draw();
            break;
         case UP : 
            Piramida.move(1, 1);
            setfillstyle(SOLID_FILL, BLACK);
            bar(100, 0, 600, 50);
            bar(0, 50, 700, 500);
            Piramida.draw();
            break;
         case DOWN: 
            Piramida.move(1, -1);
            setfillstyle(SOLID_FILL, BLACK);
            bar(100, 0, 600, 50);
            bar(0, 50, 700, 500);
            Piramida.draw();
            break;
         case RX: 
            Piramida.rote(0);
            setfillstyle(SOLID_FILL, BLACK);
            bar(100, 0, 600, 50);
            bar(0, 50, 700, 500);
            Piramida.draw(); 
            break;
         case RY: 
            Piramida.rote(1);
            setfillstyle(SOLID_FILL, BLACK);
            bar(100, 0, 600, 50);
            bar(0, 50, 700, 500);
            Piramida.draw();
            break;
         case RZ: 
            Piramida.rote(2);
            setfillstyle(SOLID_FILL, BLACK);
            bar(100, 0, 600, 50);
            bar(0, 50, 700, 500);
            Piramida.draw();
            break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      delay(50);
   }
}

