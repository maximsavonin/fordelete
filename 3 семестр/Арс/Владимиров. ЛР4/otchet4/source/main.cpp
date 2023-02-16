#include "graphics.h"
#include "control.h"
#include "task.h"

int main(){
   initwindow(800, 600);
   IMAGE *image;
   image = loadBMP("fon.jpg");
   putimage(0, 0, image, COPY_PUT);
   freeimage(image);
   create_control(CREATE_ROUNDS, 0, 550,"create.jpg");
   create_control(FILL, 200, 550,"fill.jpg");
   create_control(SAVE, 400, 550,"save.jpg");
   create_control(EXIT, 600, 550,"exit.jpg");
   while(true){
      while(mousebuttons() != 1);
      switch(select_control()){
         case NONE: break;
         case CREATE_ROUNDS: circles(500, 300, 100); break;
         case FILL: fill(500, 300); break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
   }
}