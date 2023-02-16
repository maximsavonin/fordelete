#include "graphics.h"
#include "control.h"
#include "task.h"

int main()
{
   initwindow(800, 600);
   
   IMAGE * image;
   image = loadBMP ("fon.jpg");
   putimage (0,0,image,COPY_PUT);
   freeimage(image);
   create_control(CREATE_POINT, 0, 550, "create_points.jpg");
   create_control(BEZIER, 160, 550, "bezie.jpg");
   create_control(CHAIKINA, 320, 550, "chaikina.jpg");
   create_control(SAVE,  480, 550, "save.jpg");
   create_control(EXIT,  640, 550, "exit.jpg");
   
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
      case CREATE_POINT: create_points(left, top, width, height); break;
      case BEZIER: bezier(); break;
      case CHAIKINA: chaikina(); break;
      case SAVE: save(); break;
      case EXIT: closegraph(); return 0;
   }
   while(mousebuttons());
}
freeimage(image);
}