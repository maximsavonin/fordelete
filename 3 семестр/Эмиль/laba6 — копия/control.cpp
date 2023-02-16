#include "graphics.h"
#include "control.h"

Control controls[N_CONTROLS];
IMAGE *image[N_CONTROLS];

void init_control(int i, int left, int top,const char *file_name){
   image[i]=loadBMP(file_name);
   
   controls[i].left   = left;
   controls[i].top    = top;
   controls[i].right  = left + imagewidth(image[i]) - 1;
   controls[i].bottom = top  + imageheight(image[i]) - 1;
   
}

void free_image(){
   for(int i=0;i<N_CONTROLS;i++){
      freeimage(image[i]);
   }
}

void draw_image(int i){
   putimage(controls[i].left, controls[i].top, image[i], COPY_PUT);
}

int select_control(){
   int x, y;
   
   x = mousex();
   y = mousey();
   
   for (int i = 0; i < N_CONTROLS; i++)
   {
      if (x > controls[i].left && x < controls[i].right &&
          y > controls[i].top  && y < controls[i].bottom)
      {
         return i;
      }
   }
   return NONE;
}