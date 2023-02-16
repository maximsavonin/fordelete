#include <math.h>
#include <random>
#include <time.h>

#include "graphics.h"
#include "task.h"

Point points[N_POINT];

void genPoint(int left, int top, int width, int height)
{
   IMAGE *image;
   image = loadBMP("back.bmp");
   putimage(left, top, image, COPY_PUT);
   freeimage(image);
   
   for(int i = 0; i < N_POINT; i++)
   {
      points[i].x = rand() % (width-4)+2;
      points[i].y = rand() % (height-4)+2;
      
      IMAGE *image;
      image = loadBMP("slime.bmp");
      putimage(points[i].x-10, points[i].y-10, image, COPY_PUT);
      freeimage(image);
   }
}

void recPoint(int left, int top, int width, int height)
{
   int x_min = width, y_min =  height, x_max = left, y_max = top;
   
   for(int i = 0; i < N_POINT; i++)
   {
      if(points[i].x < x_min){
         x_min = points[i].x;
      }
      if(points[i].x > x_max){
         x_max = points[i].x;
      }
      if(points[i].y < y_min){
         y_min = points[i].y;
      }
      if(points[i].y > y_max){
         y_max = points[i].y;
      }
   }
   rectangle(x_min-10, y_min-10, x_max+10, y_max+10);
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