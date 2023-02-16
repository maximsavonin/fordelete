#define _USE_MATH_DEFINES
#include <math.h>
#include "graphics.h"
#include "task.h"

void draw(Point center, Point *figure){
   setfillstyle(SOLID_FILL, COLOR(255, 255, 0));
   int *points;
   points = new int[8]();
   for(int i=0; i<4; i++){
      points[2*i] = figure[i].x+center.x;
      points[2*i+1] = figure[i].y+center.y;
   }
   fillpoly(4, points);
   delete [] points;
}

void scale(Point *figure, double s){
   for(int i=0; i<4; i++){
      figure[i].x *= s;
      figure[i].y *= s;
   }
}

void spin(Point *figure, double fi){
   double x;
   for(int i=0; i<4; i++){
      x = figure[i].x;
      figure[i].x = cos(fi)*figure[i].x-sin(fi)*figure[i].y;
      figure[i].y = sin(fi)*x+cos(fi)*figure[i].y;
   }
}

void save()
{
   int width, height;
   IMAGE *output;

   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);

   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}
