#define _USE_MATH_DEFINES 
#include "graphics.h"
#include "task.h"
#include "cstdlib"
#include "ctime"
#include <cmath>


bool is_drawed = false;

void circ(int x0, int y0, int r){
   int color = COLOR_MAX;
   int x = 0, y = r, p = 3 - 2 * r;
   int mark[2] = {1, -1};
   while(x <= y){
      for(int i = 0; i < 2; i++){
         for(int j=0; j < 2;j++){
            putpixel(x0 + mark[i] * x, y0 + mark[j] * y,color);
            putpixel(x0 + mark[i] * y, y0 + mark[j] * x,color);
         }
      }
      if(p>0){
         p+= 4 * (x - y) + 10;
         y--;
      }
      else{
         p += 4 * x + 6;
      }
      x++;
   }
}

void circles(int x0, int y0, int r){
   for(int i = 0; i<12; i++){
      circ(x0+r*cos((M_PI/6)*i), y0+r*sin((M_PI/6)*i),  r);
   }
   is_drawed = true;
}

void fill(int x0, int y0){
   if(is_drawed){
      while(mousebuttons()!=0);
      srand(time(0));
      int color[6];
      int r[6]= {25, 50, 80, 135, 160, 185};
      double d = M_PI / 6, d1 = d / 2;
      int x,y; 
      for (int i=0; i < 6; i++){
         color[i]=rand()%WHITE;
      }
      for (int i=0; i<6; i++){
         setfillstyle(SOLID_FILL,color[i]);
         for (int j=0; j<12; j++){
            x=x0+r[i]*cos(j*d+d1*((i+1)%2));
            y=y0+r[i]*sin(j*d+d1*((i+1)%2));
            floodfill(x,y,COLOR_MAX);
         }
      }
   }
}

void save(){
   int width, height;
   IMAGE *output;

   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);

   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.jpg", output);
   freeimage(output);
}