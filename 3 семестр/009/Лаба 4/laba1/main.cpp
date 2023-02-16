#include "graphics.h"
#include "control.h"
#include "task.h"

int main()
{
   initwindow(900, 600);
   
   IMAGE * image ;
   image = loadBMP ("Fon.bmp" );
   putimage (0 , 0 , image , COPY_PUT );
   
   
   create_control(CLEAR, 450, 540, "clear.bmp");   //do less size
   create_control(SAVE, 600, 540, "save.bmp");  
   create_control(EXIT, 750, 540, "exit.bmp");
    
   int x = 450, y = 300, selectColor = 0;
   int color[7] = {RED, GREEN, BLUE, YELLOW, LIGHTBLUE, MAGENTA, WHITE};
   
   putimage (0 , 0 , image , COPY_PUT );
   drawAllCircle();
   setcolor(LIGHTGRAY);
   for(int i = 0; i < 7; i++)
   {
      drawCircle(40+62*i, 570, 29);
      setfillstyle(SOLID_FILL, color[i]);
      floodfill(40+62*i, 570, LIGHTGRAY);
   }
   setcolor(COLOR(77, 255, 0));
   line(0, 540, 900, 540);
   while (true)
   {
      while (select_control() == NONE || mousebuttons() != 1)
      {
         if(mousebuttons())
         {
            for(int i = 0; i < 7; i++)
            {
               if(mousex() > 11+62*i && mousex() < 69+62*i && mousey() > 541 && mousey() < 599)
               {
                  setfillstyle(SOLID_FILL, color[selectColor]);
                  floodfill(40+62*selectColor, 570, LIGHTGRAY);
                  selectColor = i;
                  setfillstyle(SOLID_FILL, BLACK);
                  floodfill(40+62*i, 570, LIGHTGRAY);
               }
            }
            if(mousey() < 540)
            {
               setfillstyle(SOLID_FILL, color[selectColor]);
               floodfill(mousex(), mousey(), COLOR(77, 255, 0));
            }
         }
      }
      switch (select_control())
      {
         case NONE: break;
         case CLEAR: 
         {
            putimage (0 , 0 , image , COPY_PUT );
            drawAllCircle();
            break;
         }
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
   }
   freeimage (image);
}