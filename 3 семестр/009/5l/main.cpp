#include "graphics.h"
#include "control.h"
#include "task.h"

int main()
{
   initwindow(900, 600);
   
   IMAGE * image;
   image = loadBMP ("Fon.bmp");
   putimage (0,0,image,COPY_PUT);
   
   create_control(TAKE_DOTS, 0, 540, "take_dots.bmp");
   create_control(CURVE_BEZIER, 150, 540, "curve_bezier.bmp");
   create_control(ALGORITM_CHAIKINA, 300, 540, "algoritm_chaikina.bmp");
   create_control(SAVE,  450, 540, "save.bmp");
   create_control(EXIT,  600, 540, "exit.bmp");
   
   int 
   left = 0, 
   top = 0, 
   width = 800, 
   height = 600;
   
   while (true)
   {
   while (mousebuttons() != 1);
   switch (select_control())
   {
      case NONE: break;
      case TAKE_DOTS:      
         putimage (0,0,image,COPY_PUT);
         create_control(TAKE_DOTS, 0, 540, "take_dots.bmp");
         create_control(CURVE_BEZIER, 150, 540, "curve_bezier.bmp");
         create_control(ALGORITM_CHAIKINA, 300, 540, "algoritm_chaikina.bmp");
         create_control(SAVE,  450, 540, "save.bmp");
         create_control(EXIT,  600, 540, "exit.bmp");
         take_dots(left, top, width, height); break;
      case CURVE_BEZIER: curve_bezier(); break;
      case ALGORITM_CHAIKINA: algoritm_chaikina(); break;
      case SAVE: save(); break;
      case EXIT: closegraph(); return 0;
   }
   while(mousebuttons());
}
freeimage (image);
}